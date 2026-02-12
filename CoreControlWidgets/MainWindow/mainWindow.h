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

    //title layout
    public: QVBoxLayout *m_titleLayout = nullptr;

    public: CoreControlWidgets::SelectTab* m_selectTab = nullptr;

    // 重写
    protected: void moveEvent(QMoveEvent *event) override;
    protected: void resizeEvent(QResizeEvent *event) override;

    signals: void windowChanged();
};

} // namespace CoreControlWidgets
#endif // MAINWINDOW_H