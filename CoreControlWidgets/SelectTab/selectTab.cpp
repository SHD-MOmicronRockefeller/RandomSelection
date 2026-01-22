#include "selectTab.h"

CoreControlWidgets::SelectTab::SelectTab(QWidget *parent) : BaseWidgets::BaseTab(parent)
{
    this->controlList->pushLable(new QLabel("选择："));
    this->controlList->pushButton(new QPushButton("文件选择"));
    this->controlList->pushButton(new QPushButton("随机选择"));
    this->controlList->pushButton(new QPushButton("列表设置"));
    this->controlList->pushButton(new QPushButton("基本设置"));
}