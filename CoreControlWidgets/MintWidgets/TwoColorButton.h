#pragma once
#include "QtPrecompiled.h"

namespace CoreControlWidgets
{

class TwoColorButton : public QPushButton
{
    Q_OBJECT
    public: TwoColorButton(QWidget *parent = nullptr): QPushButton(parent) {
        this->setGreenColor();
    }

    public: void setGreenColor()
    {
        setStyleSheet(this->styleSheet() + R"(
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

    public: void setRedColor()
    {
        setStyleSheet(this->styleSheet() + R"(
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

};


}
