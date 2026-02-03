#include "QtPrecompiled.h"
// #include "VariablesStore/variables.h"
#include "VariablesStore/globalVariables.h"
#include "VariablesStore/Initialization.h"

#include "ApplicationClass/applicationShell.h"

int main(int argc, char* argv[]){
    ApplicationClass::ApplicationShell* app = new ApplicationClass::ApplicationShell(argc, argv);
    GlobalVariables::getInstance()->application_shell = app;
    app = nullptr;

    // 初始化变量
    Initialization::initialize_values();

    // 初始化设置
    Initialization::initialize_settings();

    // 事件循环启动后执行的代码
    QTimer::singleShot(200, []() {
        MessageTipManager::getInstance().addMessage(QString("欢迎使用 Random Selection [别急，我马上走]"), false)
            ->setBackgroundColor(MorandiPink)
            ->setTextColor(FontColor1);
    });

    // 运行应用程序
    GlobalVariables::getInstance()->application_shell->exec();

    return 0;
}
