#include "CustomTitleBar.h"

namespace MainWindow {

CustomTitleBar::CustomTitleBar(QWidget *parent)
    : QWidget(parent)
{
    initLayout();
    initWidgets();
    initStyle();
    setFixedHeight(40);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
}

void CustomTitleBar::setTitleText(const QString &text)
{
    m_titleLabel->setText(text);
}

void CustomTitleBar::initLayout()
{
    m_mainLayout = new QHBoxLayout(this);
    m_mainLayout->setContentsMargins(0, 0, 0, 0);
    m_mainLayout->setSpacing(20);

    m_leftLayout = new QHBoxLayout();
    m_leftLayout->setContentsMargins(0, 0, 0, 0);
    m_leftLayout->setSpacing(10);
    m_mainLayout->addLayout(m_leftLayout);

    m_mainLayout->addStretch();

    m_midLayout = new QHBoxLayout();
    m_midLayout->setContentsMargins(0, 0, 0, 0);
    m_midLayout->setSpacing(15);
    m_mainLayout->addLayout(m_midLayout);

    m_mainLayout->addStretch();

    m_rightLayout = new QHBoxLayout();
    m_rightLayout->setContentsMargins(0, 0, 0, 0);
    m_rightLayout->setSpacing(10);
    m_mainLayout->addLayout(m_rightLayout);

    setLayout(m_mainLayout);
}

void CustomTitleBar::initWidgets()
{
    // 左侧控件
    m_leftLayout->addSpacing(10);
    m_iconLabel = new QLabel(this);
    m_iconLabel->setFixedSize(24, 24);
    m_iconLabel->setStyleSheet("background-color: #3498db; border-radius: 4px;");
    m_titleLabel = new QLabel("随机点名程序", this);
    m_titleLabel->setStyleSheet("font-size: 15px; font-weight: bold; color: #333;");
    m_leftLayout->addWidget(m_iconLabel);
    m_leftLayout->addWidget(m_titleLabel);

    // 中间按钮
    QString midBtnTexts[] = {"功能1", "功能2", "功能3", "功能4"};
    for (int i = 0; i < 4; ++i)
    {
        QPushButton *btn = new QPushButton(midBtnTexts[i], this);
        btn->setObjectName("midBtn");
        m_midBtns.append(btn);
        m_midLayout->addWidget(btn);
        // 发射信号：必须用 this->sigMidBtnClicked，或直接 emit sigMidBtnClicked
        connect(btn, &QPushButton::clicked, this, [=](){
            emit this->sigMidBtnClicked(i + 1); // 加 this-> 明确作用域，避免歧义
        });
    }

    // 右侧按钮
    m_btnSetting = new QPushButton("设置", this);
    m_btnMin = new QPushButton("最小化", this);
    m_btnClose = new QPushButton("关闭", this);
    m_btnSetting->setObjectName("rightBtn");
    m_btnMin->setObjectName("rightBtn");
    m_btnClose->setObjectName("closeBtn");
    m_rightLayout->addWidget(m_btnSetting);
    m_rightLayout->addWidget(m_btnMin);
    m_rightLayout->addWidget(m_btnClose);

    // 信号连接：必须用 MainWindow::CustomTitleBar:: 或 this->，避免作用域错误
    connect(m_btnMin, &QPushButton::clicked, this, &MainWindow::CustomTitleBar::sigMinimize);
    connect(m_btnClose, &QPushButton::clicked, this, &MainWindow::CustomTitleBar::sigClose);
    connect(m_btnSetting, &QPushButton::clicked, this, &MainWindow::CustomTitleBar::sigSetting);
}

void CustomTitleBar::initStyle()
{
    setStyleSheet("MainWindow--CustomTitleBar { background-color: #f8f9fa; border-bottom: 1px solid #e0e0e0; }");
    setStyleSheet(styleSheet() + R"(
        #midBtn {
            padding: 4px 12px; font-size: 12px;
            border: none; border-radius: 3px;
            background-color: #e9ecef; color: #333;
        }
        #midBtn:hover { background-color: #dee2e6; }
        #midBtn:pressed { background-color: #adb5bd; }
        #rightBtn {
            padding: 4px 12px; font-size: 12px;
            border: none; border-radius: 3px;
            background-color: #e9ecef; color: #333;
        }
        #rightBtn:hover { background-color: #dee2e6; }
        #rightBtn:pressed { background-color: #adb5bd; }
        #closeBtn { background-color: #ff4d4f; color: white; }
        #closeBtn:hover { background-color: #ff7875; }
        #closeBtn:pressed { background-color: #ff1f1f; }
    )");
}

void CustomTitleBar::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_isDragging = true;
        m_dragStartPos = event->globalPosition().toPoint() - this->window()->frameGeometry().topLeft();
    }
    QWidget::mousePressEvent(event);
}

void CustomTitleBar::mouseMoveEvent(QMouseEvent *event)
{
    if (m_isDragging && this->window())
    {
        this->window()->move(event->globalPosition().toPoint() - m_dragStartPos);
    }
    QWidget::mouseMoveEvent(event);
}

void CustomTitleBar::mouseReleaseEvent(QMouseEvent *event)
{
    m_isDragging = false;
    QWidget::mouseReleaseEvent(event);
}

void CustomTitleBar::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    QWidget::paintEvent(event);
}

} // namespace MainWindow