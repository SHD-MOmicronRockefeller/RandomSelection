#include "Initialization.h"

namespace Initialization {

void initialize_values()
{
    Variables::mainWindowShell = new CoreControlWidgets::MainWindowShell();
    Variables::customTitleBar = new CoreControlWidgets::MainWindow::CustomTitleBar(Variables::mainWindowShell);
}

void initialize_settings()
{
    Variables::mainWindowShell->resize(Variables::WINDOW_WIDTH, Variables::WINDOW_HEIGHT);
    Variables::mainWindowShell->show();
}

} // namespace Initialization