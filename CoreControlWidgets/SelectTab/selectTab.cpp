#include "selectTab.h"

#include "BaseWidgets/BaseTab/ControlList.h"
#include "BaseWidgets/BaseTab/BaseTab.h"

#include "Hello_P/hello.h"
#include "ImportFile_P/importFiles.h"
#include "ImportFile_P/IPT_base.h"

#include "Select_P/select_P.h"
#include "SelectFile_P/selectFile.h"
#include "ListSet_P/listSet.h"
#include "BasicSet_P/basicSet.h"
#include "Memory_P/memory.h"


CoreControlWidgets::SelectTab::SelectTab(QWidget *parent) : BaseWidgets::BaseTab(parent)
{
    this->importFile_page = new SelectTab_NS::ImportFile_Page();

    this->hello_page = new SelectTab_NS::Hello_Page();
    this->select_page = new SelectTab_NS::Select_Page();
    this->selectFile_page = new SelectTab_NS::SelectFile_Page();
    this->listSet_page = new SelectTab_NS::ListSet_Page();  
    this->basicSet_page = new SelectTab_NS::BasicSet_Page();
    this->memory_page = new SelectTab_NS::Memory_Page();

    //开启拖动
    this->setAcceptDrops(true);

    // ========== 1. 原有controlList逻辑（保留） ==========
    this->controlList->pushLabel(new QLabel("选择："));

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

    QPushButton* memoryButton = new QPushButton("抽取记录");
    connect(memoryButton, &QPushButton::clicked, this, [=, this](){
        this->setPage(this->memory_page);
    });
    this->controlList->pushButton(memoryButton);
    
    
    this->setPage(this->select_page);
    // this->setPage(this->importFile_page);
}

CoreControlWidgets::SelectTab::~SelectTab()
{

}

void CoreControlWidgets::SelectTab::dragEnterEvent(QDragEnterEvent *event)
{
    this->m_isInDrag = true;
    if (m_this_widget != importFile_page)
        this->m_oldPage = this->m_this_widget;

    if (!event->mimeData()->hasUrls()) return;
    QUrl url = event->mimeData()->urls().first();
    QFileInfo fileInfo(url.toLocalFile());
    if (!fileInfo.exists()) return;
    if (!fileInfo.isFile() && !fileInfo.isDir()) return;

    if (fileInfo.isFile()) {
        this->setPage(this->importFile_page);
        event->acceptProposedAction();
    }
}

void CoreControlWidgets::SelectTab::dragLeaveEvent(QDragLeaveEvent *event)
{
    this->m_isInDrag = false;
    Q_UNUSED(event);

    QTimer::singleShot(0, [this]() {
        if (
            this->importFile_page->IPT_FileToSelect->m_isInDrag ||
            this->importFile_page->IPT_FileToList->m_isInDrag   ||
            this->importFile_page->IPT_BouthDouble->m_isInDrag
        ) return;
        if (this->m_oldPage)
            this->setPage(this->m_oldPage);
    });
}

void CoreControlWidgets::SelectTab::dropEvent(QDropEvent *event)
{
    this->m_isInDrag = false;
    Q_UNUSED(event);
    if (m_oldPage) 
        this->setPage(this->m_oldPage);
}
