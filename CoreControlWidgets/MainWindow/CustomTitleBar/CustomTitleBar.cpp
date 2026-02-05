#include "CustomTitleBar.h"

#include "VariablesStore/globalVariables.h"

#include "CoreControlWidgets/MainWindow/mainWindow.h"

#include "CoreCalculation/TitleFunc/titleFunc.h"

namespace CoreControlWidgets {

namespace MainWindow {

CustomTitleBar::CustomTitleBar(QWidget *parent): QFrame(parent)
{
    setObjectName("CustomTitleBar");

    // 初始化布局
    initLayout();
    initWidgets();
    initStyle();

    onMidBtnClicked("randomSelect", false);

    // 设置尺寸
    setFixedHeight(40);
    //setFixedWidth(600);
    move((GlobalVariables::getInstance()->main_window_width - 600)/2, 5);
    // setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    // setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
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
        connect(btn, &QPushButton::clicked, this, [i, this, midBtnNames](){
            return this->onMidBtnClicked(midBtnNames[i]);
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

    thisTabBtn = m_midBtns["randomSelect"];

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
            background-color: rgba(248, 249, 250, 1); 
            border-bottom: 1px solid rgba(220, 220, 220, 1); 
            border-radius: 0px;
        }
        QPushButton#midBtn {
            padding: 0px 12px; font-size: 15px;
            height: 36px;
            border: none; border-radius: 18px;
            background-color: rgba(255, 255, 255, 1); color: #333;
        }
        QPushButton#midBtn:hover { background-color: rgba(152, 200, 248, 1);}
        QPushButton#midBtn:pressed { background-color: rgba(88, 171, 255, 1);}
        QPushButton#midBtn::icon { filter: none   }
        QPushButton#rightBtn {
            width: 35px;
            height: 35px;
            border: none; border-radius: 0px;
            background-color: transparent;
        }
        QPushButton#rightBtn:hover { background-color: rgba(222, 226, 230, 1); }
        QPushButton#rightBtn:pressed { background-color: rgba(173, 181, 189, 1); }
        QPushButton#closeBtn {
            width: 35px;
            height: 35px;
            border: none; border-radius: 0px;
            background-color: transparent;
        }
        QPushButton#closeBtn:hover { background-color: rgba(255, 120, 117, 1); }
        QPushButton#closeBtn:pressed { background-color: rgba(255, 31, 31, 1); }
    )");
}

QIcon CustomTitleBar::setIconColor(QIcon icon, QColor color)
{
    if (icon.isNull()) {
        printf("icon is null\n");
        return icon; // 返回原图标，避免崩溃
    }
    QPixmap pixmap = icon.pixmap(QSize(32, 32));
    QPainter painter(&pixmap);
    painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    painter.fillRect(pixmap.rect(), color);
    painter.end();
    return QIcon(pixmap);
}

void CustomTitleBar::onMinimizeClicked()
{
    this->setMainWindowminimized();
}

void CustomTitleBar::onSettingClicked()
{
    GlobalVariables *gv = GlobalVariables::getInstance();

    if (gv->is_mini_window_showed){
        bool old_is_max = gv->is_max_window_showed;
        if (gv->is_max_window_showed)
            MY_FUNC::setWindowReMaximized();
        MY_FUNC::setMainWindow();
        if (gv->old_window_is_max){
            MY_FUNC::setWindowMaximized();
            return;
        }
        if (old_is_max) {
            QScreen* screen = gv->main_window_shell->screen();
            if (!screen) screen = QGuiApplication::primaryScreen();
            QRect screenRect = screen->availableGeometry();

            int screenCenterX = screenRect.x() + screenRect.width() / 2;
            int screenCenterY = screenRect.y() + screenRect.height() / 2;

            int windowWidth = gv->main_window_shell->width();
            int windowHeight = gv->main_window_shell->height();
            int windowX = screenCenterX - windowWidth / 2;
            int windowY = screenCenterY - windowHeight / 2;

            gv->main_window_shell->move(windowX, windowY);
        }
        return;
    }

    gv->old_window_is_max = gv->is_max_window_showed;

    if (gv->old_window_is_max){
        MY_FUNC::setWindowReMaximized();
    }

    MY_FUNC::setMinWindow();

    if (gv->old_window_is_max){

        QScreen* screen = gv->main_window_shell->screen();
        if (!screen) screen = QGuiApplication::primaryScreen();
        QRect screenRect = screen->availableGeometry();

        int screenCenterX = screenRect.x() + screenRect.width() / 2;
        int screenCenterY = screenRect.y() + screenRect.height() / 2;

        int windowWidth = gv->main_window_shell->width();
        int windowHeight = gv->main_window_shell->height();
        int windowX = screenCenterX - windowWidth / 2;
        int windowY = screenCenterY - windowHeight / 2;

        gv->main_window_shell->move(windowX, windowY);
    }

    MessageTipManager::getInstance().addMessage(QString("正在打开 迷你化 窗口..."), false, 1000);
}

void CustomTitleBar::onMaximizeClicked()
{
    GlobalVariables *gv = GlobalVariables::getInstance();
    // if (gv->is_mini_window_showed)
    //     onSettingClicked();
    if (gv->is_max_window_showed){
        MY_FUNC::setWindowReMaximized();
    } else {
        MY_FUNC::setWindowMaximized();
    }
}

void CustomTitleBar::onCloseClicked()
{
    this->window()->close();
}

void CustomTitleBar::closeThisTab()
{
    if (GlobalVariables::getInstance()->this_tab_widget == nullptr) return;
    GlobalVariables::getInstance()->main_window_shell->m_centralLayout->removeWidget(GlobalVariables::getInstance()->this_tab_widget);
    GlobalVariables::getInstance()->this_tab_widget->hide();
}

void CustomTitleBar::onMidBtnClicked(QString ObjectName, bool canRun)
{
    // 设置当前按钮
    if (ObjectName != ""){
        thisTabBtn = m_midBtns[ObjectName];
    }
    for (auto &button : m_midBtns){
        button->setStyleSheet(R"(
        QPushButton#midBtn {
            color: rgba(51, 51, 51, 1);
            padding: 0px 12px; font-size: 15px;
            height: 36px;
            border: none; border-radius: 18px;
            background-color: rgba(255, 255, 255, 1);
        }
        QPushButton#midBtn:hover { background-color: rgba(152, 200, 248, 1); }
        QPushButton#midBtn:pressed { background-color: rgba(88, 171, 255, 1); }
        )");
        button->setIcon(setIconColor(button->icon(), QColor(0, 0, 0)));
    }
    thisTabBtn->setStyleSheet(R"(
    QPushButton#midBtn {
        color: rgba(255, 255, 255, 1);
        padding: 0px 12px; font-size: 15px;
        height: 36px;
        border: none; border-radius: 18px;
        background-color: rgba(17, 112, 208, 1);
    }
    QPushButton#midBtn:pressed { background-color: rgba(88, 171, 255, 1); }
    QPushButton#midBtn::icon { filter: invert(100%); }
    )");
    thisTabBtn->setIcon(setIconColor(thisTabBtn->icon(), QColor(255, 255, 255)));

    if (!canRun) return;

    closeThisTab();

    if (ObjectName == "randomSelect") {
        onMidBtnClicked_randomSelect();
    } else if (ObjectName == "fileEdit") {
        onMidBtnClicked_fileEdit();
    } else if (ObjectName == "setting") {
        onMidBtnClicked_setting();
    } else if (ObjectName == "about") {
        onMidBtnClicked_about();
    }
}

void CustomTitleBar::onMidBtnClicked_randomSelect()
{
    GlobalVariables::getInstance()->this_tab_widget = GlobalVariables::getInstance()->select_tab;
    this->onMidBtnClicked_help();
    GlobalVariables::getInstance()->tab_index = 0;
}

void CustomTitleBar::onMidBtnClicked_fileEdit()
{
    GlobalVariables::getInstance()->this_tab_widget = GlobalVariables::getInstance()->file_tab;
    this->onMidBtnClicked_help();
    GlobalVariables::getInstance()->tab_index = 1;
}

void CustomTitleBar::onMidBtnClicked_setting()
{
    GlobalVariables::getInstance()->this_tab_widget = GlobalVariables::getInstance()->setting_tab;
    this->onMidBtnClicked_help();
    GlobalVariables::getInstance()->tab_index = 2;
}

void CustomTitleBar::onMidBtnClicked_about()
{
    GlobalVariables::getInstance()->this_tab_widget = GlobalVariables::getInstance()->about_tab;
    this->onMidBtnClicked_help();
    GlobalVariables::getInstance()->tab_index = 3;
}

void CustomTitleBar::onMidBtnClicked_clicked(int tab_index)
{
    switch (tab_index)
    {
        case 0:
            onMidBtnClicked("randomSelect");
            break;
        case 1:
            onMidBtnClicked("fileEdit");
            break;
        case 2:
            onMidBtnClicked("setting");
            break;
        case 3:
            onMidBtnClicked("about");
            break;
    default:
        break;
    }
}

void CustomTitleBar::onMidBtnClicked_help()
{
    GlobalVariables* gv = GlobalVariables::getInstance();
    gv->main_window_shell->m_centralLayout->addWidget(GlobalVariables::getInstance()->this_tab_widget);
    gv->this_tab_widget->show();
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
    if (GlobalVariables::getInstance()->is_max_window_showed){
        MY_FUNC::setWindowReMaximized();
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

    MY_FUNC::setWindowMaximized();
}

} // namespace MainWindow

} // namespace CoreControlWidgets