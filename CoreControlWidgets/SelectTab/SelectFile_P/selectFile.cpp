#include "selectFile.h"

CoreControlWidgets::SelectTab_NS::SelectFile_Page::SelectFile_Page(QWidget *parent): QWidget(parent)
{
    this->m_centerLayout = new QHBoxLayout();
    this->m_centerLayout->setContentsMargins(5, 10, 5, 5);
    this->m_centerLayout->setSpacing(10);
    this->m_centerLayout->setAlignment(Qt::AlignTop);
    this->setLayout(this->m_centerLayout);


    this->m_thisFileGroupBox = new QGroupBox(this);
    this->m_centerLayout->addWidget(this->m_thisFileGroupBox);
    
    
    this->m_tempFileGroupBox = new QGroupBox(this);
    this->m_centerLayout->addWidget(this->m_tempFileGroupBox);
    
    
    this->m_thatFileGroupBox = new QGroupBox(this);
    this->m_centerLayout->addWidget(this->m_thatFileGroupBox);



}

CoreControlWidgets::SelectTab_NS::SelectFile_Page::~SelectFile_Page()
{
}
