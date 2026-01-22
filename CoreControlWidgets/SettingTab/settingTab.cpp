#include "settingTab.h"

CoreControlWidgets::SettingTab::SettingTab(QWidget *parent): BaseWidgets::BaseTab(parent)
{
    this->controlList->pushLable(new QLabel("设置"));
    this->controlList->pushButton(new QPushButton("基础设置"));
    this->controlList->pushButton(new QPushButton("高级设置"));
    this->controlList->pushButton(new QPushButton("开发者设置"));
}