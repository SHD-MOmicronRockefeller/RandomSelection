#ifndef VARIABLES_H
#define VARIABLES_H

// 常量//////////////////////////////////////////////////////////////////////////////////////////////
namespace Variables{
    const int WINDOW_WIDTH = 700;
    const int WINDOW_HEIGHT = 300 + 30;
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

#endif // VARIABLES_H