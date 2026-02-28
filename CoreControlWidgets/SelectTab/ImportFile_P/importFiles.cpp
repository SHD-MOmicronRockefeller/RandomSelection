#include "importFiles.h"

#include <windows.h>

#include "IPT_base.h"

#include "CoreCalculation/DoubleFileClass/ReadFile/readFile.h"
#include "CoreCalculation/SelectTabFunc/OptionList.hpp"

#include "Console/console.h"
#include "CoreControlWidgets/SelectTab/ListSet_P/listSet.h"
#include "VariablesStore/globalVariables.h"
#include "CoreCalculation/DoubleFileClass/ReadFile/readFile.h"
#include "CoreControlWidgets/SelectTab/SelectFile_P/selectFile.h"
#include "CoreControlWidgets/SelectTab/SelectFile_P/slcf_midBox.h"


CoreControlWidgets::SelectTab_NS::ImportFile_Page::ImportFile_Page(QWidget *parent): QWidget(parent)
{
    this->m_stackedWidget = new QStackedWidget();
    // 文件导入
    this->m_fileLayout = new QVBoxLayout();

    this->m_fileTopWidget = new QHBoxLayout();
    this->m_fileLayout->addLayout(this->m_fileTopWidget, 1);

    this->IPT_FileToSelect = new IPT_Base("IPT_FileToSelect", this->ImportFileToSelect);
    IPT_FileToSelect->setDefaultText("< 直接进行选择 >");
    IPT_FileToSelect->setTargetText ("> 直接进行选择 <");
    this->m_fileTopWidget->addWidget(IPT_FileToSelect, 1);

    this->IPT_FileToList = new IPT_Base("IPT_FileToList", this->ImportFileToList);
    IPT_FileToList->setDefaultText("< 加入临时列表 >");
    IPT_FileToList->setTargetText ("> 加入临时列表 <");
    this->m_fileTopWidget->addWidget(IPT_FileToList, 1);

    this->IPT_FileBouthDouble = new IPT_Base("IPT_BouthDouble", [this](QString filePath){
        this->ImportFileToSelect(filePath);
        this->ImportFileToList(filePath);
    });
    IPT_FileBouthDouble->setDefaultText("< 加入列表 进行选择 >");
    IPT_FileBouthDouble->setTargetText ("> 加入列表 进行选择 <");
    this->m_fileLayout->addWidget(IPT_FileBouthDouble, 1);


    // 文件夹导入
    this->m_dirt_layout = new QVBoxLayout();
    IPT_DirtToList = new IPT_Base("IPT_DirtToList", this->ImportDirtToList);
    this->m_dirt_layout->addWidget(IPT_DirtToList, 1);
    IPT_DirtToList->setDefaultText("< 加入临时列表 >");
    IPT_DirtToList->setTargetText ("> 加入临时列表 <");

    // 放入容器
    QWidget* fileWidget = new QWidget();
    fileWidget->setLayout(this->m_fileLayout);
    this->m_stackedWidget->addWidget(fileWidget);

    QWidget* dirtWidget = new QWidget();
    dirtWidget->setLayout(this->m_dirt_layout);
    this->m_stackedWidget->addWidget(dirtWidget);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(this->m_stackedWidget, 1);    // 设置主布局
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    setLayout(mainLayout);
}

void CoreControlWidgets::SelectTab_NS::ImportFile_Page::changeToFilePage() {
    this->m_stackedWidget->setCurrentIndex(0);
}

void CoreControlWidgets::SelectTab_NS::ImportFile_Page::changeToDirtPage() {
    this->m_stackedWidget->setCurrentIndex(1);
}

void CoreControlWidgets::SelectTab_NS::ImportFile_Page::ImportDirtToList(QString filePath) {
    Task task = newTask;
    PushTask([=]() mutable {
        // 读取文件夹并发送结果
        auto result = CoreCalculation::readDirt().getFilesBySuffix(filePath, "");
        SendResultFinally(task, result);
    });
    ReturnTask(task, [=]() {
        MessageTipManager::getInstance().addMessage("已添加文件夹至临时列表", false, 2000);
        GlobalVariables* gv = GLOBAL_VARIABLES;
        auto fileList = GetResult(QList<CoreCalculation::readDirt::_file>);
        for (auto file : fileList) {
            qDebug() << "ImportDirtToList: " << file.filePath << " | " << file.fileName;
        }
    });
}

void CoreControlWidgets::SelectTab_NS::ImportFile_Page::ImportFileToSelect(QString filePath)
{
    Task task = newTask;
    PushTask([=]() mutable {
        // 读取文件并发送结果
        auto result = CoreCalculation::readFile().readByPath(filePath);
        qDebug() << "ImportFileToSelect: " << filePath;
        SendResultFinally(task, result);
    });
    ReturnTask(task, [=]() {
        MessageTipManager::getInstance().addMessage("已添加文件至选择列表", false, 2000);
        GlobalVariables* gv = GLOBAL_VARIABLES;
        gv->select_tab->listSet_page->setOptionList(gv->base_option_list);
    });
}

void CoreControlWidgets::SelectTab_NS::ImportFile_Page::ImportFileToList(QString filePath)
{
    using File = CoreCalculation::readDirt::_file;
    using RD = CoreCalculation::readDirt;

    File file = RD().pathToFile(filePath);
    GlobalVariables* gv = GLOBAL_VARIABLES;
    gv->select_tab->selectFile_page->m_tempFileGroupBox->addButton(file);
}
