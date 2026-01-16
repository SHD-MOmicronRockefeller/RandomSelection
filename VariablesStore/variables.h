#ifndef VARIABLES_H
#define VARIABLES_H



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


#endif // VARIABLES_H