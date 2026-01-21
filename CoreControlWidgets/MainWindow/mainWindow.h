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
    public: ~MainWindowShell();

    // widget
    public: QWidget* m_baseWidget = nullptr;
    public: QWidget* m_centralWidget = nullptr;

    //设置标题栏
    public: MainWindow::CustomTitleBar *&m_customTitleBar = Variables::customTitleBar;
    public: void setWindowTitleBox();

    //title layout
    private: QVBoxLayout *m_titleLayout = nullptr;

    // override
};

} // namespace CoreControlWidgets
#endif // MAINWINDOW_H