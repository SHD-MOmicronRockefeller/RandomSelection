#ifndef VARIABLES_H
#define VARIABLES_H

// 常量//////////////////////////////////////////////////////////////////////////////////////////////
namespace Variables{
    const int WINDOW_WIDTH = 700;
    const int WINDOW_HEIGHT = 350 + 30;
}



// Application variables/////////////////////////////////////////////////////////////////////////////
#include "ApplicationClass/applicationShell.h"
namespace ApplicationClass {
class ApplicationShell;
} 
namespace Variables{
extern ApplicationClass::ApplicationShell* applicationShell;
}



// 主窗口///////////////////////////////////////////////////////////////////////////////////////////
#include "CoreControlWidgets/MainWindow/mainWindow.h"
namespace CoreControlWidgets {
    class MainWindowShell; 
}
namespace Variables{
extern CoreControlWidgets::MainWindowShell* mainWindowShell;
}



// 工具栏//////////////////////////////////////////////////////////////////////////////////////////
#include "CoreControlWidgets/MainWindow/CustomTitleBar/CustomTitleBar.h"
namespace CoreControlWidgets {
    namespace MainWindow {
        class CustomTitleBar;
    }
}
namespace Variables{
extern CoreControlWidgets::MainWindow::CustomTitleBar* customTitleBar;
}

// 状态栏//////////////////////////////////////////////////////////////////////////////////////////
#include "CoreControlWidgets/MainWindow/StatusBar/statusBar.h"
namespace CoreControlWidgets {
    namespace MainWindow {
        class StatusBar;
    }
}
namespace Variables{
extern CoreControlWidgets::MainWindow::StatusBar* statusBar;
}

// 选择页面/////////////////////////////////////////////////////////////////////////////////////////
#include "CoreControlWidgets/SelectTab/selectTab.h"
namespace CoreControlWidgets {
    class SelectTab;
}
namespace Variables{
extern CoreControlWidgets::SelectTab* selectTab;
}

// 文件页面/////////////////////////////////////////////////////////////////////////////////////////
#include "CoreControlWidgets/FileTab/fileTab.h"
namespace CoreControlWidgets {
    class FileTab;
}
namespace Variables{
extern CoreControlWidgets::FileTab* fileTab;
}

// 设置页面/////////////////////////////////////////////////////////////////////////////////////////
#include "CoreControlWidgets/SettingTab/settingTab.h"
namespace CoreControlWidgets {
    class SettingTab;
}
namespace Variables{
extern CoreControlWidgets::SettingTab* settingTab;
}

// 更多页面/////////////////////////////////////////////////////////////////////////////////////////
#include "CoreControlWidgets/AboutTab/aboutTab.h"
namespace CoreControlWidgets {
    class AboutTab;
}
namespace Variables{
extern CoreControlWidgets::AboutTab* aboutTab;
}

// 其他变量/////////////////////////////////////////////////////////////////////////////////////////

namespace Variables{
    extern QWidget* thisTabWidget;
}

#endif // VARIABLES_H