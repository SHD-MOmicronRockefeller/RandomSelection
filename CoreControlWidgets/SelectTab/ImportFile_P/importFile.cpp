#include "importFile.h"

#include "IPT_base.h"

CoreControlWidgets::SelectTab_NS::ImportFile_Page::ImportFile_Page(QWidget *parent): QWidget(parent)
{
    this->m_centerLayout = new QVBoxLayout(this);

    this->m_topWidget = new QHBoxLayout();
    this->m_centerLayout->addLayout(this->m_topWidget, 1);

    this->IPT_FileToSelect = new IPT_Base("IPT_FileToSelect", this->ImportFileToSelect);
    IPT_FileToSelect->setDefaultText("> 导入到 选择区 <");
    IPT_FileToSelect->setTargetText("> 松开文件 进行选择 <");
    this->m_topWidget->addWidget(IPT_FileToSelect, 1);

    this->IPT_FileToList = new IPT_Base("IPT_FileToList", this->ImportFileToList);
    IPT_FileToList->setDefaultText("> 导入到 列表区 <");
    IPT_FileToList->setTargetText("> 松开文件 加入列表 <");
    this->m_topWidget->addWidget(IPT_FileToList, 1);

    this->IPT_BouthDouble = new IPT_Base("IPT_BouthDouble", [this](QString filePath){
        this->ImportFileToSelect(filePath);
        this->ImportFileToList(filePath);
    });
    IPT_BouthDouble->setDefaultText("> 导入到 选择区 和 列表区 <");
    IPT_BouthDouble->setTargetText("> 加入列表 进行选择 <");
    this->m_centerLayout->addWidget(IPT_BouthDouble, 1);
}

void CoreControlWidgets::SelectTab_NS::ImportFile_Page::ImportFileToSelect(QString filePath)
{
    qDebug() << "ImportFileToSelect: " << filePath;
}

void CoreControlWidgets::SelectTab_NS::ImportFile_Page::ImportFileToList(QString filePaths)
{
    qDebug() << "ImportFileToList: " << filePaths;
}
