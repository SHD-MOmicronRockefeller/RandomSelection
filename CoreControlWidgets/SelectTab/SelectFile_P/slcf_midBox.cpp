//
// Created by Administrator on 2026/2/17.
//

#include "slcf_midBox.h"

CoreControlWidgets::SelectTab_NS::importButton::importButton(QWidget* parent) {

}

CoreControlWidgets::SelectTab_NS::slcf_midBox::slcf_midBox(QWidget* parent) : QGroupBox(parent)
{
    return;
}

CoreControlWidgets::SelectTab_NS::slcf_midBox::slcf_midBox(QString title, QWidget* parent) : QGroupBox(title, parent)
{
}

void CoreControlWidgets::SelectTab_NS::slcf_midBox::init() {
    mainLayout = new QVBoxLayout(this);
    this->setLayout(mainLayout);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);


}
