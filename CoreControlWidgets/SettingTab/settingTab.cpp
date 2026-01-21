#include "settingTab.h"

CoreControlWidgets::SettingTab::SettingTab(QWidget *parent): BaseWidgets::BaseTab(parent)
{
    this->controlList->pushLable(new QLabel("SettingTabLabel"));
    this->controlList->pushButton(new QPushButton("SettingTabButton1"));
    this->controlList->pushButton(new QPushButton("SettingTabButton2"));
    this->controlList->pushButton(new QPushButton("SettingTabButton3"));
}