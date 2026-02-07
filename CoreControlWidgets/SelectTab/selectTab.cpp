#include "selectTab.h"
#include "BaseWidgets/BaseTab/ControlList.h"
#include "BaseWidgets/BaseTab/BaseTab.h"
#include "Hello_P/hello.h"
#include "ImportFile_P/importFile.h"
#include "ImportFile_P/IPT_base.h"
#include "Select_P/select_P.h"
#include "SelectFile_P/selectFile.h"
#include "ListSet_P/listSet.h"
#include "BasicSet_P/basicSet.h"

using namespace CoreControlWidgets;

SelectTab::SelectTab(QWidget *parent) : BaseWidgets::BaseTab(parent)
{
    this->hello_page = new SelectTab_NS::Hello_Page();
    this->importFile_page = new SelectTab_NS::ImportFile_Page();
    this->select_page = new SelectTab_NS::Select_Page();
    this->selectFile_page = new SelectTab_NS::SelectFile_Page();
    this->listSet_page = new SelectTab_NS::ListSet_Page();  
    this->basicSet_page = new SelectTab_NS::BasicSet_Page();

    this->setAcceptDrops(true);

    // 初始化延迟定时器（单次触发，10ms延迟）
    m_dragLeaveTimer = new QTimer(this);
    m_dragLeaveTimer->setSingleShot(true);
    m_dragLeaveTimer->setInterval(10);
    connect(m_dragLeaveTimer, &QTimer::timeout, this, &SelectTab::onDragLeaveTimeout);

    // 连接所有子控件的拖拽信号
    connect(importFile_page->IPT_FileToSelect, &SelectTab_NS::IPT_Base::dragEntered, this, &SelectTab::onChildDragEntered);
    connect(importFile_page->IPT_FileToSelect, &SelectTab_NS::IPT_Base::dragLeaved, this, &SelectTab::onChildDragLeaved);
    connect(importFile_page->IPT_FileToList, &SelectTab_NS::IPT_Base::dragEntered, this, &SelectTab::onChildDragEntered);
    connect(importFile_page->IPT_FileToList, &SelectTab_NS::IPT_Base::dragLeaved, this, &SelectTab::onChildDragLeaved);
    connect(importFile_page->IPT_BouthDouble, &SelectTab_NS::IPT_Base::dragEntered, this, &SelectTab::onChildDragEntered);
    connect(importFile_page->IPT_BouthDouble, &SelectTab_NS::IPT_Base::dragLeaved, this, &SelectTab::onChildDragLeaved);

    // 原有按钮逻辑（保留）
    this->controlList->pushLable(new QLabel("选择："));
    QPushButton* helloButton = new QPushButton("Hello");
    connect(helloButton, &QPushButton::clicked, this, [this](){ this->setPage(this->hello_page); });
    this->controlList->pushButton(helloButton);

    QPushButton* randomSelectButton = new QPushButton("随机选择");
    connect(randomSelectButton, &QPushButton::clicked, this, [this](){ this->setPage(this->select_page); });
    this->controlList->pushButton(randomSelectButton);

    QPushButton* fileSelectButton = new QPushButton("文件选择");
    connect(fileSelectButton, &QPushButton::clicked, this, [this](){ this->setPage(this->selectFile_page); });
    this->controlList->pushButton(fileSelectButton);

    QPushButton* listSettingButton = new QPushButton("列表设置");
    connect(listSettingButton, &QPushButton::clicked, this, [this](){ this->setPage(this->listSet_page); });
    this->controlList->pushButton(listSettingButton);
    
    QPushButton* basicSettingButton = new QPushButton("基本设置");
    connect(basicSettingButton, &QPushButton::clicked, this, [this](){ this->setPage(this->basicSet_page); });
    this->controlList->pushButton(basicSettingButton);
    
    this->setPage(this->select_page);
}

SelectTab::~SelectTab() {}

// 子控件进入拖拽：标记状态+停止定时器
void SelectTab::onChildDragEntered()
{
    m_hasChildDragging = true;
    if (m_dragLeaveTimer->isActive()) m_dragLeaveTimer->stop();
}

// 子控件离开拖拽：重置状态+触发延迟切回
void SelectTab::onChildDragLeaved()
{
    m_hasChildDragging = false;
    if (m_oldPage && !m_hasChildDragging) m_dragLeaveTimer->start();
}

// 延迟切回逻辑：仅无子女拖拽时切回
void SelectTab::onDragLeaveTimeout()
{
    if (!m_hasChildDragging && m_oldPage) {
        this->setPage(m_oldPage);
        m_oldPage = nullptr;
    }
}

void SelectTab::dragEnterEvent(QDragEnterEvent *event)
{
    if (m_this_widget != importFile_page)
        this->m_oldPage = this->m_this_widget;

    if (!event->mimeData()->hasUrls()) return;
    QUrl url = event->mimeData()->urls().first();
    QFileInfo fileInfo(url.toLocalFile());
    if (!fileInfo.exists() || (!fileInfo.isFile() && !fileInfo.isDir())) return;

    if (fileInfo.isFile()) {
        this->setPage(this->importFile_page);
        event->acceptProposedAction();
    }
}

void SelectTab::dragLeaveEvent(QDragLeaveEvent *event)
{
    Q_UNUSED(event);
    // 停止旧定时器，避免重复触发
    if (m_dragLeaveTimer->isActive()) m_dragLeaveTimer->stop();
    // 有子控件拖拽则不处理，否则启动延迟切回
    if (!m_hasChildDragging) m_dragLeaveTimer->start();
}

void SelectTab::dropEvent(QDropEvent *event)
{
    Q_UNUSED(event);
    // 停止定时器+重置状态
    if (m_dragLeaveTimer->isActive()) m_dragLeaveTimer->stop();
    m_hasChildDragging = false;
    if (m_oldPage) {
        this->setPage(m_oldPage);
        m_oldPage = nullptr;
    }
}