#include "select_P.h"

#include "BaseWidgets/BaseCoreWidget/AspectRatioWidget.h"

#include "slc_midWidget.h"

#include "VariablesStore/globalVariables.h"

#include "CoreControlWidgets/ModWidgets/ToggleTopmost.h"

#include <QtTextToSpeech/QTextToSpeech>

#include "BaseWidgets/BaseCoreWidget/TinyWidget/AutoFitLabel.h"
#include "CoreControlWidgets/MintWidgets/TwoColorButton.h"

CoreControlWidgets::SelectTab_NS::Select_Page::Select_Page(QWidget *parent): QWidget(parent)
{
    this->m_centerLayout = new QVBoxLayout();
    this->m_centerLayout->setContentsMargins(0, 0, 0, 0);
    this->m_centerLayout->setSpacing(0);
    this->m_centerLayout->setAlignment(Qt::AlignTop);
    this->setLayout(this->m_centerLayout);

    // ========== 2. 构建上层固定区域 ==========
    m_topWidget = new QWidget();
    m_topWidget->setObjectName("SelectTab_TopWidget");
    m_topWidget->setStyleSheet("QWidget#SelectTab_TopWidget{background: rgba(179, 214, 255, 1); min-height: 50px;}");
    QHBoxLayout *topLayout = new QHBoxLayout(m_topWidget);
    topLayout->setContentsMargins(10, 0, 10, 0);
    topLayout->addWidget(new QLabel("上层固定区域"));
    topLayout->addStretch();
    topLayout->addWidget(new QPushButton("上层按钮"));

    // ========== 3. 构建中间比例固定区域 ==========
    // 初始化比例容器（示例：4:3的宽高比）
    GlobalVariables* gv = GLOBAL_VARIABLES;
    m_aspectMidWidget = new BaseWidgets::AspectRatioWidget(gv->mid_window_proportion);
    m_aspectMidWidget->setObjectName("SelectTab_AspectMidWidget");
    m_aspectMidWidget->setStyleSheet("QWidget#SelectTab_AspectMidWidget{background: #cee8f6;}");
    // 包裹原有MidWidget
    m_midWidget = new MidWidget();
    gv->main_mid_widget = m_midWidget;
    m_aspectMidWidget->setContentWidget(m_midWidget);

    // ========== 4. 构建下层固定区域 ==========
    m_downWidget = new QWidget();
    m_downWidget->setObjectName("SelectTab_BottomWidget");
    m_downWidget->setAutoFillBackground(true);
    m_downWidget->setAttribute(Qt::WA_StyledBackground, true);
    m_downWidget->setStyleSheet("QWidget#SelectTab_BottomWidget{background: rgba(179, 214, 255, 1); min-height: 50px;}");

    QHBoxLayout *buttomLayout = new QHBoxLayout(m_downWidget);
    buttomLayout->setContentsMargins(5, 0, 5, 0);
    buttomLayout->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    // 添加置顶按钮
    buttomLayout->addWidget(new ::ModWidgets::ToggleTopmost());

    // 添加朗读按钮
    TwoColorButton *speechButton = new TwoColorButton();
    speechButton->setText("朗读选项");
    speechButton->setFixedSize(100, 45);
    speechButton->setFont(QFont("Microsoft YaHei", 14));
    QTextToSpeech* tts = new QTextToSpeech(this);
    tts->setVolume(1.0);
    QObject::connect(speechButton, &QPushButton::clicked, [=, this]() {
        tts->say(this->m_midWidget->m_option_content->text());
        speechButton->setEnabled(false);
        QTimer::singleShot(1000, [speechButton](){
            speechButton->setEnabled(true);
        });
    });
    buttomLayout->addWidget(speechButton);

    buttomLayout->addStretch();
    // ========== 5. 把上/中/下添加到BaseTab的中心布局 ==========
    this->m_centerLayout->setContentsMargins(0, 0, 0, 0);
    this->m_centerLayout->setSpacing(0);
    this->m_centerLayout->addWidget(m_topWidget);          // 上层（固定）
    this->m_centerLayout->addWidget(m_aspectMidWidget, 1); // 中间（占剩余空间，比例固定）
    this->m_centerLayout->addWidget(m_downWidget);       // 下层（固定）
}

CoreControlWidgets::SelectTab_NS::Select_Page::~Select_Page()
{
}
