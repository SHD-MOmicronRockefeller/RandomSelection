#include "mainWindow.h"
#include "VariablesStore/globalVariables.h"
#include "CoreControlWidgets/MainWindow/CustomTitleBar/CustomTitleBar.h"
#include "CoreControlWidgets/SelectTab/selectTab.h"
#include "CoreControlWidgets/MinWindowShell/minWindowShell.h"

CoreControlWidgets::MainWindowShell::MainWindowShell(QWidget *parent) : QMainWindow(parent)
{
    this->setObjectName("MainWindowShell");
    this->m_baseWidget = new QWidget(this);// 整个窗口的widget
    this->m_baseWidget->setObjectName("MainWindowShell_baseWidget");
    this->m_baseWidget->setAutoFillBackground(true);
    this->m_baseWidget->setAttribute(Qt::WA_StyledBackground, true);
    this->m_baseWidget->setStyleSheet(R"(
        QWidget#MainWindowShell_baseWidget{
            background-color: rgba(211, 229, 247, 1);
        }
    )");
    this->setCentralWidget(this->m_baseWidget);// 设置窗口
    GlobalVariables* gv = GLOBAL_VARIABLES;
    gv->main_window_widget = this->m_baseWidget;

    // 设置窗口大小
    this->setGeometry(100, 100, 800, 600);
    this->centralWidget()->setContentsMargins(0, 0, 0, 0);

    // 设置窗口标签
    //this->setWindowFlags(Qt::Window | Qt::WindowTitleHint);
    this->setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
    //this->setAttribute(Qt::WA_TranslucentBackground, true);
    //this->setStyleSheet("QMainWindow#MainWindowShell{border: none; background-color: rgb(17, 112, 208);}");

    // 初始化title layout
    this->m_titleLayout = new QVBoxLayout(this->m_baseWidget);// 标题栏layout 用于显示title bar
    this->m_titleLayout->setContentsMargins(0, 0, 0, 0);// 设置边距为0
    this->m_titleLayout->setSpacing(0);// 设置间距为0

    // 初始化自定义标题栏
    // qDebug() << (GlobalVariables::getInstance()->custom_title_bar == nullptr);
    this->m_customTitleBar = gv->custom_title_bar;
    this->m_titleLayout->addWidget(this->m_customTitleBar); // 添加自定义标题栏

    // 初始化主体widget
    this->m_centralWidget = new QWidget();// 主体widget
    this->m_centralWidget->setObjectName("MainWindowShell_centralWidget");
    this->m_centralWidget->setAutoFillBackground(true);
    this->m_centralWidget->setAttribute(Qt::WA_StyledBackground, true);
    this->m_centralWidget->setStyleSheet(R"(
        QWidget#MainWindowShell_centralWidget{
            background-color: rgba(211, 229, 247, 1);
        }
    )");
    this->m_titleLayout->addWidget(this->m_centralWidget); // 添加主体widget

    // 初始化主体layout
    this->m_centralLayout = new QVBoxLayout();// 主体layout 用于显示主体内容
    this->m_centralLayout->setContentsMargins(0, 0, 0, 0);// 设置边距为0
    this->m_centralWidget->setLayout(this->m_centralLayout);

    // 初始化选择tab
    // this->m_selectTab = new CoreControlWidgets::SelectTab();
    // this->m_centralLayout->addWidget(this->m_selectTab);
}

CoreControlWidgets::MainWindowShell::~MainWindowShell()
{
    this->m_baseWidget = nullptr;
    this->m_centralWidget = nullptr;
    this->m_customTitleBar->deleteLater();
    this->m_customTitleBar = nullptr;
    this->m_titleLayout = nullptr;
}

void CoreControlWidgets::MainWindowShell::moveEvent(QMoveEvent *event)
{
    QMainWindow::moveEvent(event);
    emit windowChanged();
}

void CoreControlWidgets::MainWindowShell::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    emit windowChanged();
}

void CoreControlWidgets::MainWindowShell::changeEvent(QEvent* event)
{
    // 先调用父类函数，保证Qt内部状态正确更新
    QMainWindow::changeEvent(event);

    // 只处理窗口状态变化事件
    if (event->type() != QEvent::WindowStateChange) {
        return;
    }

    // 1. 获取当前最新的窗口状态
    Qt::WindowStates currentState = this->windowState();
    // 2. 判断窗口是否处于「放大状态」（最大化 或 全屏，统一处理）
    bool isZoomed = (currentState & Qt::WindowMaximized) || (currentState & Qt::WindowFullScreen);
    // 3. 统一设置图标
    QIcon targetIcon = isZoomed
        ? QIcon(":/ICONS/icons/TitleIcons/_MaximizeButtonM.png")  // 放大状态：还原图标
        : QIcon(":/ICONS/icons/TitleIcons/_MaximizeButtonN.png"); // 正常状态：最大化图标

    // 只获取一次全局变量，优化性能
    GlobalVariables* gv = GLOBAL_VARIABLES;
    gv->custom_title_bar->m_btnMax->setIcon(targetIcon);
    gv->min_custom_title_bar->m_btnMax->setIcon(targetIcon);

    gv->is_max_window_showed = isZoomed;
}
