#include "ControlList.h"

BaseWidgets::BaseElements::ControlList::ControlList(QWidget *parent) : QWidget(parent)
{
    this->setObjectName("ControlList");
    this->m_centerLayout = new QVBoxLayout(this);
    this->setLayout(this->m_centerLayout);
    this->m_centerLayout->setContentsMargins(0, 0, 0, 0);
    this->m_centerLayout->setSpacing(0);
    this->m_centerLayout->setAlignment(Qt::AlignTop);

    this->setStyleSheet(R"(
    QWidget#ControlList{
        background-color:rgba(243, 243, 35, 1);
        border:none;
    }
    )");
}

BaseWidgets::BaseElements::ControlList::~ControlList()
{
    this->m_centerLayout = nullptr;
}

QLabel * BaseWidgets::BaseElements::ControlList::pushLable(QLabel *lbl)
{
    lbl->setStyleSheet(R"(
    QLabel{
        background-color:transparent;
        color:black;
        border:none;
        padding:5px;
        font-size:14px;
    }
    )");
    this->m_centerLayout->addWidget(lbl);
    return lbl;
}

QPushButton * BaseWidgets::BaseElements::ControlList::pushButton(QPushButton *btn)
{
    btn->setStyleSheet(R"(
    QPushButton{
        background-color:transparent;
        color:black;
        border:none;
        padding:5px;
        font-size:14px;
    }
    QPushButton:hover{
        background-color:rgb(200, 200, 200);
    }
    )");
    this->m_centerLayout->addWidget(btn);
    return btn;
}
