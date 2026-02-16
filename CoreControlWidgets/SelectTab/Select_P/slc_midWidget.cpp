#include "slc_midWidget.h"

#include "BaseWidgets/BaseCoreWidget/TinyWidget/AutoFitButton.h"
#include "BaseWidgets/BaseCoreWidget/TinyWidget/AutoFitLabel.h"

#include "CoreCalculation/SelectTabFunc/RandomSelectOption.hpp"
#include "Console/console.h"

#include <QDebug>

#define ButtonSize 1
#define LabelSize 6

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

    m_numList = new BaseWidgets::AutoFitLabel("NUM> ");
    m_numList->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_numList->setAlignment(Qt::AlignLeft | Qt::AlignBottom);
    this->m_upLayout->addWidget(m_numList);
    this->m_upLayout->setStretchFactor(m_numList, LabelSize - 4);

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
    QObject::connect(button, &QPushButton::clicked, QApplication::instance(), [=]() {
        GlobalVariables* gv = GLOBAL_VARIABLES;
        if (gv->current_select_index > 1) {
            gv->current_select_index -= 1;

            QString numText = QString("NUM> %1 / %2").arg(gv->current_select_index).arg(gv->total_select_count);
            gv->main_mid_widget->m_numList->setText(numText);
            gv->min_mid_widget->m_numList->setText(numText);

            auto [num, content, information] = gv->memory_list[gv->current_select_index - 1];
            gv->main_mid_widget->m_option_content->setText(content);
            gv->min_mid_widget->m_option_content->setText(content);

            gv->main_mid_widget->m_option_information->setText(information);
            gv->min_mid_widget->m_option_information->setText(information);
        }
    });

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

    m_option_content = new BaseWidgets::AutoFitLabel("你名字六个字");
    m_option_content->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->m_midLayout->addWidget(m_option_content);
    this->m_midLayout->setStretchFactor(m_option_content, LabelSize);

    BaseWidgets::AutoFitButton *button = new BaseWidgets::AutoFitButton("选\n择");
    button->setFont(QFont("Microsoft YaHei", 36, QFont::Bold));
    button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_option_content->setStyleSheet(R"(
        QLabel {
            background-color: #FFFFFF;
            color: #333333;
            padding: 6px 12px;
            border: 1px solid transparent;
            border-radius: 3px;
        }
        QLabel:focus {
            border: 1px solid #E0F0FF;
            outline: none;
        }
    )");
    QObject::connect(button, &QPushButton::clicked, QApplication::instance(), [=]() {
        Task task_1 = newTask;
        Task task_2 = newTask;
        PushTask(([task_1, task_2]() mutable {
            GlobalVariables* gv = GLOBAL_VARIABLES;
            const auto result = CoreCalculation::RandomSelectOption().RS_Balance(
                gv->active_option_list, 1, 20);
            SendResultFinally(task_1, result);
            QString information = QString("选择对象：%1  序号：%2\n权重：%3/%4/%5 | 概率：%6%/%7% | 抽取次数：%8/%9")
                    .arg(result.getContent()) // 选择对象
                    .arg(result.getIndex())   // 序号
                    .arg(result.getWeight()) // 权重
                    .arg(gv->total_weight)   // 分权重
                    .arg(gv->total_weight)   // 总权重
                    .arg(QString::number(static_cast<double>(result.getWeight())*100/static_cast<double>(gv->total_weight), 'f', 3)) // 分概率
                    .arg(QString::number(static_cast<double>(result.getWeight())*100/static_cast<double>(gv->total_weight), 'f', 3)) // 总概率
                    .arg(result.getSelectedTimes() + 1) // 抽取次数
                    .arg(gv->total_select_count); // 总抽取次数
            SendResultFinally(task_2, information);
            gv->memory_list.append({gv->total_select_count, result.getContent(), information});
        }));
        ReturnTask(task_1, [=]() mutable {
            GlobalVariables* gv = GLOBAL_VARIABLES;
            const auto result =  GetResult(CoreCalculation::Base::OptionItem);
            gv->main_mid_widget->m_option_content->setText(result.getContent());
            gv->min_mid_widget->m_option_content->setText(result.getContent());
        });
        ReturnTask(task_2, [=]() mutable {
            GlobalVariables* gv = GLOBAL_VARIABLES;
            const auto result =  GetResult(QString);
            gv->main_mid_widget->m_option_information->setText(result);
            gv->min_mid_widget->m_option_information->setText(result);
            gv->current_select_index = gv->total_select_count;
            QString numText = QString("NUM> %1 / %2").arg(gv->current_select_index).arg(gv->total_select_count);
            gv->main_mid_widget->m_numList->setText(numText);
            gv->min_mid_widget->m_numList->setText(numText);
        });
    });
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

    GlobalVariables* gv = GLOBAL_VARIABLES;
    m_option_information = new BaseWidgets::AutoFitLabel(
        "", 0,this);
    m_option_information->setObjectName("OptionInformation_XXX");
    m_option_information->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_option_information->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    this->m_downLayout->addWidget(m_option_information);
    this->m_downLayout->setStretchFactor(m_option_information, LabelSize);

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

    QObject::connect(button, &QPushButton::clicked, QApplication::instance(), [=]() {
        GlobalVariables* gv = GLOBAL_VARIABLES;
        if (gv->current_select_index < gv->total_select_count) {
            gv->current_select_index += 1;

            QString numText = QString("NUM> %1 / %2").arg(gv->current_select_index).arg(gv->total_select_count);
            gv->main_mid_widget->m_numList->setText(numText);
            gv->min_mid_widget->m_numList->setText(numText);

            auto [num, content, information] = gv->memory_list[gv->current_select_index - 1];
            gv->main_mid_widget->m_option_content->setText(content);
            gv->min_mid_widget->m_option_content->setText(content);

            gv->main_mid_widget->m_option_information->setText(information);
            gv->min_mid_widget->m_option_information->setText(information);
        }
    });
}
