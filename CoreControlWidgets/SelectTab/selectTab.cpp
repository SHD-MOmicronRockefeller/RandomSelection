#include "selectTab.h"

CoreControlWidgets::SelectTab::SelectTab(QWidget *parent) : BaseWidgets::BaseTab(parent)
{
    // ========== 1. 原有controlList逻辑（保留） ==========
    this->controlList->pushLable(new QLabel("选择："));
    this->controlList->pushButton(new QPushButton("文件选择"));
    this->controlList->pushButton(new QPushButton("随机选择"));
    this->controlList->pushButton(new QPushButton("列表设置"));
    this->controlList->pushButton(new QPushButton("基本设置"));

    // ========== 2. 构建上层固定区域 ==========
    m_topWidget = new QWidget();
    m_topWidget->setObjectName("SelectTab_TopWidget");
    m_topWidget->setStyleSheet("QWidget#SelectTab_TopWidget{background: #FFCC00; min-height: 50px;}");
    QHBoxLayout *topLayout = new QHBoxLayout(m_topWidget);
    topLayout->setContentsMargins(10, 0, 10, 0);
    topLayout->addWidget(new QLabel("上层固定区域"));
    topLayout->addStretch();
    topLayout->addWidget(new QPushButton("上层按钮"));

    // ========== 3. 构建中间比例固定区域 ==========
    // 初始化比例容器（示例：4:3的宽高比）
    m_aspectMidWidget = new BaseWidgets::AspectRatioWidget(4.0/1.0);
    m_aspectMidWidget->setObjectName("SelectTab_AspectMidWidget");
    m_aspectMidWidget->setStyleSheet("QWidget#SelectTab_AspectMidWidget{background: #66CCFF;}");
    // 包裹原有MidWidget
    m_midWidget = new SelectTab_NS::MidWidget();
    m_aspectMidWidget->setContentWidget(m_midWidget);

    // ========== 4. 构建下层固定区域 ==========
    m_bottomWidget = new QWidget();
    m_bottomWidget->setObjectName("SelectTab_BottomWidget");
    m_bottomWidget->setStyleSheet("QWidget#SelectTab_BottomWidget{background: #FF6699; min-height: 50px;}");
    QHBoxLayout *bottomLayout = new QHBoxLayout(m_bottomWidget);
    bottomLayout->setContentsMargins(10, 0, 10, 0);
    bottomLayout->addWidget(new QLabel("下层固定区域"));
    bottomLayout->addStretch();
    bottomLayout->addWidget(new QPushButton("下层按钮"));

    // ========== 5. 把上/中/下添加到BaseTab的中心布局 ==========
    this->m_centerLayout->setContentsMargins(0, 0, 0, 0);
    this->m_centerLayout->setSpacing(0);
    this->m_centerLayout->addWidget(m_topWidget);          // 上层（固定）
    this->m_centerLayout->addWidget(m_aspectMidWidget, 1); // 中间（占剩余空间，比例固定）
    this->m_centerLayout->addWidget(m_bottomWidget);       // 下层（固定）
}

CoreControlWidgets::SelectTab::~SelectTab()
{
    delete m_midWidget;
    delete m_aspectMidWidget;
    delete m_topWidget;
    delete m_bottomWidget;
}
