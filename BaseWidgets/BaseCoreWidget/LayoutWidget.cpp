//
// Created by Administrator on 2026/2/13.
//

#include "LayoutWidget.h"

LayoutWidget::LayoutWidget(QWidget* parent) : QFrame(parent)
{
    setMouseTracking(true);

    this->setObjectName("LayoutWidget");
    this->setStyleSheet(R"(
        QFrame#LayoutWidget{
            background: #fcfdfe;
            border: none;
            border-radius: 15px;
        })");
    dropShadowEffect = new QGraphicsDropShadowEffect(this);
    dropShadowEffect->setBlurRadius(10);
    dropShadowEffect->setColor(QColor(32, 32, 32, 64));
    dropShadowEffect->setOffset(0, 0);
    setGraphicsEffect(dropShadowEffect);
}

void LayoutWidget::enterEvent(QEnterEvent* event) {
    Q_UNUSED(event);
    dropShadowEffect->setBlurRadius(16);
    dropShadowEffect->setColor(QColor(71, 160, 255)); // rgb(71, 160, 255)
    dropShadowEffect->setOffset(0, 0);
}

void LayoutWidget::leaveEvent(QEvent* event) {
    Q_UNUSED(event);
    dropShadowEffect->setBlurRadius(10);
    dropShadowEffect->setColor(QColor(32, 32, 32, 64));
    dropShadowEffect->setOffset(0, 0);
}
