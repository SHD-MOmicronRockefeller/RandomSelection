#include "titleFunc.h"

#include "VariablesStore/globalVariables.h"

#include "CoreControlWidgets/MainWindow/mainWindow.h"
#include "CoreControlWidgets/MinWindowShell/minWindowShell.h"

namespace MY_FUNC {

void setMinWindow()
{
    GlobalVariables* gv = GlobalVariables::getInstance();
    
    // 空指针安全检查（避免崩溃）
    if (!gv || !gv->window_stack || !gv->min_window_widget) {
        qWarning() << "迷你窗口初始化失败，无法切换";
        return;
    }

    // 切换栈布局到迷你窗口（无父控件变更）
    gv->window_stack->setCurrentIndex(1);
    gv->min_window_widget->show(); // 确保显示
    gv->is_mini_window_showed = true;
    gv->min_custom_title_bar->onMidBtnClicked_clicked(gv->tab_index); // 切换到当前标签页
}

void setMainWindow()
{
    GlobalVariables* gv = GlobalVariables::getInstance();
    
    if (!gv || !gv->window_stack || !gv->main_window_widget) {
        qWarning() << "主窗口初始化失败，无法切换";
        return;
    }

    // 切换栈布局到主窗口
    gv->window_stack->setCurrentIndex(0);
    gv->main_window_widget->show();
    gv->is_mini_window_showed = false;
    gv->custom_title_bar->onMidBtnClicked_clicked(gv->tab_index); // 切换到当前标签页
}

} // namespace MY_FUNC