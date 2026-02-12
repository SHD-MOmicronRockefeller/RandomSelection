#ifndef GLOBALVARIABLES_H
#define GLOBALVARIABLES_H

#include "QtPrecompiled.h"

#include "ClassSpace.h"

#include "ApplicationClass/applicationShell.h"
#include "CoreControlWidgets/MainWindow/mainWindow.h"
// namespace CoreControlWidgets { class MainWindowShell; }
#include "CoreControlWidgets/MainWindow/StatusBar/statusBar.h"
#include "CoreControlWidgets/SelectTab/selectTab.h"
#include "CoreControlWidgets/FileTab/fileTab.h"
#include "CoreControlWidgets/SettingTab/settingTab.h"
#include "CoreControlWidgets/AboutTab/aboutTab.h"
#include "CoreControlWidgets/MainWindow/CustomTitleBar/CustomTitleBar.h"
#include "CoreControlWidgets/MinWindowShell/minWindowShell.h"
#include "BaseWidgets/BaseCoreWidget/MessageTipWidget.h"
#include "CoreCalculation/SelectTabFunc/OptionList.hpp"
#include "CoreCalculation/SelectTabFunc/ClassType/OptionItem.hpp"


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
    public: const int main_window_width = 700; // 主窗口宽度
    public: const int main_window_height = 350 + 30; // 30为状态栏高度
    public: const double mid_window_proportion = 3.0 / 1.0; // 主窗口中部窗口的比例

    // 最大化窗口信息
    public: QSize normal_window_size = QSize(main_window_width, main_window_height); // 储存窗口最大化之前的大小
    public: bool is_max_window_showed = false; // 是否最大化窗口

    public: unsigned int tab_index = 0; // 当前标签页索引

    public: int window_size[2] = {0, 0}; // 窗口大小  用于 min 与 main 切换
    public: bool old_window_is_max = false; // 记录旧窗口是否最大化 用于 min 与 main 切换

    public: bool is_settop_window = false; // 是否置顶窗口 设置为 true 是因为后续初始化会发送置顶改变信号

    // 随机抽取信息
    public: unsigned int total_select_count = 0; // 总的抽取的数量
    public: unsigned int current_select_index = 0; // 显示抽取的索引

    public: CoreCalculation::Base::OptionItem current_option_item; // 当前选项项

    // 文件操作
    public: bool is_import_file = false; // 是否导入文件

    public: CoreCalculation::OptionList base_option_list;    // 基础选项列表
    public: CoreCalculation::OptionList current_option_list; // 当前选项列表
    public: CoreCalculation::OptionList active_option_list;  // 活动选项列表
    


    // 数据库信息
    // public: ApplicationClass::ApplicationShell* applicationShell = nullptr;
    public: ApplicationClass::ApplicationShell* application_shell                   = nullptr;

    // 窗口栈
    public: QStackedWidget* window_stack                                            =  nullptr;

    // 主窗口
    public: CoreControlWidgets::MainWindowShell* main_window_shell                  = nullptr;

    // 标题栏
    public: CoreControlWidgets::MainWindow::CustomTitleBar* custom_title_bar        = nullptr;
    
    // 状态栏
    public: CoreControlWidgets::MainWindow::StatusBar* status_bar                   = nullptr;
    
    // 主窗口Widgets
    public: QWidget* main_window_widget                                             = nullptr;

    // 迷你窗口Widgets
    public: CoreControlWidgets::MinWindow::MinWindowShell* min_window_widget        = nullptr;

    // 迷你窗口标题栏
    public: CoreControlWidgets::MainWindow::CustomTitleBar* min_custom_title_bar    = nullptr;

    // 选择页面
    public: CoreControlWidgets::SelectTab* select_tab                               = nullptr;

    // 文件页面
    public: CoreControlWidgets::FileTab* file_tab                                   = nullptr;

    // 设置页面
    public: CoreControlWidgets::SettingTab* setting_tab                             = nullptr;

    // 更多页面
    public: CoreControlWidgets::AboutTab* about_tab                                 = nullptr;

    // 其他变量
    public: QWidget* this_tab_widget                                                = nullptr;

    // 迷你窗口
    public: bool is_mini_window_showed = false;

    // 消息提示框
    // public: BaseWidgets::MessageTipWidget* message_tip_widget                    = nullptr;


};

#endif // GLOBALVARIABLES_H
