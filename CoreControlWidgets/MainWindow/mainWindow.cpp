#include "mainWindow.h"

CoreControlWidgets::MainWindowShell::MainWindowShell(QWidget *parent) : QMainWindow(parent)
{
    // 设置窗口widget
    this->m_baseWidget = new QWidget(this);

    this->setCentralWidget(this->m_baseWidget);

    // 初始化title layout
    this->m_titleLayout = new QVBoxLayout(this->m_baseWidget);

    this->m_customTitleBar = Variables::customTitleBar;

    // 设置窗口大小
    this->setGeometry(100, 100, 800, 600);
    this->centralWidget()->setContentsMargins(0, 0, 0, 0);

    // 设置窗口标签
    //this->setWindowFlags(Qt::Window | Qt::WindowTitleHint);
    this->setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
    //this->setAttribute(Qt::WA_TranslucentBackground, true);
    this->setStyleSheet("QMainWindow{border: none; background-color: #2c7eca;}");
    this->setWindowTitleBox();
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
    this->m_titleLayout->setContentsMargins(0, 0, 0, 0);
    this->m_titleLayout->addWidget(this->m_customTitleBar);

    this->m_centralWidget = new QWidget(this);
    this->m_titleLayout->addWidget(this->m_centralWidget);

    return;          
}
