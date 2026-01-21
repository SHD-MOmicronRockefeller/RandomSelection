#include "mainWindow.h"

CoreControlWidgets::MainWindowShell::MainWindowShell(QWidget *parent) : QMainWindow(parent)
{
    this->setObjectName("MainWindowShell");
    this->m_baseWidget = new QWidget(this);// 整个窗口的widget
    this->setCentralWidget(this->m_baseWidget);// 设置窗口 

    // 设置窗口大小
    this->setGeometry(100, 100, 800, 600);
    this->centralWidget()->setContentsMargins(0, 0, 0, 0);

    // 设置窗口标签
    //this->setWindowFlags(Qt::Window | Qt::WindowTitleHint);
    this->setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
    //this->setAttribute(Qt::WA_TranslucentBackground, true);
    //this->setStyleSheet("QMainWindow#MainWindowShell{border: none; background-color: rgb(17, 112, 208);}");
    this->setStyleSheet(R"(
        QMainWindow#MainWindowShell{
            border: none;
            background-color: rgb(17, 112, 208);
        }
    )");

    // 初始化title layout
    this->m_titleLayout = new QVBoxLayout(this->m_baseWidget);// 标题栏layout 用于显示title bar
    this->m_titleLayout->setContentsMargins(0, 0, 0, 0);// 设置边距为0

    // 初始化自定义标题栏
    this->m_customTitleBar = Variables::customTitleBar;// 设置自定义标题栏
    this->m_titleLayout->addWidget(this->m_customTitleBar); // 添加自定义标题栏

    // 初始化主体widget
    this->m_centralWidget = new QWidget();// 主体widget
    this->m_titleLayout->addWidget(this->m_centralWidget); // 添加主体widget

    // 初始化主体layout
    this->m_centralLayout = new QVBoxLayout(this->m_centralWidget);// 主体layout 用于显示主体内容
    this->m_centralLayout->setContentsMargins(0, 0, 0, 0);// 设置边距为0

    // 初始化选择tab
    this->m_selectTab = new CoreControlWidgets::SelectTab();
    this->m_centralLayout->addWidget(this->m_selectTab);
}

CoreControlWidgets::MainWindowShell::~MainWindowShell()
{
    this->m_baseWidget = nullptr;
    this->m_centralWidget = nullptr;
    this->m_customTitleBar->deleteLater();
    this->m_customTitleBar = nullptr;
    this->m_titleLayout = nullptr;
}

void CoreControlWidgets::MainWindowShell::setWindowTitleBox()
{
    return;          
}
