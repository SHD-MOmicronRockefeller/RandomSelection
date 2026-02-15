//
// Created by Administrator on 2026/2/14.
//

#include "readFile.h"
#include "CoreCalculation/SelectTabFunc/OptionList.hpp"
#include "VariablesStore/globalVariables.h"

namespace CoreCalculation {
    void readFile::readByPath(const QString& path) {
        GlobalVariables* gv = GlobalVariables::getInstance();
        OptionList optionList = RsolProcessor(false).readOptionList(path);

        // 添加选项列表
        gv->base_option_list = optionList;
        gv->current_option_list = optionList;
        gv->active_option_list = optionList;

        // 计算文件量
        gv->total_weight = std::accumulate(optionList.begin(), optionList.end(), 0.0L,
            [](long double sum, const Base::OptionItem& option) {
                return sum + option.getWeight();
        });
        // 标记已导入文件
        gv->is_import_file = true;

        gv->total_select_count = 0;
    }

    void readFile::readByStr(const QString& str) {
    }
} // CoreCalculation