#include "CollapsibleWidget.h"
#include <QApplication>
#include <QStyle>

CollapsibleWidget::CollapsibleWidget(const QString& title, QWidget *parent)
    : QWidget(parent)
{
    initUI();
    m_titleLabel->setText(title);
    // 已移除无效的toggle(false)调用，initUI已强制初始化好收起状态
}

void CollapsibleWidget::initUI()
{
    // 1. 主布局初始化（彻底解决布局拉伸异常）
    m_mainLayout = new QVBoxLayout(this);
    m_mainLayout->setContentsMargins(0, 0, 0, 0);
    m_mainLayout->setSpacing(0);

    // 2. 头部区域初始化（固定高度，绝对不会被拉伸）
    m_headerWidget = new QWidget(this);
    m_headerWidget->setFixedHeight(36);
    m_headerWidget->setCursor(Qt::PointingHandCursor);
    m_headerWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    m_headerWidget->setObjectName("CollapsibleWidgetHeader");
    m_headerWidget->setStyleSheet(R"(
        QWidget#CollapsibleWidgetHeader {
            background-color: rgba(83, 145, 157, 0.1);
            border-radius: 5px;
        }
    )");

    QHBoxLayout* headerLayout = new QHBoxLayout(m_headerWidget);
    headerLayout->setContentsMargins(8, 0, 8, 0);
    headerLayout->setSpacing(8);

    // 标题文本
    m_titleLabel = new QLabel(this);
    m_titleLabel->setStyleSheet("font-size: 14px; color: #333;");
    headerLayout->addWidget(m_titleLabel);

    // 弹簧，把箭头固定到最右侧
    headerLayout->addStretch();

    // 箭头按钮（初始状态匹配收起：箭头向右）
    m_arrowBtn = new QPushButton(this);
    m_arrowBtn->setFixedSize(20, 20);
    m_arrowBtn->setFlat(true);
    m_arrowBtn->setCursor(Qt::PointingHandCursor);
    m_arrowBtn->setIcon(QApplication::style()->standardIcon(QStyle::SP_ArrowRight));
    m_arrowBtn->setIconSize(QSize(16, 16));
    headerLayout->addWidget(m_arrowBtn);

    // 头部拉伸因子设为0，永远不会占用多余空间
    m_mainLayout->addWidget(m_headerWidget, 0);

    // 3. 内置滚动区域初始化
    m_contentContainer = new QWidget(this);
    m_contentContainer->setLayout(new QVBoxLayout());
    m_contentContainer->layout()->setContentsMargins(8, 8, 8, 8);
    m_contentContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

    m_contentArea = new QScrollArea(this);
    m_contentArea->setWidget(m_contentContainer);
    m_contentArea->setWidgetResizable(true);
    m_contentArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_contentArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_contentArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    // 【核心修复：强制初始完全收起，和m_isExpanded=false完全匹配】
    m_contentArea->setFixedHeight(0);
    m_contentArea->hide();

    m_mainLayout->addWidget(m_contentArea, 0);

    // 4. 信号槽关联
    connect(m_arrowBtn, &QPushButton::clicked, this, [this](){
        toggle(!m_isExpanded);
    });
}

// 计算内容区目标高度：所在顶级窗口高度的60%
int CollapsibleWidget::getContentTargetHeight() const
{
    // 如需改为父控件高度的60%，把 this->window() 改为 this->parentWidget() 即可
    return this->window() ? (this->window()->height() * 0.6) : 300;
}

// 点击头部任意位置切换展开/收起
void CollapsibleWidget::mousePressEvent(QMouseEvent *event)
{
    if (m_headerWidget->underMouse()) {
        toggle(!m_isExpanded);
    }
    QWidget::mousePressEvent(event);
}

// 窗口大小变化时，自动同步内容区高度
void CollapsibleWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    if (m_isExpanded) {
        m_contentArea->setFixedHeight(getContentTargetHeight());
    }
}

// 设置内容控件（清空原有内容）
void CollapsibleWidget::setContentWidget(QWidget* widget)
{
    QLayoutItem* child;
    while ((child = m_contentContainer->layout()->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }
    m_contentContainer->layout()->addWidget(widget);
}

// 直接设置内容布局
void CollapsibleWidget::setContentLayout(QLayout* layout)
{
    delete m_contentContainer->layout();
    m_contentContainer->setLayout(layout);
}

// 获取当前展开状态
bool CollapsibleWidget::isExpanded() const
{
    return m_isExpanded;
}

// 核心切换逻辑（修复状态同步问题）
void CollapsibleWidget::toggle(bool expand)
{
    if (m_isExpanded == expand) return;
    m_isExpanded = expand;

    if (expand) {
        // 展开：先设高度，再显示
        m_contentArea->setFixedHeight(getContentTargetHeight());
        m_contentArea->show();
    } else {
        // 收起：先设高度为0，再隐藏，完全不占用空间
        m_contentArea->setFixedHeight(0);
        m_contentArea->hide();
    }

    // 切换箭头图标
    m_arrowBtn->setIcon(QApplication::style()->standardIcon(
        expand ? QStyle::SP_ArrowDown : QStyle::SP_ArrowRight
    ));

    emit toggled(expand);
}