#ifndef APPLICATIONSHELL_H
#define APPLICATIONSHELL_H

#include "QtPrecompiled.h"

namespace ApplicationClass {

class ApplicationShell : public QApplication{
    Q_OBJECT
public:
    ApplicationShell(int& argc, char** argv);
};

} // namespace ApplicationClass

#endif // APPLICATIONSHELL_H