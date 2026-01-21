
#include "StatusBar.h"

CoreControlWidgets::MainWindow::StatusBar::StatusBar(QWidget* parent) : QWidget(parent) {
    this->setObjectName("StatusBar");
    this->setAutoFillBackground(true);
    this->setAttribute(Qt::WA_StyledBackground, true);

    this->setStyleSheet(R"(
        QWidget#StatusBar{
            background-color: rgba(13, 255, 182, 1);
        }
    )");
    
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    this->setFixedHeight(30); 
    
    m_leftArea = new QWidget(this);
    leftLayout = new QHBoxLayout(m_leftArea);
    leftLayout->setContentsMargins(5, 0, 0, 0); 
    leftLayout->setSpacing(5); 
    leftLayout->setAlignment(Qt::AlignLeft | Qt::AlignVCenter); 
    m_leftArea->setLayout(leftLayout);
    
    m_rightArea = new QWidget(this);
    rightLayout = new QHBoxLayout(m_rightArea);
    rightLayout->setContentsMargins(0, 0, 5, 0); 
    rightLayout->setSpacing(5); 
    rightLayout->setAlignment(Qt::AlignRight | Qt::AlignVCenter); 
    m_rightArea->setLayout(rightLayout);
}

CoreControlWidgets::MainWindow::StatusBar::~StatusBar() {
    
}



void CoreControlWidgets::MainWindow::StatusBar::addLeftWidget(QWidget* widget) {
    if (!widget || leftWidgets.contains(widget)) return;
    leftLayout->addWidget(widget);
    leftWidgets.insert(widget, widget); 
}


void CoreControlWidgets::MainWindow::StatusBar::removeLeftWidget(QWidget* widget, bool deleteWidget) {
    if (!widget || !leftWidgets.contains(widget)) {
        return; 
    }
    
    leftLayout->removeWidget(widget);
    widget->setParent(nullptr);
    leftWidgets.remove(widget);
    if (deleteWidget) {
        widget->deleteLater();
    }
}

void CoreControlWidgets::MainWindow::StatusBar::addRightWidget(QWidget* widget) {
    if (!widget || rightWidgets.contains(widget)) return;
    rightLayout->addWidget(widget);
    rightWidgets.insert(widget, widget); 
}

void CoreControlWidgets::MainWindow::StatusBar::removeRightWidget(QWidget* widget, bool deleteWidget) {
    if (!widget || !rightWidgets.contains(widget)) {
        return; 
    }

    rightLayout->removeWidget(widget);
    widget->setParent(nullptr);
    rightWidgets.remove(widget);
    if (deleteWidget) {
        widget->deleteLater();
    }
}

void CoreControlWidgets::MainWindow::StatusBar::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    m_leftArea->setGeometry(0, 0, this->width(), this->height());
    m_rightArea->setGeometry(0, 0, this->width(), this->height());
}
