#include "fileTab.h"

CoreControlWidgets::FileTab::FileTab(QWidget *parent): BaseWidgets::BaseTab(parent)
{
    this->controlList->pushLable(new QLabel("FileTabLabel"));
    this->controlList->pushButton(new QPushButton("FileTabButton1"));
    this->controlList->pushButton(new QPushButton("FileTabButton2"));
    this->controlList->pushButton(new QPushButton("FileTabButton3"));
}