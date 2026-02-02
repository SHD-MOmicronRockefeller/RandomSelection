#include "basicSet.h"

CoreControlWidgets::SelectTab_NS::BasicSet_Page::BasicSet_Page(QWidget *parent): QWidget(parent)
{
    this->m_centerLayout = new QVBoxLayout();
    this->m_centerLayout->setContentsMargins(0, 0, 0, 0);
    this->m_centerLayout->setSpacing(0);
    this->m_centerLayout->setAlignment(Qt::AlignTop);
    this->setLayout(this->m_centerLayout);

    // ========== 2. 构建上层固定区域 ==========
    m_topWidget = new QWidget();
    m_topWidget->setObjectName("ListSetTab_TopWidget");
    m_topWidget->setStyleSheet("QWidget#ListSetTab_TopWidget{background: #FFCC00; min-height: 50px;}");
    QHBoxLayout *topLayout = new QHBoxLayout(m_topWidget);
    topLayout->setContentsMargins(10, 0, 10, 0);
    topLayout->addWidget(new QLabel("上层固定区域"));
    topLayout->addStretch();
    topLayout->addWidget(new QPushButton("上层按钮"));


    // ========== 3. 构建中层可变区域 ==========
    m_midWidget = new QWidget();
    m_midWidget->setObjectName("ListSetTab_MidWidget");
    m_midWidget->setStyleSheet("QWidget#ListSetTab_MidWidget{background: #FF9933; min-height: 50px;}");
    QHBoxLayout *midLayout = new QHBoxLayout(m_midWidget);
    midLayout->setContentsMargins(10, 10, 10, 10);
    midLayout->setSpacing(10);

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
    this->m_centerLayout->addWidget(m_topWidget);          // 上层（固定）
    this->m_centerLayout->addWidget(m_midWidget, 1); // 中间（占剩余空间，比例固定）
    this->m_centerLayout->addWidget(m_downWidget);       // 下层（固定）
}

CoreControlWidgets::SelectTab_NS::BasicSet_Page::~BasicSet_Page()
{
}
