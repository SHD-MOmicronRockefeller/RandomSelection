#ifndef TOGGLETOPMOST_H
#define TOGGLETOPMOST_H

#include "QtPrecompiled.h"

#include "ClassSpace.h"

namespace ModWidgets {


class ToggleTopmost : public QPushButton {
    Q_OBJECT
    public: ToggleTopmost(QWidget *parent = 0);

    public: void changeWindowTopmost();
    public: void changeColor();
    public: void setGreenColor();
    public: void setRedColor();
};

} // namespace ModWidgets



#endif