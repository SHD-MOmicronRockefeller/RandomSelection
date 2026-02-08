#include "slc_midWidget.h"

#include "BaseWidgets/BaseCoreWidget/TinyWidget/AutoFitButton.h"
#include "BaseWidgets/BaseCoreWidget/TinyWidget/AutoFitLabel.h"

#define ButtonSize 1
#define LableSize 6

// static QWidget* createRatioWidget(QWidget* contentWidget) {
//     QWidget* container = new QWidget();
//     // 容器尺寸策略：强制按拉伸因子分配空间
//     container->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//     // 替代setMinimumSizeHint：直接设置容器的最小尺寸为0（核心等价效果）
//     container->setMinimumSize(0, 0);

//     // 容器内布局：填满整个容器，无间距
//     QHBoxLayout* containerLayout = new QHBoxLayout(container);
//     containerLayout->setContentsMargins(0, 0, 0, 0);
//     containerLayout->setSpacing(0);
//     containerLayout->addWidget(contentWidget);

//     // 替代setMinimumSizeHint：直接设置内容控件的最小尺寸为0（禁用文字撑大）
//     contentWidget->setMinimumSize(0, 0);
//     contentWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

//     return container;
// }

CoreControlWidgets::SelectTab_NS::MidWidget::MidWidget(QWidget *parent) : QWidget(parent)
{
    this->setAutoFillBackground(true);
    this->setAttribute(Qt::WA_StyledBackground, true);
    this->setObjectName("MidWidget");
    this->setStyleSheet(R"(
    QWidget#MidWidget{
        background-color: transparent;
    }
    )");
    this->m_mainLayout = new QVBoxLayout(this);
    this->m_mainLayout->setContentsMargins(0, 0, 0, 0);
    this->m_mainLayout->setSpacing(0);

    this->setUpLayout();
    this->setMidLayout();
    this->setDownLayout();
}

CoreControlWidgets::SelectTab_NS::MidWidget::~MidWidget()
{
}

void CoreControlWidgets::SelectTab_NS::MidWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    adjustFontSize(); // 尺寸变了就重新计算字体大小
}

void CoreControlWidgets::SelectTab_NS::MidWidget::adjustFontSize()
{
}


/// 顶控件
void CoreControlWidgets::SelectTab_NS::MidWidget::setUpLayout()
{
    this->m_upLayout = new QHBoxLayout();
    this->m_upLayout->setContentsMargins(0, 0, 0, 0);
    this->m_upLayout->setSpacing(0);

    BaseWidgets::AutoFitLabel *label = new BaseWidgets::AutoFitLabel("NUM> 123 / 123");
    label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    label->setAlignment(Qt::AlignLeft | Qt::AlignBottom);
    this->m_upLayout->addWidget(label);
    this->m_upLayout->setStretchFactor(label, LableSize - 4);

    BaseWidgets::AutoFitLabel *spring = new BaseWidgets::AutoFitLabel("");
    spring->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->m_upLayout->addWidget(spring);
    this->m_upLayout->setStretchFactor(spring, 4);

    BaseWidgets::AutoFitButton *button = new BaseWidgets::AutoFitButton("︽");
    button->setFont(QFont("Microsoft YaHei", 24, QFont::Bold));
    button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    button->setMinimumSize(0, 0);
    this->m_upLayout->addWidget(button);
    this->m_upLayout->setStretchFactor(button, ButtonSize);

    // BaseWidgets::AutoFitButton *button = new BaseWidgets::AutoFitButton("︽");
    // button->setFont(QFont("Microsoft YaHei", 24, QFont::Bold));
    // // button->setMinimumSize(0, 0);
    // QWidget* buttonContainer = createRatioWidget(button);
    // this->m_upLayout->addWidget(buttonContainer);
    // this->m_upLayout->setStretchFactor(buttonContainer, 1);


    this->m_mainLayout->addLayout(this->m_upLayout);
    this->m_mainLayout->setStretchFactor(this->m_upLayout, 3);
}


// 中层控件
void CoreControlWidgets::SelectTab_NS::MidWidget::setMidLayout()
{
    this->m_midLayout = new QHBoxLayout();
    this->m_midLayout->setContentsMargins(0, 0, 0, 0);
    this->m_midLayout->setSpacing(0);
    this->m_upLayout->setSizeConstraint(QLayout::SetNoConstraint);

    BaseWidgets::AutoFitLabel *label = new BaseWidgets::AutoFitLabel("你名字六个字");
    label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->m_midLayout->addWidget(label);
    this->m_midLayout->setStretchFactor(label, LableSize);

    BaseWidgets::AutoFitButton *button = new BaseWidgets::AutoFitButton("选\n择");
    button->setFont(QFont("Microsoft YaHei", 36, QFont::Bold));
    button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    label->setStyleSheet(R"(
        QLabel {
            /* 基础样式 - 白色背景 + 深色文字，和按钮统一色调 */
            background-color: #FFFFFF;
            color: #333333;
            /* font-size: 14px; */
            padding: 6px 12px; /* 和按钮内边距一致，对齐布局 */
            border: 1px solid transparent; /* 透明边框，避免和按钮排版错位 */
            border-radius: 3px; /* 和按钮圆角一致 */
        }

        /* 可选：给标签添加选中/焦点样式（若需要交互） */
        QLabel:focus {
            border: 1px solid #E0F0FF; /* 和按钮悬停边框颜色一致 */
            outline: none; /* 去除默认焦点框 */
        }
    )");
    this->m_midLayout->addWidget(button);
    this->m_midLayout->setStretchFactor(button, ButtonSize);
    
    this->m_mainLayout->addLayout(this->m_midLayout);
    this->m_mainLayout->setStretchFactor(this->m_midLayout, 10);
}


// 底控件
void CoreControlWidgets::SelectTab_NS::MidWidget::setDownLayout()
{
    this->m_downLayout = new QHBoxLayout();
    this->m_downLayout->setContentsMargins(0, 0, 0, 0);
    this->m_downLayout->setSpacing(0);

    BaseWidgets::AutoFitLabel *label = new BaseWidgets::AutoFitLabel(
        "选择对象：人人人人  序号：xxx\n权重：xxxx/xxxxxx/xxxxxx | 概率：xxx.xxx%/xxx.xxx% | 抽取次数：xxxx/xxxxx");
    label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    label->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    this->m_downLayout->addWidget(label);
    this->m_downLayout->setStretchFactor(label, LableSize);

    BaseWidgets::AutoFitButton *button = new BaseWidgets::AutoFitButton("︾");
    //QPushButton *button = new QPushButton("︾");
    button->setFont(QFont("Microsoft YaHei", 24, QFont::Bold));
    button->setMinimumSize(0, 0);
    button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->m_downLayout->addWidget(button);
    this->m_downLayout->setStretchFactor(button, ButtonSize);

    //this->m_downLayout->addWidget();
    this->m_mainLayout->addLayout(this->m_downLayout);
    this->m_mainLayout->setStretchFactor(this->m_downLayout, 3);
}
