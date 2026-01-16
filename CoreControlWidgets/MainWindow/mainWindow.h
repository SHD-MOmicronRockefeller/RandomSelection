#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "QtPrecompiled.h"
namespace CoreControlWidgets {

class MainWindowShell : public QMainWindow{
    Q_OBJECT
public:
    // 构造函数
    explicit MainWindowShell(QWidget *parent = nullptr);
};

} // namespace CoreControlWidgets
#endif // MAINWINDOW_H