#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "VariablesStore/variables.h"
#include "QtPrecompiled.h"
#include "CoreControlWidgets/MainWindow/CustomTitleBar.h"
namespace CoreControlWidgets {

class MainWindowShell : public QMainWindow{
    Q_OBJECT
public:
    // 构造函数
    explicit MainWindowShell(QWidget *parent = nullptr);

    // widget
    QWidget* centralWidget = nullptr;

    //设置标题栏
    QVBoxLayout* mainLayout = nullptr;
    MainWindow::CustomTitleBar *titleBar;
    void setWindowTitleBox();

    // override
};

} // namespace CoreControlWidgets
#endif // MAINWINDOW_H