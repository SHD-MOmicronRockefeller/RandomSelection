#include "selectTab.h"

#include "BaseWidgets/BaseTab/ControlList.h"
#include "BaseWidgets/BaseTab/BaseTab.h"

#include "Hello_P/hello.h"
#include "Select_P/select_P.h"
#include "SelectFile_P/selectFile.h"
#include "ListSet_P/listSet.h"
#include "BasicSet_P/basicSet.h"


CoreControlWidgets::SelectTab::SelectTab(QWidget *parent) : BaseWidgets::BaseTab(parent)
{
    this->hello_page = new SelectTab_NS::Hello_Page();
    this->select_page = new SelectTab_NS::Select_Page();
    this->selectFile_page = new SelectTab_NS::SelectFile_Page();
    this->listSet_page = new SelectTab_NS::ListSet_Page();  
    this->basicSet_page = new SelectTab_NS::BasicSet_Page();

    // ========== 1. 原有controlList逻辑（保留） ==========
    this->controlList->pushLable(new QLabel("选择："));

    QPushButton* helloButton = new QPushButton("Hello");
    connect(helloButton, &QPushButton::clicked, this, [=, this](){
        this->setPage(this->hello_page);
    });
    this->controlList->pushButton(helloButton);

    // 选择按钮
    QPushButton* randomSelectButton = new QPushButton("随机选择");
    connect(randomSelectButton, &QPushButton::clicked, this, [=, this](){
        this->setPage(this->select_page);
    });
    this->controlList->pushButton(randomSelectButton);
    

    // 文件选择按钮
    QPushButton* fileSelectButton = new QPushButton("文件选择");
    connect(fileSelectButton, &QPushButton::clicked, this, [=, this](){
        this->setPage(this->selectFile_page);
    });
    this->controlList->pushButton(fileSelectButton);
    

    // 列表设置按钮
    QPushButton* listSettingButton = new QPushButton("列表设置");
    connect(listSettingButton, &QPushButton::clicked, this, [=, this](){
        this->setPage(this->listSet_page);
    });
    this->controlList->pushButton(listSettingButton);
    
    QPushButton* basicSettingButton = new QPushButton("基本设置");
    connect(basicSettingButton, &QPushButton::clicked, this, [=, this](){
        this->setPage(this->basicSet_page);
    });
    this->controlList->pushButton(basicSettingButton);
    
    
    
    this->setPage(this->select_page);
}

CoreControlWidgets::SelectTab::~SelectTab()
{

}