#include "listSet.h"

#include "CoreCalculation/ToolBox/cleanLayout.hpp"

#include "CoreCalculation/SelectTabFunc/OptionList.hpp"

CoreControlWidgets::SelectTab_NS::ListSet_Page::ListSet_Page(QWidget *parent): QWidget(parent)
{
    this->m_centerLayout = new QVBoxLayout();
    this->m_centerLayout->setContentsMargins(0, 0, 0, 0);
    this->m_centerLayout->setSpacing(0);
    this->m_centerLayout->setAlignment(Qt::AlignTop);
    this->setLayout(this->m_centerLayout);

    this->setAutoFillBackground(true);
    this->setAttribute(Qt::WA_StyledBackground, true);


    // ========== 3. 构建中层可变区域 ==========
    m_setListScrollArea = new QScrollArea();
    m_setListScrollArea->setFrameShape(QFrame::NoFrame);
    m_setListScrollArea->setWidgetResizable(true);
    m_setListScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_setListScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    m_setListScrollArea->setStyleSheet(R"(
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
    QFrame *listSetListWidget = new QFrame();
    listSetListWidget->setAutoFillBackground(true);
    listSetListWidget->setAttribute(Qt::WA_StyledBackground, true);
    listSetListWidget->setObjectName("ListSetTab_SetListWidget");
    listSetListWidget->setStyleSheet("QFrame#ListSetTab_SetListWidget{background: transparent;}");
    listSetListWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    m_setListScrollArea->setWidget(listSetListWidget);

    QVBoxLayout *listSetListLayout = new QVBoxLayout(listSetListWidget);
    listSetListLayout->setAlignment(Qt::AlignTop);
    listSetListLayout->setSpacing(10);

    // 0 设置标题
    QLabel* title = new QLabel("选择设置");
    title->setAlignment(Qt::AlignHCenter| Qt::AlignVCenter);
    title->setFont(QFont("微软雅黑", 16, QFont::Bold));
    title->setWordWrap(true);
    listSetListLayout->addWidget(title);

    // 1 设置选项列表
    setOptionList = [=, this](CoreCalculation::OptionList optionList) {
        MYFUNCTION::CleanLayout() << listSetListLayout;
        for (CoreCalculation::Base::Group group : optionList.getGroups()) {
            listSetListLayout->addWidget(new ListSetGroup(group, optionList));
        }
        listSetListLayout->addStretch();
    };

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
    this->m_centerLayout->addWidget(m_setListScrollArea, 1); // 中间（占剩余空间，比例固定）
    this->m_centerLayout->addWidget(m_downWidget);       // 下层（固定）
}

CoreControlWidgets::SelectTab_NS::ListSet_Page::~ListSet_Page()
{
}
