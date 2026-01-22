#include "aboutTab.h"

CoreControlWidgets::AboutTab::AboutTab(QWidget *parent): BaseWidgets::BaseTab(parent)
{
    this->controlList->pushLable(new QLabel("关于："));
    this->controlList->pushButton(new QPushButton("关于软件"));
    this->controlList->pushButton(new QPushButton("软件更新"));
    this->controlList->pushButton(new QPushButton("更新日志"));
}