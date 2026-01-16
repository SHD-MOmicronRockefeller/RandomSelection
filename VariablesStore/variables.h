#ifndef VARIABLES_H
#define VARIABLES_H

// Application variables
#include "ApplicationClass/applicationShell.h"
namespace Variables{
extern ApplicationClass::ApplicationShell* applicationShell;
}

// 主窗口
#include "CoreControlWidgets/MainWindow/mainWindow.h"
namespace Variables{
extern CoreControlWidgets::MainWindowShell* mainWindowShell;
}


#endif // VARIABLES_H