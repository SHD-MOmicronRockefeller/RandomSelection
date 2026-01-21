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
    //setFixedWidth(600);
    move((Variables::WINDOW_WIDTH - 600)/2, 5);
    // setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    // /setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
}

CustomTitleBar::~CustomTitleBar()
{
    m_mainLayout = nullptr;
    m_leftLayout = nullptr;
    m_midLayout = nullptr;
    m_rightLayout = nullptr;
    m_iconBtn = nullptr;
    m_titleLabel = nullptr;
    m_midBtns.clear();
    m_btnMin = nullptr;
    m_btnSetting = nullptr;
    m_btnMax = nullptr;
    m_btnClose = nullptr;

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
    m_midLayout->setSpacing(10);
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
    m_iconBtn = new QPushButton(this);
    m_iconBtn->setObjectName("rightBtn");
    m_iconBtn->setIcon(QIcon(":/ICONS/icons/ApplicationIcon.png"));
    m_iconBtn->setIconSize(QSize(35, 35));
    //m_iconLabel->setStyleSheet("background-color: transparent; border: none;");


    m_titleLabel = new QLabel("Random Selection", this);
    m_titleLabel->setStyleSheet("font-size: 15px; font-weight: bold; color: #333;");
    m_leftLayout->addWidget(m_iconBtn);
    m_leftLayout->addWidget(m_titleLabel);

    // 中间按钮
    QString midBtnTexts[] = {" 选择", " 文件", " 设置", " 更多"};
    QString midBtnNames[] = {"randomSelect", "fileEdit", "setting", "about"};
    for (int i = 0; i < 4; ++i){
        QPushButton *btn = new QPushButton(midBtnTexts[i], this);
        btn->setObjectName("midBtn");
        m_midLayout->addWidget(btn);
        m_midBtns[midBtnNames[i]] = btn;
        // 发射信号：必须用 this->sigMidBtnClicked，或直接 emit sigMidBtnClicked
        connect(btn, &QPushButton::clicked, this, [i, this](){
            return this->onMidBtnClicked(i);
        });
    }
    m_midBtns["randomSelect"]->setIcon(QIcon(":/ICONS/icons/MainTabIcons/RandomSelectTabIcon.png"));
    m_midBtns["randomSelect"]->setIconSize(QSize(20, 20));
    m_midBtns["fileEdit"]->setIcon(QIcon(":/ICONS/icons/MainTabIcons/FileEditTabIcon.png"));
    m_midBtns["fileEdit"]->setIconSize(QSize(23, 23));
    m_midBtns["setting"]->setIcon(QIcon(":/ICONS/icons/MainTabIcons/SettingTabIcon.png"));
    m_midBtns["setting"]->setIconSize(QSize(20, 20));
    m_midBtns["about"]->setIcon(QIcon(":/ICONS/icons/MainTabIcons/AboutTabIcon.png"));
    m_midBtns["about"]->setIconSize(QSize(20, 20));

    // 右侧按钮
    m_btnMin = new QPushButton(this);
    m_btnMin->setObjectName("rightBtn");
    m_btnMin->setIcon(QIcon(":/ICONS/icons/TitleIcons/_MinimizeButton.png"));
    m_btnMin->setIconSize(QSize(25, 25));
    m_rightLayout->addWidget(m_btnMin);
    connect(m_btnMin,     &QPushButton::clicked, this, &CoreControlWidgets::MainWindow::CustomTitleBar::onMinimizeClicked);
    
    m_btnSetting = new QPushButton(this);
    m_btnSetting->setObjectName("rightBtn");
    m_btnSetting->setIcon(QIcon(":/ICONS/icons/TitleIcons/_MinWindowButtonN.png"));
    m_btnSetting->setIconSize(QSize(20, 20));
    m_rightLayout->addWidget(m_btnSetting);
    connect(m_btnSetting, &QPushButton::clicked, this, &CoreControlWidgets::MainWindow::CustomTitleBar::onSettingClicked);
    
    m_btnMax = new QPushButton(this);
    m_btnMax->setObjectName("rightBtn");
    m_btnMax->setIcon(QIcon(":/ICONS/icons/TitleIcons/_MaximizeButtonN.png"));
    m_btnMax->setIconSize(QSize(20, 20));
    m_rightLayout->addWidget(m_btnMax);
    connect(m_btnMax,     &QPushButton::clicked, this, &CoreControlWidgets::MainWindow::CustomTitleBar::onMaximizeClicked);

    m_btnClose = new QPushButton(this);
    m_btnClose->setObjectName("closeBtn");
    m_btnClose->setIcon(QIcon(":/ICONS/icons/TitleIcons/_CloseButton.png"));
    m_btnClose->setIconSize(QSize(20, 20));
    m_rightLayout->addWidget(m_btnClose);
    connect(m_btnClose,   &QPushButton::clicked, this, &CoreControlWidgets::MainWindow::CustomTitleBar::onCloseClicked);
    
}

void CustomTitleBar::initStyle()//#f8f9fa
{
    setStyleSheet(R"(
        #CustomTitleBar { 
            background-color: #f8f9fa; 
            border-bottom: 1px solid #e0e0e0; 
            border-radius: 0px;
        }
        QPushButton#midBtn {
            padding: 0px 12px; font-size: 15px;
            height: 36px;
            border: none; border-radius: 18px;
            background-color: #e9ecef; color: #333;
        }
        QPushButton#midBtn:hover { background-color: #dee2e6; }
        QPushButton#midBtn:pressed { background-color: #adb5bd; }
        QPushButton#rightBtn {
            width: 35px;
            height: 35px;
            border: none; border-radius: 0px;
            background-color: transparent;
        }
        QPushButton#rightBtn:hover { background-color: #dee2e6; }
        QPushButton#rightBtn:pressed { background-color: #adb5bd; }
        QPushButton#closeBtn {
            width: 35px;
            height: 35px;
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
    this->onMaximizeClicked();
}

void CustomTitleBar::onMaximizeClicked()
{
    this->setMainWindowMaximized();
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
        case 2: onMidBtnClicked_setting();       break;
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

void CustomTitleBar::onMidBtnClicked_setting()
{
    printf("baibao button clicked\n");
}

void CustomTitleBar::onMidBtnClicked_about()
{
    printf("about button clicked\n");
}

void CustomTitleBar::setMainWindowMaximized()
{


    if (this->m_isMaximized){
        this->window()->showNormal();
        this->window()->resize(this->m_windowSize);
        this->m_btnMax->setIcon(QIcon(":/ICONS/icons/TitleIcons/_MaximizeButtonN.png"));
        this->m_btnSetting->setIcon(QIcon(":/ICONS/icons/TitleIcons/_MinWindowButtonN.png"));
        this->m_isMaximized = false;
    } else {
        this->m_windowSize = this->window()->size();
        this->window()->showMaximized();
        this->m_btnMax->setIcon(QIcon(":/ICONS/icons/TitleIcons/_MaximizeButtonM.png"));
        this->m_btnSetting->setIcon(QIcon(":/ICONS/icons/TitleIcons/_MinWindowButtonM.png"));
        this->m_isMaximized = true;
    }
}

void CustomTitleBar::setMainWindowminimized()
{
    CoreControlWidgets::MainWindowShell *mainWindowShell = qobject_cast<CoreControlWidgets::MainWindowShell *>(this->window());
    if (not mainWindowShell) return;

    if (mainWindowShell->isMinimized()){
        mainWindowShell->showNormal();
    } else {
        mainWindowShell->showMinimized();
    }
}

void CustomTitleBar::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton){
        m_isDragging = true;
        m_dragStartPos = event->pos();
        m_dragStartGlobalPos = event->globalPosition().toPoint();
    }
    QWidget::mousePressEvent(event);
}

void CustomTitleBar::mouseMoveEvent(QMouseEvent *event)
{
    if (!m_isDragging){
        QFrame::mouseMoveEvent(event);
        return;
    }
    // 窗口最大化时，移动窗口
    if (this->m_isMaximized){
        this->setMainWindowMaximized();
        double screenWidth = this->window()->screen()->size().width();
        double windowWidth = this->window()->width();
        int newX = static_cast<int>(m_dragStartGlobalPos.x() / screenWidth * windowWidth);
        QPoint newTitleBarPos = QPoint(newX, m_dragStartPos.y());// 新的相对向量

        QPoint mouseMovePoint = event->globalPosition().toPoint() - m_dragStartGlobalPos;// 鼠标移动的向量

        QPoint newWindowGlobalPos = m_dragStartGlobalPos + mouseMovePoint - newTitleBarPos;// 新的全局向量
        this->window()->move(newWindowGlobalPos);

        return;
    } else {
        // 窗口非最大化时，移动窗口
        QPoint mouseMovePoint = event->globalPosition().toPoint() - m_dragStartGlobalPos;
        QPoint newPos = this->window()->pos() + mouseMovePoint;
        this->window()->move(newPos);
    }
    m_dragStartPos = event->pos();
    m_dragStartGlobalPos = event->globalPosition().toPoint();
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

    this->setMainWindowMaximized();
}

} // namespace MainWindow

} // namespace CoreControlWidgets