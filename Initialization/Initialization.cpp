#include "Initialization.h"

namespace Initialization {

void initialize_values()
{
    Variables::mainWindowShell = new CoreControlWidgets::MainWindowShell();
}

void initialize_settings()
{
    Variables::mainWindowShell->show();
}

} // namespace Initialization