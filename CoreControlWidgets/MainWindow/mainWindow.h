#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// #include "VariablesStore/globalVariables.h"
#include "QtPrecompiled.h"


// 声明MainWindowShell类
#include "ClassSpace.h"

namespace CoreControlWidgets {

class MainWindowShell : public QMainWindow{
    Q_OBJECT
    // 构造函数
    public: explicit MainWindowShell(QWidget *parent = nullptr);
    public: ~MainWindowShell();

    // widget
    public: QWidget* m_baseWidget = nullptr;
    public: QWidget* m_centralWidget = nullptr;
    public: QVBoxLayout* m_centralLayout = nullptr;

    //设置标题栏
    public: MainWindow::CustomTitleBar *m_customTitleBar = nullptr;
    public: void setWindowTitleBox();

    //title layout
    public: QVBoxLayout *m_titleLayout = nullptr;

    public: CoreControlWidgets::SelectTab* m_selectTab = nullptr;
};

} // namespace CoreControlWidgets
#endif // MAINWINDOW_H