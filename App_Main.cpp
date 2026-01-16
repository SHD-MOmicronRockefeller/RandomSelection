#include "QtPrecompiled.h"
#include "VariablesStore/variables.h"
#include "Initialization/Initialization.h"

int main(int argc, char* argv[]){
    // 创建应用程序实例
    Variables::applicationShell = new ApplicationClass::ApplicationShell(argc, argv);

    // 初始化变量
    Initialization::initialize_values();

    // 初始化设置
    Initialization::initialize_settings();

    // 运行应用程序
    Variables::applicationShell->exec();

    return 0;
}