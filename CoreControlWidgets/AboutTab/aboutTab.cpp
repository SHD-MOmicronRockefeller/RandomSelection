#include "aboutTab.h"

CoreControlWidgets::AboutTab::AboutTab(QWidget *parent): BaseWidgets::BaseTab(parent)
{
    this->controlList->pushLable(new QLabel("AboutTabLabel"));
    this->controlList->pushButton(new QPushButton("AboutTabButton1"));
    this->controlList->pushButton(new QPushButton("AboutTabButton2"));
    this->controlList->pushButton(new QPushButton("AboutTabButton3"));
}