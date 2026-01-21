#include "selectTab.h"

CoreControlWidgets::SelectTab::SelectTab(QWidget *parent) : BaseWidgets::BaseTab(parent)
{
    this->controlList->pushLable(new QLabel("SelectTab"));
    this->controlList->pushButton(new QPushButton("Button1"));
    this->controlList->pushButton(new QPushButton("Button2"));
    this->controlList->pushButton(new QPushButton("Button3"));
}