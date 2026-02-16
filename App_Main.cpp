#include "QtPrecompiled.h"
// #include "VariablesStore/variables.h"
#include "VariablesStore/globalVariables.h"
#include "VariablesStore/Initialization.h"

#include "ApplicationClass/applicationShell.h"
#include "Console/console.h"


int main(int argc, char* argv[])
{
    // system("chcp 65001 > nul"); // 设置编码为UTF-8

    //  Initialization ApplicationShell
    {
        GlobalVariables* gv = GLOBAL_VARIABLES;
        ApplicationClass::ApplicationShell* app = new ApplicationClass::ApplicationShell(argc, argv);
        gv->application_shell = app;
        app = nullptr;
    }

    // 初始化变量
    Initialization::initialize_values();

    // 初始化设置
    Initialization::initialize_settings();

    // 事件循环启动后执行的代码
    Initialization::after_event_loop_started();

    // 联系子进程
    QObject::connect(GlobalVariables::getInstance()->application_shell, &QApplication::aboutToQuit, []()
    {
        Console::getInstance()->deleteInstance();
    });

    // 激活子进程
    MainThreadReady();

    // 运行应用程序
    GlobalVariables::getInstance()->application_shell->exec();

    return 0;
}

// cmake -S . -B cmake-build-debug -DCMAKE_BUILD_TYPE=Debug -DCMAKE_PREFIX_PATH="D:/DownApp/QtManager/6.10.2/mingw_64"
