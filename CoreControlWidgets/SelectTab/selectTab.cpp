#include "selectTab.h"

CoreControlWidgets::SelectTab::SelectTab(QWidget *parent) : BaseWidgets::BaseTab(parent)
{
    this->controlList->pushLable(new QLabel("SelectTabLabel"));
    this->controlList->pushButton(new QPushButton("SelectTabButton1"));
    this->controlList->pushButton(new QPushButton("SelectTabButton2"));
    this->controlList->pushButton(new QPushButton("SelectTabButton3"));
}