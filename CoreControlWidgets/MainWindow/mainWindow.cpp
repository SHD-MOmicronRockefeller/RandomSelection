#include "mainWindow.h"

CoreControlWidgets::MainWindowShell::MainWindowShell(QWidget *parent) : QMainWindow(parent)
{
    // 设置窗口widget
    this->centralWidget = new QWidget(this);
    this->setCentralWidget(this->centralWidget);

    //
    this->setGeometry(100, 100, 800, 600);

    // 设置窗口标签
    this->setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
    //this->setWindowFlags(Qt::FramelessWindowHint | Qt::FramelessWindowHint);
    //this->setAttribute(Qt::WA_TranslucentBackground, true);
    this->setStyleSheet("QMainWindow{border: none; background-color: white;}");
    this->setWindowTitleBox();
}

void CoreControlWidgets::MainWindowShell::setWindowTitleBox()
{
    // 设置窗口标题栏
    this->titleBar = new MainWindow::CustomTitleBar(this);

    // 设置窗口布局
    this->mainLayout = new QVBoxLayout(this->centralWidget);
    this->mainLayout->setContentsMargins(0, 0, 0, 0);
    this->mainLayout->setSpacing(0);
    this->mainLayout->addWidget(this->titleBar);
    //this->mainLayout->addWidget(new QWidget(Variables::mainWindowShell));
    this->mainLayout->addStretch();
    this->centralWidget->layout()->update();
    return;
    return;
}
