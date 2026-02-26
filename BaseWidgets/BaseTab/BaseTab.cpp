#include "BaseTab.h"

#include "BaseWidgets/BaseTab/ControlList.h"

#include "BaseWidgets/BaseTab/ControlList.h"

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
    
    this->setMinimumSize(0, 0);
    
    // 设置控件列表的样式
    this->m_controlLayout = new QHBoxLayout(this);
    this->m_controlLayout->setContentsMargins(0, 0, 0, 0);
    this->m_controlLayout->setSpacing(0);
    this->m_controlLayout->setAlignment(Qt::AlignLeft);
    this->setLayout(this->m_controlLayout);
    
    
    // 添加控件列表到布局中
    this->controlList = new BaseElements::ControlList();// 创建控件列表
    this->controlList->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    this->m_controlLayout->addWidget(this->controlList);

    // 创建中心区域
    this->m_centerWidget = new QWidget();
    this->m_centerWidget->setAutoFillBackground(true);
    this->m_centerWidget->setAttribute(Qt::WA_StyledBackground, true);
    this->m_centerWidget->setObjectName("BaseTab_CenterWidget");
    this->m_centerWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->m_controlLayout->addWidget(this->m_centerWidget);
    this->m_controlLayout->setStretchFactor(this->m_centerWidget, 1);

    // 设置中心区域的样式
    this->m_centerWidget->setStyleSheet(R"(
    QWidget#BaseTab_CenterWidget{
        background-color: rgba(211, 229, 247, 1);
    }
    )");
    
    // 设置中心区域的布局
    this->m_centerLayout = new QVBoxLayout(this->m_centerWidget);
    this->m_centerLayout->setContentsMargins(0, 0, 0, 0);
    this->m_centerLayout->setSpacing(0);
    this->m_centerLayout->setAlignment(Qt::AlignTop);
    this->m_centerWidget->setLayout(this->m_centerLayout);

}

BaseWidgets::BaseTab::~BaseTab()
{
}

void BaseWidgets::BaseTab::setPage(QWidget *page)
{
    if (this->m_this_widget != nullptr){
        this->m_this_widget->hide();
        this->m_centerLayout->removeWidget(this->m_this_widget);
    }
    this->m_this_widget = page;
    this->m_centerLayout->addWidget(page);
    this->m_this_widget->show();
    this->m_centerLayout->setStretchFactor(this->m_this_widget, 1);
}

bool BaseWidgets::BaseTab::isPage(QWidget* page) {
    return this->m_this_widget == page;
}
