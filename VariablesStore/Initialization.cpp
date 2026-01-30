#include "Initialization.h"

#include "VariablesStore/globalVariables.h"

namespace Initialization {

void initialize_values()
{
    return;
}

void initialize_settings()
{


    GlobalVariables::getInstance()->main_window_shell->resize(GlobalVariables::getInstance()->main_window_width, GlobalVariables::getInstance()->main_window_height);
    GlobalVariables::getInstance()->main_window_shell->show();

    // 设置默认选择页面
    GlobalVariables::getInstance()->main_window_shell->m_centralLayout->addWidget(GlobalVariables::getInstance()->select_tab);
    GlobalVariables::getInstance()->this_tab_widget = GlobalVariables::getInstance()->select_tab;

    // 添加状态栏
    GlobalVariables::getInstance()->main_window_shell->m_titleLayout->addWidget(GlobalVariables::getInstance()->status_bar);
    GlobalVariables::getInstance()->status_bar->addLeftWidget(new QLabel("__状态栏左侧__"));
    GlobalVariables::getInstance()->status_bar->addRightWidget(new QLabel("__状态栏右侧__"));
}

} // namespace Initialization