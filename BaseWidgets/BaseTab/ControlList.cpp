#include "ControlList.h"

BaseWidgets::BaseElements::ControlList::ControlList(QWidget *parent) : QWidget(parent)
{
    this->setAutoFillBackground(true);
    this->setAttribute(Qt::WA_StyledBackground, true);
    this->setObjectName("ControlList");

    this->m_centerLayout = new QVBoxLayout(this);
    this->setLayout(this->m_centerLayout);

    this->m_centerLayout->setContentsMargins(0, 0, 0, 0);
    this->m_centerLayout->setSpacing(0);
    this->m_centerLayout->setAlignment(Qt::AlignTop);

    this->setStyleSheet(R"(
    QWidget#ControlList{
        background-color:rgba(243, 243, 35, 1);
    }
    )");
}

BaseWidgets::BaseElements::ControlList::~ControlList()
{
    this->m_centerLayout = nullptr;
}

QLabel * BaseWidgets::BaseElements::ControlList::pushLable(QLabel *lbl)
{
    lbl->setAutoFillBackground(true);
    lbl->setAttribute(Qt::WA_StyledBackground, true);
    lbl->setStyleSheet(R"(
    QLabel{
        background-color:transparent;
        color:rgba(92, 92, 92, 1);
        border:none;
        padding:5px;
        font-size:12px;
    }
    )");
    lbl->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    this->m_centerLayout->addWidget(lbl);
    return lbl;
}

QPushButton * BaseWidgets::BaseElements::ControlList::pushButton(QPushButton *btn)
{
    btn->setAutoFillBackground(true);
    btn->setAttribute(Qt::WA_StyledBackground, true);
    btn->setStyleSheet(R"(
    QPushButton{
        background-color:transparent;
        color:black;
        border:none;
        padding:5px;
        font-size:14px;
        padding-left:12px;
        padding-right:12px;
    }
    QPushButton:hover{
        background-color:rgb(200, 200, 200);
    }
    )");
    this->m_centerLayout->addWidget(btn);
    return btn;
}
