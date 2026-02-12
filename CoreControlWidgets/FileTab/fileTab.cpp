#include "fileTab.h"

#include "BaseWidgets/BaseTab/ControlList.h"
#include "BaseWidgets/BaseTab/BaseTab.h"

CoreControlWidgets::FileTab::FileTab(QWidget *parent): BaseWidgets::BaseTab(parent)
{
    this->controlList->pushLabel(new QLabel("编辑："));
    this->controlList->pushButton(new QPushButton("文件编辑"));
    this->controlList->pushButton(new QPushButton("基本语法"));
    this->controlList->pushButton(new QPushButton("常用函数"));
}