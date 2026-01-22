#ifndef MIDWIDGET_H
#define MIDWIDGET_H

#include "QtPrecompiled.h"

namespace CoreControlWidgets
{

namespace SelectTab_NS
{

class Select_Page : public QWidget
{
    Q_OBJECT
    public: Select_Page(QWidget *parent = 0);
    public: ~Select_Page();

    protected: QHBoxLayout *m_mainLayout;

    protected: QVBoxLayout *m_upLayout;
    protected: void setUpLayout();

    protected: QVBoxLayout *m_midLayout;
    protected: void setMidLayout();

    protected: QVBoxLayout *m_downLayout;
    protected: void setDownLayout();

};



} // namespace SelectTab_NS




} // namespace CoreControlWidgets




#endif // MIDWIDGET_H