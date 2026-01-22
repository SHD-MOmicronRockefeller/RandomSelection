#include "Initialization.h"

namespace Initialization {

void initialize_values()
{

    Variables::selectTab = new CoreControlWidgets::SelectTab();        //初始化选择标签页
    Variables::fileTab = new CoreControlWidgets::FileTab();            //初始化文件标签页
    Variables::settingTab = new CoreControlWidgets::SettingTab();      //初始化设置标签页
    Variables::aboutTab = new CoreControlWidgets::AboutTab();          //初始化更多标签页

    Variables::customTitleBar = new CoreControlWidgets::MainWindow::CustomTitleBar(Variables::mainWindowShell);//初始化自定义标题栏

    Variables::mainWindowShell = new CoreControlWidgets::MainWindowShell();//初始化主窗口
    Variables::statusBar = new CoreControlWidgets::MainWindow::StatusBar();//初始化状态栏
}

void initialize_settings()
{
    Variables::mainWindowShell->resize(Variables::WINDOW_WIDTH, Variables::WINDOW_HEIGHT);
    Variables::mainWindowShell->show();

    // 设置默认选择页面
    Variables::mainWindowShell->m_centralLayout->addWidget(Variables::selectTab);
    Variables::thisTabWidget = Variables::selectTab;

    //添加状态栏
    Variables::mainWindowShell->m_titleLayout->addWidget(Variables::statusBar);
    Variables::statusBar->addLeftWidget(new QLabel("__状态栏左侧__"));
    Variables::statusBar->addRightWidget(new QLabel("__状态栏右侧__"));
}

} // namespace Initialization