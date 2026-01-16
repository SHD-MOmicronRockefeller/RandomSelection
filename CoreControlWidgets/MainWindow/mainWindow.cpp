#include "mainWindow.h"

CoreControlWidgets::MainWindowShell::MainWindowShell(QWidget *parent) : QMainWindow(parent)
{
    this->setWindowTitle("Core Control Widgets");
    this->setGeometry(100, 100, 800, 600);
    return;
}
