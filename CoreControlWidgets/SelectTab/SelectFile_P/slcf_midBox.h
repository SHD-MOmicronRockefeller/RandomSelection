//
// Created by Administrator on 2026/2/17.
//

#ifndef SLCF_MIDBOX_H
#define SLCF_MIDBOX_H

#include "QtPrecompiled.h"

namespace CoreControlWidgets {

namespace SelectTab_NS {

class importButton : public QPushButton
{
    public: explicit importButton(QWidget *parent = nullptr);
    public: QString filePath = "";
};


class slcf_midBox : public QGroupBox
{
    public: explicit slcf_midBox(QWidget *parent = nullptr);
    public: explicit slcf_midBox(QString title, QWidget *parent = nullptr);

    private: void init();
    public: QVBoxLayout *mainLayout;
};


}

}   // namespace CoreControlWidgets

#endif //SLCF_MIDBOX_H