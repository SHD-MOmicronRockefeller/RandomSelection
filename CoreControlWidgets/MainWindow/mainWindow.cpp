#include "mainWindow.h"

CoreControlWidgets::MainWindowShell::MainWindowShell(QWidget *parent) : QMainWindow(parent)
{
    // 设置窗口widget
    this->m_centralWidget = new QWidget(this);
    this->setCentralWidget(this->m_centralWidget);

    // 设置窗口大小
    this->setGeometry(100, 100, 800, 600);
    this->centralWidget()->setContentsMargins(0, 0, 0, 0);

    // 设置窗口标签
    //this->setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::WindowCloseButtonHint | Qt::WindowMaximizeButtonHint);
    //this->setWindowFlags(Qt::FramelessWindowHint | Qt::FramelessWindowHint);
    //this->setAttribute(Qt::WA_TranslucentBackground, true);
    this->setStyleSheet("QMainWindow{border: none; background-color: #2c7eca;}");
    this->setWindowTitleBox();
}

void CoreControlWidgets::MainWindowShell::setWindowTitleBox()
{
    // 设置窗口布局
    //this->m_titleBar = Variables::customTitleBar;
    //this->m_centralWidget->setContentsMargins(0, 0, 0, 0);
    return;          
}
