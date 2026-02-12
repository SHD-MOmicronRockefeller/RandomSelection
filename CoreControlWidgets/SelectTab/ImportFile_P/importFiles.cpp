#include "importFiles.h"

#include <windows.h>

#include "IPT_base.h"

#include "CoreCalculation/DoubleFileClass/ReadFile/ImportFile.h"
#include "CoreCalculation/SelectTabFunc/OptionList.hpp"

#include "Console/console.h"
#include "VariablesStore/globalVariables.h"

CoreControlWidgets::SelectTab_NS::ImportFile_Page::ImportFile_Page(QWidget *parent): QWidget(parent)
{
    this->m_centerLayout = new QVBoxLayout(this);

    this->m_topWidget = new QHBoxLayout();
    this->m_centerLayout->addLayout(this->m_topWidget, 1);

    this->IPT_FileToSelect = new IPT_Base("IPT_FileToSelect", this->ImportFileToSelect);
    IPT_FileToSelect->setDefaultText("< 直接进行选择 >");
    IPT_FileToSelect->setTargetText ("> 直接进行选择 <");
    this->m_topWidget->addWidget(IPT_FileToSelect, 1);

    this->IPT_FileToList = new IPT_Base("IPT_FileToList", this->ImportFileToList);
    IPT_FileToList->setDefaultText("< 加入临时列表 >");
    IPT_FileToList->setTargetText ("> 加入临时列表 <");
    this->m_topWidget->addWidget(IPT_FileToList, 1);

    this->IPT_BouthDouble = new IPT_Base("IPT_BouthDouble", [this](QString filePath){
        this->ImportFileToSelect(filePath);
        this->ImportFileToList(filePath);
    });
    IPT_BouthDouble->setDefaultText("< 加入列表 进行选择 >");
    IPT_BouthDouble->setTargetText ("> 加入列表 进行选择 <");
    this->m_centerLayout->addWidget(IPT_BouthDouble, 1);
}

void CoreControlWidgets::SelectTab_NS::ImportFile_Page::ImportFileToSelect(QString filePath)
{
    qDebug() << "ImportFileToSelect: " << filePath;
    // CoreCalculation::RsolProcessor().readOptionList(filePath).print();

    Task task_1 = newTask;
    // 创建新任务并发送到后台线程
    PushTask( 
        // 读取文件并发送结果
        const auto optionList = CoreCalculation::RsolProcessor().readOptionList(filePath);
        SendResult(task_1, optionList);
    );
    // 接受结果并显示
    ReturnTask(task_1,[=](){
        // 读取结果并显示
        const auto gv = GlobalVariables::getInstance();
        gv->base_option_list = GetResult(CoreCalculation::OptionList);
        gv->base_option_list.print();
        gv->is_import_file = true;
    });
}

void CoreControlWidgets::SelectTab_NS::ImportFile_Page::ImportFileToList(QString filePath)
{
    qDebug() << "ImportFileToList: " << filePath;
    CoreCalculation::RsolProcessor().readOptionList(filePath).print();
}
