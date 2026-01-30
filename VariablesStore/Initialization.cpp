#include "Initialization.h"

#include "VariablesStore/globalVariables.h"

namespace Initialization {

void initialize_values()
{
    return;
}

void initialize_settings()
{
    GlobalVariables* gv = GlobalVariables::getInstance();
    
    // 分步初始化UI成员（确保在QApplication就绪后）
    if (!gv->custom_title_bar)      gv->custom_title_bar    = new CoreControlWidgets::MainWindow::CustomTitleBar();                         // 标题栏
    if (!gv->status_bar)            gv->status_bar          = new CoreControlWidgets::MainWindow::StatusBar();                              // 状态栏
    if (!gv->select_tab)            gv->select_tab          = new CoreControlWidgets::SelectTab();                                          // 选择页面 
    if (!gv->file_tab)              gv->file_tab            = new CoreControlWidgets::FileTab();                                            // 文件页面
    if (!gv->setting_tab)           gv->setting_tab         = new CoreControlWidgets::SettingTab();                                         // 设置页面
    if (!gv->about_tab)             gv->about_tab           = new CoreControlWidgets::AboutTab();                                           // 关于页面
    if (!gv->main_window_shell)     gv->main_window_shell   = new CoreControlWidgets::MainWindowShell();                                    // 主窗口
    


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