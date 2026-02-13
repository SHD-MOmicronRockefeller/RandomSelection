//
// Created by Administrator on 2026/2/13.
//

#ifndef LAYOUTWIDGET_H
#define LAYOUTWIDGET_H

#include "QtPrecompiled.h"



class LayoutWidget : public QFrame
{
    Q_OBJECT
    public: explicit LayoutWidget(QWidget *parent = nullptr);

    QGraphicsDropShadowEffect *dropShadowEffect = nullptr;

    private: void enterEvent(QEnterEvent *event) override; // 鼠标进入事件
    private: void leaveEvent(QEvent *event) override; // 鼠标离开事件
};


#endif //LAYOUTWIDGET_H