#include "settingTab.h"

#include "BaseWidgets/BaseTab/ControlList.h"
#include "BaseWidgets/BaseTab/BaseTab.h"

CoreControlWidgets::SettingTab::SettingTab(QWidget *parent): BaseWidgets::BaseTab(parent)
{
    this->controlList->pushLabel(new QLabel("设置"));
    this->controlList->pushButton(new QPushButton("基础设置"));
    this->controlList->pushButton(new QPushButton("高级设置"));
    this->controlList->pushButton(new QPushButton("开发者设置"));
}