//
// Created by Administrator on 2026/2/17.
//

#ifndef SLCF_MIDBOX_H
#define SLCF_MIDBOX_H

#include "QtPrecompiled.h"
#include "CoreCalculation/DoubleFileClass/ReadFile/readFile.h"

namespace CoreControlWidgets {

namespace SelectTab_NS {

class importButton : public QPushButton
{
    public: explicit importButton(QWidget *parent = nullptr);
    public: CoreCalculation::readDirt::_file file;
};


class Slcf_midBox : public QGroupBox
{
    public: explicit Slcf_midBox(QWidget *parent = nullptr);
    public: explicit Slcf_midBox(QString title, QWidget *parent = nullptr);

    public: QVBoxLayout *mainLayout = nullptr;
    private: void init();

    public: void cleanButton();
    public: void addButton(CoreCalculation::readDirt::_file file);
};


}

}   // namespace CoreControlWidgets

#endif //SLCF_MIDBOX_H