#pragma once

#include "CoreCalculation/SelectTabFunc/OptionList.hpp"

#include "VariablesStore/globalVariables.h"

#include <random>
#include <ranges>
#include <vector>
#include <algorithm>
#include <map>

namespace CoreCalculation
{

class RandomSelectOption
{
    public: inline static bool _checkList(const OptionList& optionList){
        if (optionList.size() == 0) return false;
        return true;
    }

    public: inline static Base::OptionItem RS_Ordinary(const OptionList& optionList){
        if (not _checkList(optionList)) return Base::OptionItem();
        // 随机选择一个选项
        Base::OptionItem result = _Ordinary(optionList);
        // 增加选中次数
        GlobalVariables::getInstance()->active_option_list.findByIndex(result.getIndex())->selectedTimes()++;
        // 返回结果
        return result;
    }

    public: inline static Base::OptionItem _Ordinary(const OptionList& optionList){
        // 构造权重向量
        std::vector<double> weights;
        weights.reserve(optionList.size());
        for (const auto& option : optionList){
            weights.push_back(option.getWeight());
        }
        // 随机选择
        static std::mt19937 gen(std::random_device{}());
        std::discrete_distribution<size_t> dist(weights.begin(), weights.end());
        return optionList[dist(gen)];
    }

    public: inline static Base::OptionItem RS_Balance(const OptionList& optionList,
        const long double smoothing_factor, const long double power_factor){
        if (not _checkList(optionList)) return Base::OptionItem();
        // 随机选择一个选项
        Base::OptionItem result = _Balance(optionList, smoothing_factor, power_factor);
        // 增加选中次数
        GlobalVariables::getInstance()->active_option_list.findByIndex(result.getIndex())->selectedTimes()++;
        // 返回结果
        return result;
    }

    // 2
    public: inline static Base::OptionItem _Balance(const OptionList& optionList,
        const long double smoothing_factor, const long double power_factor){
        // long double 18 位有效
        //  常量定义
        constexpr long double EPS = 1e-16L;          // 精度补偿值
        constexpr long double BASE_OFFSET = 1.0L;   // top_count基础偏移量
        constexpr long double MIN_TOP_COUNT = 1e-16L;// top_count最小阈值
        constexpr long double MAX_TOP_COUNT = 1e18L; // top_count最大阈值

        //  1. 过滤活跃选项
        // 存储<原列表索引, 选项>对，避免索引错位
        std::vector<std::pair<size_t, Base::OptionItem>> active_options;
        for (size_t idx = 0; idx < optionList.size(); ++idx) {
            const auto& opt = optionList[idx];
            if (opt.getWeight() > 0) { // 过滤权重>0的活跃选项
                active_options.emplace_back(idx, opt);
            }
        }

        // 无活跃选项返回空对象
        if (active_options.empty()) {
            return Base::OptionItem(); // 适配你实际的空对象构造方式
        }

        //  2. 提取核心数据
        std::vector<long double> active_weights;
        std::vector<long double> selected_times;
        active_weights.reserve(active_options.size());
        selected_times.reserve(active_options.size());

        for (const auto& opt : active_options | std::views::values) {
            active_weights.push_back(static_cast<long double>(opt.getWeight()));
            selected_times.push_back(static_cast<long double>(opt.getSelectedTimes()));
        }

        //  3. 计算权重平均值 
        const long double total_weight = std::accumulate(
            active_weights.begin(), active_weights.end(), 0.0L);
        const long double avg_weight = total_weight / active_weights.size();

        //  4. 计算动态被抽取次数 
        std::vector<long double> dynamic_scores;
        dynamic_scores.reserve(active_options.size());
        for (size_t i = 0; i < active_options.size(); ++i) {
            dynamic_scores.push_back(
                selected_times[i] * avg_weight / (active_weights[i] + EPS)
            );
        }

        //  5. 计算统计量（max/avg/std）
        const long double max_count = *std::ranges::max_element(dynamic_scores);
        const long double total_count = std::accumulate(
            dynamic_scores.begin(), dynamic_scores.end(), 0.0L);
        const long double avg_count = total_count / dynamic_scores.size();

        // 计算标准差
        long double std_sum = 0.0L;
        for (const long double val : dynamic_scores) {
            std_sum += std::pow(val - avg_count, 2.0L);
        }
        const long double std_value = std::sqrt(std_sum / dynamic_scores.size());

        //  6. 计算top_count
        long double top_count = max_count + BASE_OFFSET + smoothing_factor
                             * (max_count + avg_count) * (std_value + EPS) / (avg_count + EPS);
        // 限制top_count范围，避免异常值导致逻辑失效
        top_count = std::clamp(top_count, MIN_TOP_COUNT, MAX_TOP_COUNT);

        //  7. 计算偏差度、平均偏差、移位因子 
        std::vector<long double> degree_of_deviation;
        degree_of_deviation.reserve(active_options.size());
        for (const long double ds : dynamic_scores) {
            long double deviation = top_count - ds;
            deviation = std::max(deviation, 0.0L); // 确保非负
            degree_of_deviation.push_back(deviation);
        }

        const long double total_deviation = std::accumulate(
            degree_of_deviation.begin(), degree_of_deviation.end(), 0.0L);
        const long double avg_deviation = total_deviation / degree_of_deviation.size();

        std::vector<long double> shift_factors;
        shift_factors.reserve(active_options.size());
        for (const long double deviation : degree_of_deviation) {
            shift_factors.push_back(
                std::pow(deviation / (avg_deviation + EPS), power_factor)
            );
        }

        //  8. 计算调整后权重
        std::vector<long double> adjusted_weights;
        adjusted_weights.reserve(active_options.size());
        for (size_t i = 0; i < active_options.size(); ++i) {
            long double adj_w = shift_factors[i] * active_weights[i];
            adj_w = std::max(adj_w, EPS); // 避免权重为0
            adjusted_weights.push_back(adj_w);
        }

        //  9. 随机数生成
        // 所有静态变量均在函数内定义，无外部依赖
        static std::mt19937 gen;
        static std::once_flag gen_init_flag;
        static std::mutex rng_mutex;

        // 初始化随机数生成器
        std::call_once(gen_init_flag, []() {
            // 混合真随机数+系统时间+线程ID，提升各平台随机性
            std::random_device rd;
            uint64_t seed_data[std::mt19937::state_size];
            std::generate_n(seed_data, std::mt19937::state_size, [&]() {
                return static_cast<uint64_t>(rd()) ^
                       static_cast<uint64_t>(std::chrono::steady_clock::now().time_since_epoch().count()) ^
                       static_cast<uint64_t>(std::hash<std::thread::id>{}(std::this_thread::get_id()));
            });
            std::seed_seq seq(std::begin(seed_data), std::end(seed_data));
            gen.seed(seq);
        });

        //  10. 线程安全的随机选择 
        std::lock_guard<std::mutex> lock(rng_mutex);
        std::discrete_distribution<size_t> dist(adjusted_weights.begin(), adjusted_weights.end());
        const size_t active_idx = dist(gen);

        //  11. 索引校验
        const size_t original_idx = active_options[active_idx].first;
        // 最终容错：确保索引有效
        if (original_idx >= optionList.size()) {
            return Base::OptionItem();
        }
        return optionList[original_idx];
    }
};


} // namespace CoreCalculation