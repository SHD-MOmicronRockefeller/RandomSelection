// AspectRatioWidget.h
#ifndef ASPECTRATIOWIDGET_H
#define ASPECTRATIOWIDGET_H

#include "QtPrecompiled.h"

namespace BaseWidgets {

class AspectRatioWidget : public QWidget
{
    Q_OBJECT
    // ratio: 宽高比（例：16:9传16.0/9.0，4:3传4.0/3.0）
    public: AspectRatioWidget(QWidget *parent = nullptr, double ratio = 1.0);
    // 设置要包裹的核心控件
    public: void setContentWidget(QWidget *widget);

    protected: void resizeEvent(QResizeEvent *event) override;

    protected: double m_aspectRatio;    // 宽高比（宽/高）
    protected: QWidget *m_contentWidget = nullptr; // 中间核心控件（MidWidget）
};

} // BaseWidgets

#endif // ASPECTRATIOWIDGET_H
