#ifndef MIDWIDGET_H
#define MIDWIDGET_H

#include "QtPrecompiled.h"

namespace CoreControlWidgets
{

namespace SelectTab_NS
{

class MidWidget : public QWidget
{
    Q_OBJECT
    public: MidWidget(QWidget *parent = 0);
    public: ~MidWidget();

    // public: static QWidget* createRatioWidget(QWidget* contentWidget, int stretchFactor);

    protected: void resizeEvent(QResizeEvent  *event) override;
    protected: void adjustFontSize();

    protected: QVBoxLayout *m_mainLayout;

    protected: QHBoxLayout *m_upLayout;
    protected: void setUpLayout();

    protected: QHBoxLayout *m_midLayout;
    protected: void setMidLayout();

    protected: QHBoxLayout *m_downLayout;
    protected: void setDownLayout();

};



} // namespace SelectTab_NS




} // namespace CoreControlWidgets




#endif // MIDWIDGET_H