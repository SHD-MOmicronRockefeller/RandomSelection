#include "mmryItem.h"

#include "QtPrecompiled.h"
#include "ClassSpace.h"

#include "BaseWidgets/BaseCoreWidget/LayoutWidget.h"
#include "CoreCalculation/SelectTabFunc/OptionList.hpp"




CoreControlWidgets::SelectTab_NS::MmryItem::MmryItem(CoreCalculation::Base::OptionItem optionItem, QWidget *parent)
    : LayoutWidget(parent)
{
    this->mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(10, 5, 10, 5);
    mainLayout->setSpacing(5);
    mainLayout->setAlignment(Qt::AlignVCenter);

    this->optionItem = optionItem;

    this->setStyleSheet(R"(
        QWidget {
            background-color: #f1f5f5;
            border-radius: 5px;
        }
    )");

    // 选项名
    QLabel* contentLabel_Tip = new QLabel();
    contentLabel_Tip->setText("选项名:");
    contentLabel_Tip->setContentsMargins(3,2,3,2);
    contentLabel_Tip->setStyleSheet(R"(
        QLabel {
            font-size: 12px;
            color: rgba(54, 157, 241, 0.9);
            background-color: rgba(54, 157, 241, 0.2);
            border-radius: 5px;
        }
    )");
    contentLabel_Tip->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    mainLayout->addWidget(contentLabel_Tip, 1);

    QLabel* contentLabel_Val = new QLabel();
    contentLabel_Val->setText(optionItem.getContent());
    contentLabel_Val->setContentsMargins(3,2,3,2);
    contentLabel_Val->setFont(QFont("微软雅黑", 13));
    mainLayout->addWidget(contentLabel_Val, 4);

    // 索引
    QLabel* indexLabel_Tip = new QLabel();
    indexLabel_Tip->setText("索引:");
    indexLabel_Tip->setContentsMargins(3,2,3,2);
    indexLabel_Tip->setStyleSheet(R"(
        QLabel {
            font-size: 12px;
            color: rgba(54, 157, 241, 0.9);
            background-color: rgba(54, 157, 241, 0.2);
            border-radius: 5px;
        }
    )");
    indexLabel_Tip->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    mainLayout->addWidget(indexLabel_Tip, 1);

    QLabel* indexLabel_Val = new QLabel();
    indexLabel_Val->setText(QString::number(optionItem.getIndex()));
    indexLabel_Val->setContentsMargins(3,2,3,2);
    indexLabel_Val->setFont(QFont("微软雅黑", 13));
    mainLayout->addWidget(indexLabel_Val, 2);

    // 权重
    QLabel* weightLabel_Tip = new QLabel();
    weightLabel_Tip->setText("权重:");
    weightLabel_Tip->setContentsMargins(3,2,3,2);
    weightLabel_Tip->setStyleSheet(R"(
        QLabel {
            font-size: 12px;
            color: rgba(54, 157, 241, 0.9);
            background-color: rgba(54, 157, 241, 0.2);
            border-radius: 5px;
        }
    )");
    weightLabel_Tip->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    mainLayout->addWidget(weightLabel_Tip, 1);

    QLabel* weightLabel_Val = new QLabel();
    weightLabel_Val->setText(QString::number(optionItem.getWeight()));
    weightLabel_Val->setContentsMargins(3,2,3,2);
    weightLabel_Val->setFont(QFont("微软雅黑", 13));
    mainLayout->addWidget(weightLabel_Val, 2);

    // 选择次数
    QLabel* selectedTimesLabel_Tip = new QLabel();
    selectedTimesLabel_Tip->setText("选择次数:");
    selectedTimesLabel_Tip->setContentsMargins(3,2,3,2);
    selectedTimesLabel_Tip->setStyleSheet(R"(
        QLabel {
            font-size: 12px;
            color: rgba(54, 157, 241, 0.9);
            background-color: rgba(54, 157, 241, 0.2);
            border-radius: 5px;
        }
    )");
    selectedTimesLabel_Tip->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    mainLayout->addWidget(selectedTimesLabel_Tip, 1);

    this->selectedTimesLabel_Val = new QLabel();
    selectedTimesLabel_Val->setText(QString::number(optionItem.getSelectedTimes() + 1));
    selectedTimesLabel_Val->setContentsMargins(3,2,3,2);
    selectedTimesLabel_Val->setFont(QFont("微软雅黑", 13));
    mainLayout->addWidget(selectedTimesLabel_Val, 2);

    // 所属组
    QLabel* groupLabel_Tip = new QLabel();
    groupLabel_Tip->setText("所属组:");
    groupLabel_Tip->setContentsMargins(3,2,3,2);
    groupLabel_Tip->setStyleSheet(R"(
        QLabel {
            font-size: 12px;
            color: rgba(54, 157, 241, 0.9);
            background-color: rgba(54, 157, 241, 0.2);
            border-radius: 6px;
        }
    )");
    groupLabel_Tip->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    mainLayout->addWidget(groupLabel_Tip, 1);

    QComboBox* groupCombox = new QComboBox();
    groupCombox->setStyleSheet(R"(
            QComboBox {
                height: 24px;
                border: 1px solid #dcdfe6;
                border-radius: 4px;
                padding: 0 0px;
                font-size: 13px;
            }
            QComboBox:hover { border-color: #c0c4cc; }
            QComboBox:focus { border-color: #409eff; }
            QComboBox:editable QLineEdit {
                border: none;
                background: transparent;
                color: #303133;
            }
        )");
    // groupCombox->addItems(optionItem.getOwnGroupNames());
    groupCombox->setEditable(true);
    groupCombox->lineEdit()->setReadOnly(true);
    groupCombox->lineEdit()->setText("所属组列表");
    if (not optionItem.getOwnGroups().isEmpty())
        groupCombox->addItems(optionItem.getOwnGroupNames());
    groupCombox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    mainLayout->addWidget(groupCombox, 4);
}

bool CoreControlWidgets::SelectTab_NS::MmryItem::addOption(CoreCalculation::Base::OptionItem optionItem) {
    if (optionItem.getIndex() != this->optionItem.getIndex()) return false; // 避免添加重复的选项
    this->optionItem.setSelectedTimes(optionItem.getSelectedTimes()); // 更新选择次数
    this->selectedTimesLabel_Val->setText(QString::number(optionItem.getSelectedTimes() + 1));
    return true;
}
