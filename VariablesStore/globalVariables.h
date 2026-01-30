#ifndef GLOBALVARIABLES_H
#define GLOBALVARIABLES_H

#include "QtPrecompiled.h"

#include "ApplicationClass/applicationShell.h"
#include "CoreControlWidgets/MainWindow/mainWindow.h"
// namespace CoreControlWidgets { class MainWindowShell; }
#include "CoreControlWidgets/MainWindow/StatusBar/statusBar.h"
#include "CoreControlWidgets/SelectTab/selectTab.h"
#include "CoreControlWidgets/FileTab/fileTab.h"
#include "CoreControlWidgets/SettingTab/settingTab.h"
#include "CoreControlWidgets/AboutTab/aboutTab.h"


class GlobalVariables {
    // 全局访问接口声明
    public: static GlobalVariables* getInstance();
    // 安全销毁接口声明
    public: static void deleteInstance();

    private: static GlobalVariables* m_instance;
    private: static QMutex m_mutex;


    // 私有构造、析构、拷贝、赋值（仅声明）
    private: GlobalVariables() = default;
    private: ~GlobalVariables() = default;
    private: GlobalVariables(const GlobalVariables&) = delete;
    private: GlobalVariables& operator=(const GlobalVariables&) = delete;

    // 全局变量 /////////////////////////////////////////////////////////////////////////

    // 应用程序信息
    public: const QString application_name = "RandomSelection";
    public: const QString application_version = "1.0.0";
    public: const int application_setp_version = 1;

    // 主窗口信息
    public: const int main_window_width = 700;
    public: const int main_window_height = 350 + 30;

    // 数据库信息
    // public: ApplicationClass::ApplicationShell* applicationShell = nullptr;
    public: ApplicationClass::ApplicationShell* application_shell                   = nullptr;

    // 主窗口
    public: CoreControlWidgets::MainWindowShell* main_window_shell                  = new CoreControlWidgets::MainWindowShell();

    // 标题栏
    public: CoreControlWidgets::MainWindow::CustomTitleBar* custom_title_bar        = new CoreControlWidgets::MainWindow::CustomTitleBar(this->main_window_shell);
    
    // 状态栏
    public: CoreControlWidgets::MainWindow::StatusBar* status_bar                   = new CoreControlWidgets::MainWindow::StatusBar();

    // 选择页面
    public: CoreControlWidgets::SelectTab* select_tab                               = new CoreControlWidgets::SelectTab();

    // 文件页面
    public: CoreControlWidgets::FileTab* file_tab                                   = new CoreControlWidgets::FileTab();

    // 设置页面
    public: CoreControlWidgets::SettingTab* setting_tab                             = new CoreControlWidgets::SettingTab();

    // 更多页面
    public: CoreControlWidgets::AboutTab* about_tab                                 = new CoreControlWidgets::AboutTab();

    // 其他变量
    public: QWidget* this_tab_widget                                                = nullptr;
};

#endif // GLOBALVARIABLES_H
