#include "ToggleTopmost.h"

#include "VariablesStore/globalVariables.h"

#include "CoreCalculation/Application/SignalSource.h"

#include "BaseWidgets/BaseCoreWidget/MessageTipWidget.h"

ModWidgets::ToggleTopmost::ToggleTopmost(QWidget *parent): QPushButton(parent)
{
    connect(this, QPushButton::clicked, this, [this](){
        this->changeWindowTopmost();
        if (GlobalVariables::getInstance()->is_settop_window)
            MessageTipManager::getInstance().addMessage(QString("窗口已 置顶"), false, 1000);
        else 
            MessageTipManager::getInstance().addMessage(QString("窗口已 取消 置顶"), false, 1000);
        emit SignalSource::getInstance()->WindowTopmostToggled();

        this->setEnabled(false);
        QTimer::singleShot(333, [this](){
            this->setEnabled(true);
        });
    });
    connect(SignalSource::getInstance(), SignalSource::WindowTopmostToggled, this, [this](){
        this->changeColor();
    });

    this->setText(QString("置顶窗口"));

    this->setFixedSize(100, 45);
    this->setFont(QFont("Microsoft YaHei", 14));
}

void ModWidgets::ToggleTopmost::changeWindowTopmost()
{
    GlobalVariables *gv = GlobalVariables::getInstance();
    if (gv->is_settop_window) {
        gv->is_settop_window = false;
        // 取消置顶
        gv->main_window_shell->windowHandle()->setFlag(Qt::WindowStaysOnTopHint, false);
    } else {
        gv->is_settop_window = true;
        // 置顶
        gv->main_window_shell->windowHandle()->setFlag(Qt::WindowStaysOnTopHint, true);
    }

}

void ModWidgets::ToggleTopmost::changeColor(){
    if (GlobalVariables::getInstance()->is_settop_window) {
        setGreenColor();
    } else {
        setRedColor();
    }
}

void ModWidgets::ToggleTopmost::setGreenColor()
{
    setStyleSheet(R"(
        QPushButton {
            background-color: rgba(16, 185, 129, 0.2);
            color: #333333;
            border: 2px solid rgba(16, 185, 129, 0.7);
            border-radius: 0px;
            padding: 0px 0px;}
        QPushButton:hover {
            background-color: rgba(251, 191, 36, 0.08);
            color: #000000;
            border: 2px solid rgba(251, 191, 36, 0.5);
            border-radius: 0px;}
        QPushButton:pressed {
            background-color: #e8e8e8;}
        QPushButton:checked {
            background-color: #e0e0e0;
            font-weight: medium;}
        QPushButton:disabled {
            background-color: rgba(200, 200, 200, 0.2);  /* 浅灰色背景 */
            color: #999999;                              /* 浅灰色文字 */
            border: 2px solid rgba(180, 180, 180, 0.5);  /* 灰色边框 */}
    )");
    this->setText(QString("取消置顶"));
}

void ModWidgets::ToggleTopmost::setRedColor()
{
    setStyleSheet(R"(
        QPushButton {
            background-color: rgba(239, 68, 68, 0.15);
            color: #333333;
            border: 2px solid rgba(239, 68, 68, 0.25);
            border-radius: 0px;
            padding: 0px 0px;}
        QPushButton:hover {
            background-color: #f0f0f0;
            color: #000000;
            border: 2px solid rgba(251, 191, 36, 0.5);
            border-radius: 0px;}
        QPushButton:pressed {
            background-color: #e8e8e8;}
        QPushButton:checked {
            background-color: #e0e0e0;
            font-weight: medium;}
        QPushButton:disabled {
            background-color: rgba(200, 200, 200, 0.2);  /* 浅灰色背景 */
            color: #999999;                              /* 浅灰色文字 */
            border: 2px solid rgba(180, 180, 180, 0.5);  /* 灰色边框 */}
    )");
    this->setText(QString("置顶窗口"));
}
