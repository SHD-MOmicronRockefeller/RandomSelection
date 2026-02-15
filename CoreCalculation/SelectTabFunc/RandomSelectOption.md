#### 前置定义：常量参数
| 常量名          | 取值        | 作用                                                                 |
|-----------------|-------------|----------------------------------------------------------------------|
| EPS             | 1e-16L      | 精度补偿值，避免除法中分母为0的情况             |
| BASE_OFFSET     | 1.0L        | top_count的基础偏移量，保证top_count至少大于max_count                |
| MIN_TOP_COUNT   | 1e-16L      | top_count最小值，防止过小导致后续偏差度计算失效                      |
| MAX_TOP_COUNT   | 1e18L       | top_count最大值，防止溢出（long double有效位数18位，1e18为安全上限） |

#### 步骤1：过滤活跃选项
- **输入**：`optionList`（待抽取的选项列表）
- **规则**：仅保留满足 `opt.getWeight() > 0` 的选项
- **存储**：用 `std::vector<std::pair<size_t, Base::OptionItem>>` 存储<原列表索引, 选项>对，避免后续步骤索引错位
- **边界处理**：若活跃选项为空，直接返回空的`OptionItem`

#### 步骤2：提取核心数据
从活跃选项中提取两个等长的`long double`数组（长度为活跃选项数`n`）：
- `active_weights[i] = static_cast<long double>(opt.getWeight())`：第`i`个活跃选项的原始权重
- `selected_times[i] = static_cast<long double>(opt.getSelectedTimes())`：第`i`个活跃选项已被选中的次数

#### 步骤3：计算权重平均值
- 总权重：$total\_weight = \sum_{i=0}^{n-1} active\_weights[i]$
- 平均权重：$avg\_weight = \frac{total\_weight}{n}$
- 作用：消除不同选项原始权重差异，为后续“标准化选中次数”做基准

#### 步骤4：计算动态被抽取次数
对每个活跃选项，计算“权重标准化后的选中次数”：
$dynamic\_scores[i] = \frac{selected\_times[i] \times avg\_weight}{active\_weights[i] + EPS}$
- 含义：将每个选项的实际选中次数，换算到“平均权重”下的等效值（比如权重是平均值2倍的选项，若实际选中次数为4，标准化后为2）。
- 目的：消除权重差异对“选中次数公平性”的影响，比如权重高的选项本应被选中更多次，这里统一到同一基准下对比。

#### 步骤5：计算动态分数的统计量
先定义：$DS = dynamic\_scores$
1. 最大值：$max\_count = \max(DS[0], DS[1], ..., DS[n-1])$
2. 总和：$total\_count = \sum_{i=0}^{n-1} DS[i]$
3. 平均值：$avg\_count = \frac{total\_count}{n}$
4. 标准差（衡量DS的离散程度）：
    - 方差和：$std\_sum = \sum_{i=0}^{n-1} (DS[i] - avg\_count)^2$
    - 标准差：$std\_value = \sqrt{\frac{std\_sum}{n}}$
- 作用：描述所有选项“标准化选中次数”的分布特征（最大值、均值、离散度），为后续计算“偏差参考上限”做准备。

#### 步骤6：计算top_count
$top\_count = max\_count + BASE\_OFFSET + smoothing\_factor \times \frac{(max\_count + avg\_count) \times (std\_value + EPS)}{avg\_count + EPS}$
- 参数含义：
    - `smoothing_factor`：平滑因子（输入参数），调节标准差对top_count的影响强度；
    - EPS：避免`avg_count`为0时除法无意义；
- 约束：$top\_count = \text{clamp}(top\_count, MIN\_TOP\_COUNT, MAX\_TOP\_COUNT)$（限制在[1e-16L, 1e18L]）；
- 意义：top_count是“理想的最大标准化选中次数”，作为后续计算“选中不足程度”的参考上限，融合了最大值、均值、离散度，且可通过平滑因子调节。

#### 步骤7：计算偏差度、平均偏差、移位因子
##### 7.1 偏差度（选中不足程度）
$degree\_of\_deviation[i] = \max(top\_count - DS[i], 0.0L)$
- 含义：每个选项的“标准化选中次数”与top_count的差距，且保证非负（若DS[i]≥top_count，说明选中次数已足够，偏差度为0）。

##### 7.2 平均偏差
- 总偏差：$total\_deviation = \sum_{i=0}^{n-1} degree\_of\_deviation[i]$
- 平均偏差：$avg\_deviation = \frac{total\_deviation}{n}$

##### 7.3 移位因子（放大/缩小偏差度的影响）
$shift\_factors[i] = \left( \frac{degree\_of\_deviation[i]}{avg\_deviation + EPS} \right)^{power\_factor}$
- 参数含义：
    - `power_factor`：幂次因子（输入参数），调节偏差度对移位因子的影响强度：
        - $power\_factor > 1$：偏差大的选项，移位因子被放大（选中不足越严重，权重提升越多）；
        - $power\_factor < 1$：偏差大的选项，移位因子被缩小（权重提升幅度更平缓）；
        - $power\_factor = 1$：移位因子与偏差度成正比；
    - EPS：避免`avg_deviation`为0时除法无意义；
- 作用：量化“选中不足程度”，为后续调整权重做核心依据。

#### 步骤8：计算调整后权重
$adjusted\_weights[i] = \max(shift\_factors[i] \times active\_weights[i], EPS)$
- 含义：将原始权重按“选中不足程度”放大（移位因子越大，调整后权重越高）；
- EPS：确保调整后权重不为0（避免选项完全无法被抽取）；
- 核心目的：让选中不足的选项获得更高的抽取权重，实现平衡。

#### 步骤9：初始化线程安全的随机数生成器
- 静态变量：`gen`（mt19937随机数引擎）、`gen_init_flag`（确保仅初始化1次）、`rng_mutex`（互斥锁）；
- 种子生成：混合`random_device`（真随机数）+ 系统时间 + 线程ID，生成`uint64_t seed_data[std::mt19937::state_size]`，再通过`seed_seq`初始化`gen`；
- 作用：保证随机数的不可预测性，且多线程下安全。

#### 步骤10：线程安全的随机选择
1. 加锁：`std::lock_guard<std::mutex> lock(rng_mutex)`（防止多线程竞争随机数引擎）；
2. 离散分布：`std::discrete_distribution<size_t> dist(adjusted_weights.begin(), adjusted_weights.end())`；
    - 规则：选中第`i`个活跃选项的概率 = $\frac{adjusted\_weights[i]}{\sum_{j=0}^{n-1} adjusted\_weights[j]}$；
3. 生成索引：`active_idx = dist(gen)`（按调整后权重的概率分布随机选一个活跃选项索引）。

#### 步骤11：索引校验与返回
1. 映射原索引：`original_idx = active_options[active_idx].first`（从<原索引, 选项>对中获取原始列表索引）；
2. 校验：若`original_idx >= optionList.size()`（索引越界），返回空`OptionItem`；否则返回`optionList[original_idx]`。

### 总结
1. **核心逻辑**：通过“权重标准化选中次数”消除原始权重差异，再基于“选中不足程度”动态调整权重，让选中偏少的选项获得更高抽取概率，实现长期平衡；
2. **核心公式**：
    - 标准化选中次数：$dynamic\_scores[i] = \frac{selected\_times[i] \times avg\_weight}{active\_weights[i] + EPS}$；
    - 调整后权重：$adjusted\_weights[i] = \max( (\frac{\max(top\_count - DS[i], 0)}{avg\_deviation + EPS})^{power\_factor} \times active\_weights[i], EPS )$；
3. **关键参数**：`smoothing_factor`（调节top_count的平滑程度）、`power_factor`（调节选中不足程度对权重的影响强度），是控制平衡力度的核心可调参数。