#include "basicSet.h"

#include "CoreControlWidgets/ModWidgets/ToggleTopmost.h"
#include "BaseWidgets/BaseCoreWidget/LayoutWidget.h"
#include "ApplicationClass/Application/SignalSource.h"
#include "BaseWidgets/BaseCoreWidget/MessageTipWidget.h"
#include "VariablesStore/globalVariables.h"
CoreControlWidgets::SelectTab_NS::BasicSet_Page::BasicSet_Page(QWidget *parent): QWidget(parent)
{
    this->m_centerLayout = new QVBoxLayout();
    this->m_centerLayout->setContentsMargins(0, 0, 0, 0);
    this->m_centerLayout->setSpacing(0);
    this->m_centerLayout->setAlignment(Qt::AlignTop);
    this->setLayout(this->m_centerLayout);

    // ========== 3. 构建中层可变区域 ==========
    m_setListScrollArea = new QScrollArea();
    m_setListScrollArea->setWidgetResizable(true);
    m_setListScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_setListScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    m_setListScrollArea->setStyleSheet("QScrollArea{background: #cee8f6; min-height: 50px;}");
    QWidget *setListWidget = new QWidget();
    setListWidget->setStyleSheet("QWidget{background: transparent;}");
    setListWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    QVBoxLayout *setListLayout = new QVBoxLayout(setListWidget);
    setListLayout->setAlignment(Qt::AlignTop);
    setListLayout->setSpacing(20);
    // 0 设置标题
    QLabel* title = new QLabel("选择设置");
    title->setAlignment(Qt::AlignHCenter| Qt::AlignVCenter);
    title->setFont(QFont("微软雅黑", 16, QFont::Bold));
    title->setWordWrap(true);
    setListLayout->addWidget(title);

    // 1 选择模式
    LayoutWidget *selectModMainWidget = new LayoutWidget();
    this->setSelectMod(selectModMainWidget);
    setListLayout->addWidget(selectModMainWidget);

    // 2 选择方法
    LayoutWidget *selectFuncWidget = new LayoutWidget();
    this->setSelectFunc(selectFuncWidget);
    setListLayout->addWidget(selectFuncWidget);

    // 3. 百宝盒子
    LayoutWidget *widgetBox = new LayoutWidget();
    this->setBaibaoBox(widgetBox);
    setListLayout->addWidget(widgetBox);


    setListWidget->adjustSize();
    m_setListScrollArea->setWidget(setListWidget);

    // // ========== 4. 构建下层固定区域 ==========
    // m_downWidget = new QWidget();
    // m_downWidget->setObjectName("BasicSetTab_BottomWidget");
    // m_downWidget->setAutoFillBackground(true);
    // m_downWidget->setAttribute(Qt::WA_StyledBackground, true);
    // m_downWidget->setStyleSheet("QWidget#BasicSetTab_BottomWidget{background: rgba(179, 214, 255, 1); min-height: 50px;}");
    // QHBoxLayout *bottomLayout = new QHBoxLayout(m_downWidget);
    // bottomLayout->setContentsMargins(5, 0, 5, 0);
    // bottomLayout->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    //
    // bottomLayout->addWidget(new ::ModWidgets::ToggleTopmost());
    // bottomLayout->addStretch();

    setStyleSheet(styleSheet() + R"(
        QTabBar#doubleSLCT {
            background-color: #eff7ff;
            border-radius: 15px;
            border: none;
        }
        QTabBar#doubleSLCT::tab {
            background-color: transparent;
            color: #666666;
            padding: 8px 16px;
            border: none;
            border-radius: 16px;
            margin-left: 6px;
            margin-right: 6px;
        }
        QTabBar#doubleSLCT::tab:selected {
            background-color: #1170d0;
            color: #ffffff;
        }
        QTabBar#doubleSLCT::tab:!selected {
            margin-top: 2px;
        }
    )");

    // ========== 5. 把上/中/下添加到BaseTab的中心布局 ==========
    this->m_centerLayout->setContentsMargins(0, 0, 0, 0);
    this->m_centerLayout->setSpacing(0);
    this->m_centerLayout->addWidget(m_setListScrollArea, 1); // 中间（占剩余空间，比例固定）
    // this->m_centerLayout->addWidget(m_downWidget);       // 下层（固定）
}

CoreControlWidgets::SelectTab_NS::BasicSet_Page::~BasicSet_Page()
{
}

void CoreControlWidgets::SelectTab_NS::BasicSet_Page::setSelectMod(QWidget* parent) {
    // 1 选择模式
    // 1.0 选择卡片
    QVBoxLayout *selectModMainLayout = new QVBoxLayout();
    parent->setLayout(selectModMainLayout);
    // 1.1 布局
    QHBoxLayout* selectModLayout = new QHBoxLayout();
    selectModLayout->setContentsMargins(0, 0, 0, 0);
    selectModLayout->setSpacing(10);
    selectModLayout->setAlignment(Qt::AlignLeft);
    // 1.2 laybal
    QLabel* selectModLabel = new QLabel("抽取模式");
    selectModLabel->setFont(QFont("微软雅黑", 12));
    selectModLayout->addWidget(selectModLabel);
    // 1.3 选项卡
    QTabBar *selectModTabBar = new QTabBar();
    selectModTabBar->setObjectName("doubleSLCT");
    selectModTabBar->addTab("按 单元 选取");
    selectModTabBar->addTab("按 分组 选取");
    selectModLayout->addWidget(selectModTabBar);
    selectModMainLayout->addLayout(selectModLayout);
    // 1.4 提示信息
    QString selectModTipText_1 = "   按 单元 选取\n"
                               "   根据 组单元管理器 对单元进行随机选取";
    QString selectModTipText_2 = "   按 分组 选取\n"
                               "   根据 组单元管理器 对分组进行随机选取";
    QLabel *selectModTip = new QLabel(selectModTipText_1);
    selectModTip->setStyleSheet(R"(
        QLabel {
            background-color: #eff7ff;
            border-radius: 16px;
            border: 1px solid #cee1f5;
        }
    )");
    selectModTip->setWordWrap(true);
    selectModTip->setFont(QFont("微软雅黑", 8));
    selectModMainLayout->addWidget(selectModTip);
    QObject::connect(selectModTabBar, &QTabBar::tabBarClicked, [=](int index) {
        if (index == 0) {
            selectModTip->setText(selectModTipText_1);
        } else {
            selectModTip->setText(selectModTipText_2);
        }
    });

}

void CoreControlWidgets::SelectTab_NS::BasicSet_Page::setSelectFunc(QWidget* parent) {
    // 1 选择方法
    // 1.0 选择卡片
    QVBoxLayout *selectFuncMainLayout = new QVBoxLayout();
    parent->setLayout(selectFuncMainLayout);
    // 1.1 布局
    QHBoxLayout* selectFuncLayout = new QHBoxLayout();
    selectFuncLayout->setContentsMargins(0, 0, 0, 0);
    selectFuncLayout->setSpacing(10);
    selectFuncLayout->setAlignment(Qt::AlignLeft);
    // 1.2 laybal
    QLabel* selectFuncLabel = new QLabel("选择方法");
    selectFuncLabel->setFont(QFont("微软雅黑", 12));
    selectFuncLayout->addWidget(selectFuncLabel);
    // 1.3 选项卡
    QTabBar *selectFuncTabBar = new QTabBar();
    selectFuncTabBar->setObjectName("doubleSLCT");
    selectFuncTabBar->addTab("轮盘赌 随机抽取");
    selectFuncTabBar->addTab("移位因子平衡 随机抽取");
    selectFuncLayout->addWidget(selectFuncTabBar);
    selectFuncMainLayout->addLayout(selectFuncLayout);
    // 1.4 提示信息
    QString selectFuncTipText_1 = "   轮盘赌 随机抽取\n"
                               "   基于 轮盘赌选择法（Roulette Wheel Selection） 随机抽取";
    QString selectFuncTipText_2 = "   移位因子平衡 随机抽取\n"
                               "   基于 移位因子平衡算法 + 轮盘赌选择法 随机抽取";
    QLabel *selectFuncTip = new QLabel(selectFuncTipText_1);
    selectFuncTip->setStyleSheet(R"(
        QLabel {
            background-color: #eff7ff;
            border-radius: 16px;
            border: 1px solid #cee1f5;
        }
    )");
    selectFuncTip->setWordWrap(true);
    selectFuncTip->setFont(QFont("微软雅黑", 8));
    selectFuncMainLayout->addWidget(selectFuncTip);

    // 移位因子平衡算法 参数设置
    QFrame *selectFuncFrame = new QFrame();
    selectFuncFrame->setFrameShape(QFrame::NoFrame);
    QVBoxLayout *selectFuncFrameLayout = new QVBoxLayout();
    selectFuncFrameLayout->setContentsMargins(0, 0, 0, 0);
    selectFuncFrameLayout->setSpacing(10);
    selectFuncFrameLayout->setAlignment(Qt::AlignLeft);
    selectFuncFrame->setLayout(selectFuncFrameLayout);

    // 链接 参数设置
    QObject::connect(selectFuncTabBar, &QTabBar::tabBarClicked, [=](int index) {
        if (index == 0) {
            selectFuncTip->setText(selectFuncTipText_1);
            selectFuncMainLayout->removeWidget(selectFuncFrame);
        } else {
            selectFuncTip->setText(selectFuncTipText_2);
            selectFuncMainLayout->addWidget(selectFuncFrame);
        }
    });

    // 分隔符
    QFrame *separator = new QFrame();
    separator->setStyleSheet(R"(
        QFrame {
            border: none;
            border-radius: 1px;
            background: #98c8fa;
            margin-top: 10px;
            margin-left: 10px;
            margin-right: 10px;
    })");
    separator->setFixedHeight(13);
    selectFuncFrameLayout->addWidget(separator);

    //  移位因子平衡算法 参数设置
    // 标签
    QLabel *weightLabel = new QLabel("移位因子平衡算法 参数设置");
    weightLabel->setFont(QFont("微软雅黑", 12, QFont::Bold));
    selectFuncFrameLayout->addWidget(weightLabel);

    // 分隔符
    QFrame *separator_1 = new QFrame();
    separator_1->setStyleSheet("QFrame {background: transparent;}");
    separator_1->setFixedHeight(5);
    selectFuncFrameLayout->addWidget(separator_1);

    // top量影响因子
    QHBoxLayout *topLayout = new QHBoxLayout();
    topLayout->setContentsMargins(0, 0, 0, 0);
    topLayout->setSpacing(10);
    topLayout->setAlignment(Qt::AlignLeft);
        // 标签
    QLabel *topLabel = new QLabel("top量影响因子");
    topLabel->setFont(QFont("微软雅黑", 12));
    topLayout->addWidget(topLabel);
        // 滑动条
    QSlider *topSlider = new QSlider();
    topSlider->setObjectName("whiteSlider");
    topSlider->setFixedHeight(22);
    topSlider->setOrientation(Qt::Horizontal);
    topSlider->setMinimum(0);
    topSlider->setMaximum(3000);
    topSlider->setValue(1000);
    topLayout->addWidget(topSlider);
        // 数值标签
    QLabel *topValueLabel = new QLabel("1.000");
    topValueLabel->setFont(QFont("微软雅黑", 12));
    topLayout->addWidget(topValueLabel);
        // 滑动条 数值标签同步
    selectFuncFrameLayout->addLayout(topLayout);
    connect(topSlider, &QSlider::valueChanged, [=](int value) {
        topValueLabel->setText(QString::number(value / 1000.0, 'f', 3));
    });

    QFrame *separator_2 = new QFrame();
    separator_2->setStyleSheet("QFrame {background: transparent;}");
    separator_2->setFixedHeight(5);
    selectFuncFrameLayout->addWidget(separator_2);

    //幂倍率 标签
    QHBoxLayout *powerLayout = new QHBoxLayout();
    powerLayout->setContentsMargins(0, 0, 0, 0);
    powerLayout->setSpacing(10);
    selectFuncFrameLayout->addLayout(powerLayout);
        // 标签
    QLabel *powerLabel = new QLabel("幂倍率");
    powerLabel->setFont(QFont("微软雅黑", 12));
    powerLayout->addWidget(powerLabel);
        // 弹簧
    powerLayout->addStretch();
        // 数值
    QLabel *powerValueLabel = new QLabel("1.000");
    powerValueLabel->setFont(QFont("微软雅黑", 12));
    powerLayout->addWidget(powerValueLabel);

    // 幂倍率-整数部分-标签
    QHBoxLayout *powerLayout_coarse = new QHBoxLayout();
    powerLayout_coarse->setContentsMargins(0, 0, 0, 0);
    powerLayout_coarse->setSpacing(10);
    powerLayout_coarse->setAlignment(Qt::AlignLeft);
    selectFuncFrameLayout->addLayout(powerLayout_coarse);
        // 标签
    QLabel *powerLabel_coarse = new QLabel("    幂倍率-整数");
    powerLabel_coarse->setFont(QFont("微软雅黑", 12));
    powerLayout_coarse->addWidget(powerLabel_coarse);
        // 滑动条
    QSlider *powerSlider_coarse = new QSlider();
    powerSlider_coarse->setObjectName("whiteSlider");
    powerSlider_coarse->setFixedHeight(22);
    powerSlider_coarse->setOrientation(Qt::Horizontal);
    powerSlider_coarse->setMinimum(0);
    powerSlider_coarse->setMaximum(19);
    powerSlider_coarse->setValue(1);
    powerLayout_coarse->addWidget(powerSlider_coarse);


    // 幂倍率-小数部分-标签
    QHBoxLayout *powerLayout_fine = new QHBoxLayout();
    powerLayout_fine->setContentsMargins(0, 0, 0, 0);
    powerLayout_fine->setSpacing(10);
    powerLayout_fine->setAlignment(Qt::AlignLeft);
    selectFuncFrameLayout->addLayout(powerLayout_fine);
        // 标签
    QLabel *powerLabel_fine = new QLabel("    幂倍率-小数");
    powerLabel_fine->setFont(QFont("微软雅黑", 12));
    powerLayout_fine->addWidget(powerLabel_fine);
        // 滑动条
    QSlider *powerSlider_fine = new QSlider();
    powerSlider_fine->setObjectName("whiteSlider");
    powerSlider_fine->setFixedHeight(22);
    powerSlider_fine->setOrientation(Qt::Horizontal);
    powerSlider_fine->setMinimum(0);
    powerSlider_fine->setMaximum(1000);
    powerSlider_fine->setValue(0);
    powerLayout_fine->addWidget(powerSlider_fine);

    auto setPower = [=]() {
        powerValueLabel->setText(QString::number(
            powerSlider_coarse->value() + (powerSlider_fine->value() / 1000.0),'f', 3));
    };

    connect(powerSlider_coarse, &QSlider::valueChanged, setPower);
    connect(powerSlider_fine, &QSlider::valueChanged, setPower);

    setStyleSheet(styleSheet() + R"(
        QSlider#whiteSlider::groove:horizontal {
            background: #d3e5f7;
            height: 8px;
            border-radius: 4px;
        }
        QSlider#whiteSlider::sub-page:horizontal {
            background: #328de7;
            border-radius: 4px;
        }
        QSlider#whiteSlider::handle:horizontal {
            background: #cee1f5;
            border: 1px solid #1170d0;
            width: 20px;
            height: 16px;
            margin: -5px 0;
            border-radius: 8px;
        }
        QSlider#whiteSlider::handle:horizontal:hover {
            transform: scale(1.1);
        }
    )");
}

void CoreControlWidgets::SelectTab_NS::BasicSet_Page::setBaibaoBox(QWidget* parent) {
    // 1 置顶
    // 1.0 选择卡片
    QVBoxLayout *selectModMainLayout = new QVBoxLayout();
    parent->setLayout(selectModMainLayout);
    // 1.1 布局
    QHBoxLayout* selectModLayout = new QHBoxLayout();
    selectModLayout->setContentsMargins(0, 0, 0, 0);
    selectModLayout->setSpacing(10);
    selectModLayout->setAlignment(Qt::AlignLeft);
    // 1.2 laybal
    QLabel* selectModLabel = new QLabel("窗口置顶");
    selectModLabel->setFont(QFont("微软雅黑", 12));
    selectModLayout->addWidget(selectModLabel);
    // 1.3 选项卡
    QTabBar *selectModTabBar = new QTabBar();
    selectModTabBar->setObjectName("doubleSLCT");
    selectModTabBar->addTab("关闭 置顶");
    selectModTabBar->addTab("开启 置顶");
    selectModLayout->addWidget(selectModTabBar);
    selectModMainLayout->addLayout(selectModLayout);

    QObject::connect(selectModTabBar, &QTabBar::tabBarClicked, [=](int index) {
        GlobalVariables* gv = GlobalVariables::getInstance();
        if (index == 0) {
            gv->is_settop_window = false;
            gv->main_window_shell->windowHandle()->setFlag(Qt::WindowStaysOnTopHint, false);
            emit SignalSource::getInstance()->WindowTopmostToggled();
        } else {
            gv->is_settop_window = true;
            gv->main_window_shell->windowHandle()->setFlag(Qt::WindowStaysOnTopHint, true);
            emit SignalSource::getInstance()->WindowTopmostToggled();
        }
    });
    connect(SignalSource::getInstance(), &SignalSource::WindowTopmostToggled, selectModTabBar, [=](){
        GlobalVariables* gv = GlobalVariables::getInstance();
        if (gv->is_settop_window) {
            selectModTabBar->setCurrentIndex(1);
        } else {
            selectModTabBar->setCurrentIndex(0);
        }
    });
}
