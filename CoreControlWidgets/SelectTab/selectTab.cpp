#include "selectTab.h"

CoreControlWidgets::SelectTab::SelectTab(QWidget *parent) : BaseWidgets::BaseTab(parent)
{
    this->select_page = new SelectTab_NS::Select_Page();
    this->selectFile_page = new SelectTab_NS::SelectFile_Page();
    // ========== 1. 原有controlList逻辑（保留） ==========
    this->controlList->pushLable(new QLabel("选择："));
    
    QPushButton* randomSelectButton = new QPushButton("随机选择");
    connect(randomSelectButton, &QPushButton::clicked, this, [=, this](){
        this->setPage(this->select_page);
    });
    this->controlList->pushButton(randomSelectButton);
    
    QPushButton* fileSelectButton = new QPushButton("文件选择");
    connect(fileSelectButton, &QPushButton::clicked, this, [=, this](){
        this->setPage(this->selectFile_page);
    });
    this->controlList->pushButton(fileSelectButton);
    
    QPushButton* listSettingButton = new QPushButton("列表设置");
    this->controlList->pushButton(listSettingButton);
    
    QPushButton* basicSettingButton = new QPushButton("基本设置");
    this->controlList->pushButton(basicSettingButton);
    
    
    
    this->setPage(this->select_page);
}

CoreControlWidgets::SelectTab::~SelectTab()
{

}