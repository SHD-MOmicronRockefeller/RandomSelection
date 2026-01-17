#include "CustomTitleBar.h"

namespace CoreControlWidgets {

namespace MainWindow {

CustomTitleBar::CustomTitleBar(QWidget *parent): QFrame(parent)
{
    setObjectName("CustomTitleBar");

    // 初始化布局
    initLayout();
    initWidgets();
    initStyle();

    // 设置尺寸
    setFixedHeight(40);
    setFixedWidth(600);
    move((Variables::WINDOW_WIDTH - 600)/2, 5);
    // setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    // /setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
}


void CustomTitleBar::initLayout()
{
    m_mainLayout = new QHBoxLayout(this);
    m_mainLayout->setContentsMargins(0, 0, 0, 0);
    m_mainLayout->setSpacing(0);


    m_leftLayout = new QHBoxLayout();
    m_leftLayout->setContentsMargins(0, 0, 0, 0);
    m_leftLayout->setSpacing(10);
    m_mainLayout->addLayout(m_leftLayout);

    m_mainLayout->addStretch();

    m_midLayout = new QHBoxLayout();
    m_midLayout->setContentsMargins(0, 0, 0, 0);
    m_midLayout->setSpacing(0);
    m_mainLayout->addLayout(m_midLayout);

    m_mainLayout->addStretch();

    m_rightLayout = new QHBoxLayout();
    m_rightLayout->setContentsMargins(0, 0, 5, 0);
    m_rightLayout->setSpacing(0);
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
    m_titleLabel = new QLabel("a", this);
    m_titleLabel->setStyleSheet("font-size: 15px; font-weight: bold; color: #333;");
    m_leftLayout->addWidget(m_iconLabel);
    m_leftLayout->addWidget(m_titleLabel);

    // 中间按钮
    QString midBtnTexts[] = {"随机选择", "文件编辑", "百宝盒子", "关于程序"};
    QString midBtnNames[] = {"randomSelect", "fileEdit", "baibao", "about"};
    for (int i = 0; i < 4; ++i){
        QPushButton *btn = new QPushButton(midBtnTexts[i], this);
        btn->setObjectName(midBtnNames[i]);
        m_midLayout->addWidget(btn);
        m_midBtns[midBtnNames[i]] = btn;
        // 发射信号：必须用 this->sigMidBtnClicked，或直接 emit sigMidBtnClicked
        connect(btn, &QPushButton::clicked, this, [i = i, this](){
            return this->onMidBtnClicked(i);
        });
    }

    // 右侧按钮
    m_btnMin = new QPushButton("恢复", this);
    m_btnMin->setObjectName("rightBtn");

    m_btnSetting = new QPushButton("迷你化", this);
    m_btnSetting->setObjectName("rightBtn");

    m_btnClose = new QPushButton("回位", this);
    m_btnClose->setObjectName("rightBtn");

    m_btnMax = new QPushButton("置顶", this);
    m_btnMax->setObjectName("rightBtn");

    m_rightLayout->addWidget(m_btnMin);
    m_rightLayout->addWidget(m_btnSetting);
    m_rightLayout->addWidget(m_btnMax);
    m_rightLayout->addWidget(m_btnClose);

    // 信号连接：必须用 MainWindow::CustomTitleBar:: 或 this->，避免作用域错误
    connect(m_btnMin,     &QPushButton::clicked, this, &CoreControlWidgets::MainWindow::CustomTitleBar::onMinimizeClicked);
    connect(m_btnClose,   &QPushButton::clicked, this, &CoreControlWidgets::MainWindow::CustomTitleBar::onCloseClicked);
    connect(m_btnMax,     &QPushButton::clicked, this, &CoreControlWidgets::MainWindow::CustomTitleBar::onMaximizeClicked);
    connect(m_btnSetting, &QPushButton::clicked, this, &CoreControlWidgets::MainWindow::CustomTitleBar::onSettingClicked);
}

void CustomTitleBar::initStyle()//#f8f9fa
{
    setStyleSheet(R"(
        #CustomTitleBar { 
            background-color: #f8f9fa; 
            border-bottom: 1px solid #e0e0e0; 
            border-radius: 5px;
        }
        QPushButton#midBtn {
            padding: 4px 12px; font-size: 12px;
            border: none; border-radius: 3px;
            background-color: #e9ecef; color: #333;
        }
        QPushButton#midBtn:hover { background-color: #dee2e6; }
        QPushButton#midBtn:pressed { background-color: #adb5bd; }
        QPushButton#rightBtn {
            width: 40px;
            height: 40px;
            border: none; border-radius: 0px;
            background-color: transparent;
        }
        QPushButton#rightBtn:hover { background-color: #dee2e6; }
        QPushButton#rightBtn:pressed { background-color: #adb5bd; }
        QPushButton#closeBtn {
            width: 40px;
            height: 40px;
            border: none; border-radius: 0px;
            background-color: transparent;
        }
        QPushButton#closeBtn:hover { background-color: #ff7875; }
        QPushButton#closeBtn:pressed { background-color: #ff1f1f; }
    )");
}

void CustomTitleBar::onMinimizeClicked()
{
    this->window()->showMinimized();
}

void CustomTitleBar::onSettingClicked()
{
    this->window()->showMaximized();
}

void CustomTitleBar::onMaximizeClicked()
{
    this->setMainWindowNormal();
}

void CustomTitleBar::onCloseClicked()
{
    this->window()->close();
}

void CustomTitleBar::onMidBtnClicked(int index)
{
    printf("mid button clicked: %d\n", index);
    switch (index){
        case 0: onMidBtnClicked_randomSelect();  break;
        case 1: onMidBtnClicked_fileEdit();      break;
        case 2: onMidBtnClicked_baibao();        break;
        case 3: onMidBtnClicked_about();         break;
    }
}

void CustomTitleBar::onMidBtnClicked_randomSelect()
{
    printf("random select button clicked\n");
}

void CustomTitleBar::onMidBtnClicked_fileEdit()
{
    printf("file edit button clicked\n");
}

void CustomTitleBar::onMidBtnClicked_baibao()
{
    printf("baibao button clicked\n");
}

void CustomTitleBar::onMidBtnClicked_about()
{
    printf("about button clicked\n");
}

void CustomTitleBar::setMainWindowNormal()
{
    CoreControlWidgets::MainWindowShell *mainWindowShell = qobject_cast<CoreControlWidgets::MainWindowShell *>(this->window());
    if (not mainWindowShell) return;

    if (mainWindowShell->isMaximized()){
        mainWindowShell->showNormal();
    } else {
        mainWindowShell->showMaximized();
    }
}

void CustomTitleBar::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton){
        m_isDragging = true;
        m_dragStartPos = event->pos();
    }
    QWidget::mousePressEvent(event);
}

void CustomTitleBar::mouseMoveEvent(QMouseEvent *event)
{
    if (!m_isDragging){
        QFrame::mouseMoveEvent(event);
        return;
    }

    // 计算标题栏新位置：当前位置 + 鼠标移动偏移
    QPoint newPos = this->pos() + (event->pos() - m_dragStartPos);
    
    // 可选：限制标题栏不能拖出主窗口范围
    QRect parentRect = this->parentWidget()->rect();
    newPos.setX(qBound(0, newPos.x(), parentRect.width() - this->width()));
    newPos.setY(qBound(0, newPos.y(), parentRect.height() - this->height()));

    // 仅移动标题栏自身
    this->move(newPos);
    QFrame::mouseMoveEvent(event);
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

void CustomTitleBar::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() != Qt::LeftButton) return;

    this->setMainWindowNormal();
}

} // namespace MainWindow

} // namespace CoreControlWidgets