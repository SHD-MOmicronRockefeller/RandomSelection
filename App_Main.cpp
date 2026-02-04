#include "QtPrecompiled.h"
// #include "VariablesStore/variables.h"
#include "VariablesStore/globalVariables.h"
#include "VariablesStore/Initialization.h"

#include "ApplicationClass/applicationShell.h"

int main(int argc, char* argv[]){
//  Initialization ApplicationShell
    {
        ApplicationClass::ApplicationShell* app = new ApplicationClass::ApplicationShell(argc, argv);
        GlobalVariables::getInstance()->application_shell = app;
        app = nullptr;
    }

    // 初始化变量
    Initialization::initialize_values();

    // 初始化设置
    Initialization::initialize_settings();

    // 事件循环启动后执行的代码
    Initialization::after_event_loop_started();

    // 运行应用程序
    GlobalVariables::getInstance()->application_shell->exec();

    return 0;
}
