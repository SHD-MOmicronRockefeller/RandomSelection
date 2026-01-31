#include "mainWindow.h"
#include "VariablesStore/globalVariables.h"
#include "CoreControlWidgets/MainWindow/CustomTitleBar/CustomTitleBar.h"
#include "CoreControlWidgets/SelectTab/selectTab.h"

CoreControlWidgets::MainWindowShell::MainWindowShell(QWidget *parent) : QMainWindow(parent)
{
    this->m_customTitleBar = GlobalVariables::getInstance()->custom_title_bar;
    this->setObjectName("MainWindowShell");
    this->m_baseWidget = new QWidget(this);// 整个窗口的widget
    this->m_baseWidget->setObjectName("MainWindowShell_baseWidget");
    this->m_baseWidget->setAutoFillBackground(true);
    this->m_baseWidget->setAttribute(Qt::WA_StyledBackground, true);
    this->m_baseWidget->setStyleSheet(R"(
        QWidget#MainWindowShell_baseWidget{
            background-color: rgba(255, 130, 13, 1);
        }
    )");
    this->setCentralWidget(this->m_baseWidget);// 设置窗口 

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
    this->m_customTitleBar = GlobalVariables::getInstance()->custom_title_bar;
    this->m_titleLayout->addWidget(this->m_customTitleBar); // 添加自定义标题栏

    // 初始化主体widget
    this->m_centralWidget = new QWidget();// 主体widget
    this->m_centralWidget->setObjectName("MainWindowShell_centralWidget");
    this->m_centralWidget->setAutoFillBackground(true);
    this->m_centralWidget->setAttribute(Qt::WA_StyledBackground, true);
    this->m_centralWidget->setStyleSheet(R"(
        QWidget#MainWindowShell_centralWidget{
            background-color: rgba(13, 69, 255, 1);
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

void CoreControlWidgets::MainWindowShell::setWindowTitleBox()
{
    return;          
}
