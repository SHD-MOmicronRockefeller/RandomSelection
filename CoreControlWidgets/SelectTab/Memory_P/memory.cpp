#include "memory.h"

#include "mmryItem.h"

#include <algorithm>
CoreControlWidgets::SelectTab_NS::Memory_Page::Memory_Page(QWidget *parent): QWidget(parent)
{
    this->m_centerLayout = new QVBoxLayout();
    this->m_centerLayout->setContentsMargins(0, 0, 0, 0);
    this->m_centerLayout->setSpacing(0);
    this->m_centerLayout->setAlignment(Qt::AlignTop);
    this->setLayout(this->m_centerLayout);


    // ========== 3. 构建中层可变区域 ==========
    m_optionListScrollArea = new QScrollArea();
    m_optionListScrollArea->setFrameShape(QFrame::NoFrame);
    m_optionListScrollArea->setWidgetResizable(true);
    m_optionListScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_optionListScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    m_optionListScrollArea->setStyleSheet(R"(
        QScrollArea {
            border: none;
            background-color: #cee8f6;
        }
        QScrollBar:vertical {
            border: none;
            background: #cee8f6;
            width: 8px;
            border-radius: 4px;
        }
        QScrollBar::handle:vertical {
            background: #55a5f5;
            border-radius: 4px;
        }
        QScrollBar::handle:vertical:hover {
            background: #98c8fa;
        }
        QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {
            border: none;
            background: none;
        }
    )");
    QFrame *optionListWidget = new QFrame();
    optionListWidget->setObjectName("BasicSetTab_SetListWidget");
    optionListWidget->setStyleSheet("QFrame#BasicSetTab_SetListWidget{background: transparent;}");
    optionListWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    QVBoxLayout *memoryListLayout = new QVBoxLayout(optionListWidget);
    memoryListLayout->setAlignment(Qt::AlignTop);
    memoryListLayout->setSpacing(10);

    // 获取记录列表
    GetList = [=, this]() -> QList<MmryItem*> {
        QList<MmryItem*> result;
        if (!memoryListLayout || memoryListLayout->count() == 0) return result;
        for (int i = 0; i < memoryListLayout->count(); i++) {
            QLayoutItem* item = memoryListLayout->itemAt(i);
            if (!item) continue;
            MmryItem* memoryItem = qobject_cast<MmryItem*>(item->widget());
            if (memoryItem) {
                result.append(memoryItem);
            }
        }
        return result;
    };
    // 添加记录
    PushOption = [=, this](CoreCalculation::Base::OptionItem optionItem) {
        QList<MmryItem*> mmryItemList = GetList();
        bool is_have = false;
        for (int i = 0; i < mmryItemList.size(); ++i) {
            is_have = is_have || mmryItemList[i]->addOption(optionItem);
        }
        if (not is_have) {
            memoryListLayout->addWidget(new MmryItem(optionItem));
        }
    };
    // 排序记录列表
    SortMemory = [=, this]() {
        QList<MmryItem*> mmryItemList = GetList();
        if (!memoryListLayout || mmryItemList.count() == 0) return;
        QWidget* parentWidget = memoryListLayout->parentWidget();
        if (parentWidget) parentWidget->setUpdatesEnabled(false);

        std::sort(mmryItemList.begin(), mmryItemList.end(), [](MmryItem* a, MmryItem* b) {
            return a->optionItem.getSelectedTimes() > b->optionItem.getSelectedTimes();
        });

        for (int i = 0; i < mmryItemList.size();++i) {
            memoryListLayout->insertWidget(i, mmryItemList.at(i));
        }
        if (parentWidget) {
            parentWidget->setUpdatesEnabled(true);
            parentWidget->update();
        }
    };


    optionListWidget->adjustSize();
    m_optionListScrollArea->setWidget(optionListWidget);

    // ========== 4. 构建下层固定区域 ==========
    m_downWidget = new QWidget();
    m_downWidget->setObjectName("ListSetTab_DownWidget");
    m_downWidget->setStyleSheet("QWidget#ListSetTab_DownWidget{background: #FF6699; min-height: 50px;}");
    QHBoxLayout *bottomLayout = new QHBoxLayout(m_downWidget);
    bottomLayout->setContentsMargins(10, 0, 10, 0);
    bottomLayout->addWidget(new QLabel("下层固定区域"));
    bottomLayout->addStretch();
    bottomLayout->addWidget(new QPushButton("下层按钮"));

    // ========== 5. 把上/中/下添加到BaseTab的中心布局 ==========
    this->m_centerLayout->setContentsMargins(0, 0, 0, 0);
    this->m_centerLayout->setSpacing(0);
    this->m_centerLayout->addWidget(m_optionListScrollArea, 1); // 中间（占剩余空间，比例固定）
    this->m_centerLayout->addWidget(m_downWidget);       // 下层（固定）
}

CoreControlWidgets::SelectTab_NS::Memory_Page::~Memory_Page()
{
}
