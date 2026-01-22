#include "fileTab.h"

CoreControlWidgets::FileTab::FileTab(QWidget *parent): BaseWidgets::BaseTab(parent)
{
    this->controlList->pushLable(new QLabel("编辑："));
    this->controlList->pushButton(new QPushButton("文件编辑"));
    this->controlList->pushButton(new QPushButton("基本语法"));
    this->controlList->pushButton(new QPushButton("常用函数"));
}