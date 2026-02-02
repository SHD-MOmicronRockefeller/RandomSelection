#include "slc_midWidget.h"

CoreControlWidgets::SelectTab_NS::MidWidget::MidWidget(QWidget *parent) : QWidget(parent)
{
    this->setAutoFillBackground(true);
    this->setAttribute(Qt::WA_StyledBackground, true);
    this->setObjectName("MidWidget");
    this->setStyleSheet(R"(
    QWidget#MidWidget{
        background-color: rgba(201, 201, 201, 1);
    }
    )");
    this->m_mainLayout = new QHBoxLayout(this);
    this->m_mainLayout->setContentsMargins(0, 0, 0, 0);
    this->m_mainLayout->setSpacing(0);

    this->setUpLayout();
    this->setMidLayout();
    this->setDownLayout();
}

CoreControlWidgets::SelectTab_NS::MidWidget::~MidWidget()
{
}

void CoreControlWidgets::SelectTab_NS::MidWidget::setUpLayout()
{
    this->m_upLayout = new QVBoxLayout();
    this->m_upLayout->setContentsMargins(0, 0, 0, 0);
    this->m_upLayout->setSpacing(0);

    //this->m_upLayout->addWidget();

    this->m_mainLayout->addLayout(this->m_upLayout);
}

void CoreControlWidgets::SelectTab_NS::MidWidget::setMidLayout()
{
    this->m_midLayout = new QVBoxLayout();
    this->m_midLayout->setContentsMargins(0, 0, 0, 0);
    this->m_midLayout->setSpacing(0);

    this->m_midLayout->addWidget(new QLabel("Middle Widget"));
    
    this->m_mainLayout->addLayout(this->m_midLayout);
}

void CoreControlWidgets::SelectTab_NS::MidWidget::setDownLayout()
{
    this->m_downLayout = new QVBoxLayout();
    this->m_downLayout->setContentsMargins(0, 0, 0, 0);
    this->m_downLayout->setSpacing(0);

    //this->m_downLayout->addWidget();

    this->m_mainLayout->addLayout(this->m_downLayout);
}
