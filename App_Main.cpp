#include "QtPrecompiled.h"
// #include "VariablesStore/variables.h"
#include "VariablesStore/globalVariables.h"
#include "VariablesStore/Initialization.h"

#include "ApplicationClass/applicationShell.h"

int main(int argc, char* argv[]){
    system("chcp 65001"); // 设置编码为UTF-8
    // 创建应用程序实例
    GlobalVariables::getInstance()->application_shell = new ApplicationClass::ApplicationShell(argc, argv);
    
    // 初始化变量
    Initialization::initialize_values();

    // 初始化设置
    Initialization::initialize_settings();

    // 运行应用程序
    GlobalVariables::getInstance()->application_shell->exec();

    return 0;
}