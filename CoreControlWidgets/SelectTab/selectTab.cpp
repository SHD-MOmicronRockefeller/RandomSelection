#include "selectTab.h"

CoreControlWidgets::SelectTab::SelectTab(QWidget *parent) : BaseWidgets::BaseTab(parent)
{
    // ========== 1. 原有controlList逻辑（保留） ==========
    this->controlList->pushLable(new QLabel("选择："));
    this->controlList->pushButton(new QPushButton("文件选择"));
    this->controlList->pushButton(new QPushButton("随机选择"));
    this->controlList->pushButton(new QPushButton("列表设置"));
    this->controlList->pushButton(new QPushButton("基本设置"));

    this->select_page = new SelectTab_NS::Select_Page();
    this->m_centerLayout->addWidget(this->select_page);
}

CoreControlWidgets::SelectTab::~SelectTab()
{

}
