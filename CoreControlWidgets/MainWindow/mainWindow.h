#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "VariablesStore/variables.h"
#include "QtPrecompiled.h"
#include "CoreControlWidgets/MainWindow/CustomTitleBar/CustomTitleBar.h"

// 声明MainWindowShell类
namespace MainWindow {
class CustomTitleBar;
}
// CustomTitleBar类声明
namespace Variables{
extern CoreControlWidgets::MainWindow::CustomTitleBar* customTitleBar;
}

namespace CoreControlWidgets {

class MainWindowShell : public QMainWindow{
    Q_OBJECT
    // 构造函数
    public: explicit MainWindowShell(QWidget *parent = nullptr);

    // widget
    public: QWidget* m_centralWidget = nullptr;

    //设置标题栏
    public: MainWindow::CustomTitleBar *&m_titleBar = Variables::customTitleBar;
    public: void setWindowTitleBox();

    // override
};

} // namespace CoreControlWidgets
#endif // MAINWINDOW_H