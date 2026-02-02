#include "QtPrecompiled.h"
// #include "VariablesStore/variables.h"
#include "VariablesStore/globalVariables.h"
#include "VariablesStore/Initialization.h"

#include "ApplicationClass/applicationShell.h"

int main(int argc, char* argv[]){
    ApplicationClass::ApplicationShell* app = new ApplicationClass::ApplicationShell(argc, argv);
    GlobalVariables::getInstance()->application_shell = app;
    
    // 初始化变量
    Initialization::initialize_values();

    // 初始化设置
    Initialization::initialize_settings();

    // 运行应用程序
    GlobalVariables::getInstance()->application_shell->exec();

    return 0;
}
