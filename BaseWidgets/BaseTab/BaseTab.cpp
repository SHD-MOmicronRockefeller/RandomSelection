#include "BaseTab.h"

BaseWidgets::BaseTab::BaseTab(QWidget *parent) : QWidget(parent)
{
    this->setAutoFillBackground(true);
    this->setAttribute(Qt::WA_StyledBackground, true);

    this->setObjectName("BaseTab");
    this->setStyleSheet(R"(
    QWidget#BaseTab{
        background-color: rgba(243, 35, 191, 1);
    }
    )");
    
    
    // 设置控件列表的样式
    this->m_controLayout = new QHBoxLayout(this);
    this->m_controLayout->setContentsMargins(10, 10, 10, 10);
    this->m_controLayout->setSpacing(0);
    this->m_controLayout->setAlignment(Qt::AlignLeft);
    this->setLayout(this->m_controLayout);
    
    
    // 添加控件列表到布局中
    this->controlList = new BaseElements::ControlList();// 创建控件列表
    this->m_controLayout->addWidget(this->controlList);

    // 创建中心区域
    this->m_centerWidget = new QWidget();
    this->m_centerWidget->setAutoFillBackground(true);
    this->m_centerWidget->setAttribute(Qt::WA_StyledBackground, true);
    this->m_centerWidget->setObjectName("BaseTab_CenterWidget");
    this->m_controLayout->addWidget(this->m_centerWidget);
    this->m_controLayout->setStretchFactor(this->m_centerWidget, 1);

    // 设置中心区域的样式
    this->m_centerWidget->setStyleSheet(R"(
    QWidget#BaseTab_CenterWidget{
        background-color: rgba(16, 195, 240, 1);
    }
    )");
    
    // 设置中心区域的布局
    this->m_centerLayout = new QVBoxLayout(this->m_centerWidget);
    this->m_centerLayout->setContentsMargins(10, 10, 10, 10);
    this->m_centerLayout->setSpacing(0);
    this->m_centerLayout->setAlignment(Qt::AlignTop);
    this->m_centerWidget->setLayout(this->m_centerLayout);

}

BaseWidgets::BaseTab::~BaseTab()
{
}
