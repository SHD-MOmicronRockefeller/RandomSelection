#include "ControlList.h"

BaseWidgets::ControlList::ControlList(QWidget *parent) : QWidget(parent)
{
    this->mainLayout = new QVBoxLayout(this);

    this->initLayout();
    this->initWidgets();
    this->initStyle();
}

BaseWidgets::ControlList::~ControlList()
{
    this->mainLayout->deleteLater();
    this->mainLayout = nullptr;
}

void BaseWidgets::ControlList::initLayout()
{
}

void BaseWidgets::ControlList::initWidgets()
{
}

void BaseWidgets::ControlList::initStyle()
{
}
