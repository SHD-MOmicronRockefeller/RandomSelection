//
// Created by Administrator on 2026/2/26.
//

#include "listSetOption.h"

#include "ApplicationClass/Application/SignalSource.h"

static void refreshWidgetStyle(QWidget *widget) {
    if (!widget) return;
    // 强制Qt重新计算样式表
    widget->style()->unpolish(widget);
    widget->style()->polish(widget);
    // 强制重绘
    widget->update();
}

CoreControlWidgets::SelectTab_NS::ListSetOption::ListSetOption(CoreCalculation::Base::OptionItem optionItem,QWidget* parent)
    : BaseWidgets::AutoFitButton(optionItem.getContent(), 3, parent), optionItem(optionItem) {
    QObject::connect(this, &QPushButton::clicked, this, [this](){
        this->isSelected = !isSelected;
        this->changeColor();
    });

    QObject::connect(SignalSource::getInstance(), &SignalSource::SelectTab_ListSet_ChangeOption, this, [this](unsigned int index, bool isSelected){
        if (this->optionItem.getIndex() != index) return;
        this->isSelected = isSelected;
        if (this->isSelected)
            this->setGreenColor();
        else
            this->setRedColor();
        refreshWidgetStyle(this);
    });

    this->setGreenColor();
}

void CoreControlWidgets::SelectTab_NS::ListSetOption::changeColor() {
    isSelected ? setRedColor() : setGreenColor();
    this->update();
    emit SignalSource::getInstance()->SelectTab_ListSet_ChangeOption(this->optionItem.getIndex(), this->isSelected);
}

void CoreControlWidgets::SelectTab_NS::ListSetOption::setGreenColor() {
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
}

void CoreControlWidgets::SelectTab_NS::ListSetOption::setRedColor() {
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
}

void CoreControlWidgets::SelectTab_NS::ListSetOption::resizeEvent(QResizeEvent* event) {
    this->setFixedHeight(event->size().width() * 0.5);
    AutoFitButton::resizeEvent(event);
}
