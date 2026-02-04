#include "minWindowShell.h"

#include "CoreControlWidgets/SelectTab/Select_P/slc_midWidget.h"
#include "BaseWidgets/BaseCoreWidget/AspectRatioWidget.h"
#include "CoreControlWidgets/MainWindow/CustomTitleBar/CustomTitleBar.h"

#include "VariablesStore/globalVariables.h"

namespace CoreControlWidgets
{

MinWindow::MinWindowShell::MinWindowShell(QWidget *parent): QWidget(parent)
{
    this->m_customTitleBar = GlobalVariables::getInstance()->min_custom_title_bar;
    this->m_midWidget = new CoreControlWidgets::SelectTab_NS::MidWidget();
    this->m_aspectRatioWidget = new BaseWidgets::AspectRatioWidget(this, GlobalVariables::getInstance()->mid_window_porportion);

    this->setAutoFillBackground(true);
    this->setAttribute(Qt::WA_StyledBackground, true);

    this->m_centralLayout = new QVBoxLayout(this);// 标题栏layout 用于显示title bar
    this->m_centralLayout->setContentsMargins(0, 0, 0, 0);// 设置边距为0
    this->m_centralLayout->setSpacing(0);// 设置间距为0

    this->m_centralLayout->addWidget(this->m_customTitleBar); // 添加自定义标题栏

    this->m_aspectRatioWidget->setContentWidget(this->m_midWidget); // 设置中间比例容器的内容为中间控件

    this->m_centralLayout->addWidget(this->m_aspectRatioWidget); // 添加宽高比控件

    this->setObjectName("MinWindowShell");
    // this->setStyleSheet("background-color: rgb(211, 229, 247);"); // 设置背景颜色
    this->setStyleSheet(R"(
        QWidget#MinWindowShell{
            background-color: rgb(211, 229, 247);
        }
    )");
}

} // namespace CoreControlWidgets