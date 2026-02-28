//
// Created by Administrator on 2026/2/17.
//

#include "slcf_midBox.h"
#include "CoreCalculation/ToolBox/cleanLayout.hpp"

CoreControlWidgets::SelectTab_NS::importButton::importButton(QWidget* parent) {
    this->setStyleSheet(R"(
        QPushButton {
            background-color: #f3f8ff;
            border-radius: 5px;
            color: black;
            font: 14px;
            text-align: left;
            padding-left: 5px;
            padding-top: 4px;
            padding-bottom: 4px;
        }
        QPushButton:hover {
            background-color: #99c5ff;
        }
    )");
}

CoreControlWidgets::SelectTab_NS::Slcf_midBox::Slcf_midBox(QWidget* parent)
    : QGroupBox(parent) {
    init();
}

CoreControlWidgets::SelectTab_NS::Slcf_midBox::Slcf_midBox(QString title, QWidget* parent)
    : QGroupBox(title, parent)  {
    init();
}

void CoreControlWidgets::SelectTab_NS::Slcf_midBox::init() {
    mainLayout = new QVBoxLayout();
    this->setLayout(mainLayout);
    mainLayout->setContentsMargins(2, 3, 2, 0);
    mainLayout->setSpacing(0);
    mainLayout->setAlignment(Qt::AlignTop);
}

void CoreControlWidgets::SelectTab_NS::Slcf_midBox::cleanButton() {
    MYFUNCTION::CleanLayout() << mainLayout;
}

void CoreControlWidgets::SelectTab_NS::Slcf_midBox::addButton(CoreCalculation::readDirt::_file file) {
    importButton* button = new importButton(this);
    button->file = file;
    button->setText(file.fileName);
    mainLayout->addWidget(button);
}

