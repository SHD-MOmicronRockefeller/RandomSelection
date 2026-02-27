//
// Created by Administrator on 2026/2/26.
//

#include "listSetGroup.h"

#include "CoreCalculation/SelectTabFunc/OptionList.hpp"
#include "listSetOption.h"
#include "BaseWidgets/BaseCoreWidget/CollapsibleWidget.h"

CoreControlWidgets::SelectTab_NS::ListSetGroup::ListSetGroup(QString group, CoreCalculation::OptionList optionList,QWidget *parent)
: LayoutWidget(parent)
{
    // 标题布局
    this->titleLayouts = new QVBoxLayout;
    titleLayouts->setContentsMargins(10, 10, 10, 10);
    titleLayouts->setSpacing(0);
    this->setLayout(titleLayouts);

    // 标题
    QFrame* titleFrame = new QFrame;
    titleLayouts->addWidget(titleFrame);
    QHBoxLayout* titleLayout = new QHBoxLayout;
    titleFrame->setLayout(titleLayout);

    QFont font;
    font.setPointSize(15);
    font.setBold(true);

    // 标题：组名
    QLabel* groupName = new QLabel("组："+group);
    groupName->setFont(font);
    titleLayout->addWidget(groupName);

    // 成员数量
    QLabel* memberCount = new QLabel("成员数量: "+QString::number(optionList.findByGroup(group).size()));
    memberCount->setFont(font);
    titleLayout->addWidget(memberCount);

    // 主要内容框架
    this->mainFrame = new QFrame;
    // titleLayouts->addWidget(mainFrame); // 注释掉，使用折叠按钮

    // 折叠按钮
    CollapsibleWidget* collapsibleWidget = new CollapsibleWidget("> 设置来自 "+group+" 的选项");
    collapsibleWidget->setContentWidget(mainFrame);
    titleLayouts->addWidget(collapsibleWidget); // 使用折叠按钮

    // 主要内容布局
    this->mainLayout = new QVBoxLayout;
    this->mainFrame->setLayout(this->mainLayout);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(5);
    mainLayout->setAlignment(Qt::AlignTop);

    auto optionList_Group = optionList.findByGroup(group);

    unsigned int VLayoutCount = optionList_Group.size() / 8;
    unsigned int remainder = optionList_Group.size() % 8;

    buttonList.clear();

    for (unsigned int i = 0; i < VLayoutCount; i++) {
        QHBoxLayout* VLayout = new QHBoxLayout;
        mainLayout->addLayout(VLayout);
        for (unsigned int j = 0; j < 8; j++) {
            ListSetOption* option = new ListSetOption(optionList_Group[i * 8 + j]);
            VLayout->addWidget(option, 1);
            buttonList.append(option);
        }
    }
    QHBoxLayout* VLayout = new QHBoxLayout;
    mainLayout->addLayout(VLayout);
    for (unsigned int j = 0; j < remainder; j++) {
        ListSetOption* option = new ListSetOption(optionList_Group[VLayoutCount * 8 + j]);
        VLayout->addWidget(option, 1);
        buttonList.append(option);
    }
    VLayout->addStretch(8-remainder);
}
