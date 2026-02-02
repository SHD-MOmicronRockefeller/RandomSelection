#include "titleFunc.h"

#include "VariablesStore/globalVariables.h"

#include "CoreControlWidgets/MainWindow/mainWindow.h"
#include "CoreControlWidgets/MinWindowShell/minWindowShell.h"

namespace MY_FUNC {

void setMinWindow() //700 280
{
    GlobalVariables* gv = GlobalVariables::getInstance();
    
    // 空指针安全检查（避免崩溃）
    if (!gv || !gv->window_stack || !gv->min_window_widget) {
        qWarning() << "迷你窗口初始化失败，无法切换";
        return;
    }

    gv->window_stack->setCurrentIndex(1);
    gv->main_window_widget->show();
    gv->is_mini_window_showed = true;
    gv->min_custom_title_bar->onMidBtnClicked_clicked(gv->tab_index); // 切换到当前标签页

    int old_width = gv->main_window_shell->width();
    int old_height = gv->main_window_shell->height();
    int old_x = gv->main_window_shell->x();
    int old_y = gv->main_window_shell->y();
    // 2. 计算原窗口的中心坐标（关键！）
    int center_x = old_x + old_width / 2;
    int center_y = old_y + old_height / 2;

    // 保存原窗口尺寸（用于切回主窗口时还原）
    gv->window_size[0] = old_width;
    gv->window_size[1] = old_height;

    // 3. 调整迷你窗口尺寸
    const int min_width = 700;
    const int min_height = 280;
    gv->main_window_shell->resize(min_width, min_height);

    // 4. 计算新位置：中心不变 → 新左上角 = 中心坐标 - 新尺寸的一半
    int new_x = center_x - min_width / 2;
    int new_y = center_y - min_height / 2;
    gv->main_window_shell->move(new_x, new_y); // 移动到新位置
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

    if (gv->window_size[0] <= 0 || gv->window_size[1] <= 0) {
        qWarning() << "保存的窗口尺寸无效，使用默认尺寸";
        gv->window_size[0] = 1200; // 默认主窗口宽度
        gv->window_size[1] = 800;  // 默认主窗口高度
    }
    // 2. 获取迷你窗口的当前中心坐标
    int min_width = gv->main_window_shell->width();
    int min_height = gv->main_window_shell->height();
    int min_x = gv->main_window_shell->x();
    int min_y = gv->main_window_shell->y();
    int center_x = min_x + min_width / 2;
    int center_y = min_y + min_height / 2;

    // 3. 还原主窗口尺寸
    int main_width = gv->window_size[0];
    int main_height = gv->window_size[1];
    gv->main_window_shell->resize(main_width, main_height);

    // 4. 计算主窗口新位置：中心不变
    int new_x = center_x - main_width / 2;
    int new_y = center_y - main_height / 2;
    gv->main_window_shell->move(new_x, new_y); // 修正：原逻辑完全反向，已重构
}

} // namespace MY_FUNC