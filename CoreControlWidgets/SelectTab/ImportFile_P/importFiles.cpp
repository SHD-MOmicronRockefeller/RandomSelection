#include "importFiles.h"

#include <windows.h>

#include "IPT_base.h"

#include "CoreCalculation/DoubleFileClass/ReadFile/readFile.h"
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
    PushTask([=]() mutable {
        // 读取文件并发送结果
        CoreCalculation::readFile().readByPath(filePath);
        qDebug() << "ImportFileToSelect: " << filePath;
    });
}

void CoreControlWidgets::SelectTab_NS::ImportFile_Page::ImportFileToList(QString filePath)
{
    PushTask([=]() mutable {
        CoreCalculation::readFile().readByPath(filePath);
        qDebug() << "ImportFileToList: " << filePath;
    });
}
