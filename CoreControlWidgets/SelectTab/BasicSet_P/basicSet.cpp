#include "basicSet.h"

#include "CoreControlWidgets/ModWidgets/ToggleTopmost.h"
#include <QGraphicsDropShadowEffect>
#include "BaseWidgets/BaseCoreWidget/LayoutWidget.h"
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
    m_setListScrollArea->setStyleSheet("QScrollArea{background: #d3e5f7; min-height: 50px;}");
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


    setListWidget->adjustSize();
    m_setListScrollArea->setWidget(setListWidget);

    // ========== 4. 构建下层固定区域 ==========
    m_downWidget = new QWidget();
    m_downWidget->setObjectName("BasicSetTab_BottomWidget");
    m_downWidget->setAutoFillBackground(true);
    m_downWidget->setAttribute(Qt::WA_StyledBackground, true);
    m_downWidget->setStyleSheet("QWidget#BasicSetTab_BottomWidget{background: rgba(179, 214, 255, 1); min-height: 50px;}");
    QHBoxLayout *bottomLayout = new QHBoxLayout(m_downWidget);
    bottomLayout->setContentsMargins(5, 0, 5, 0);
    bottomLayout->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    bottomLayout->addWidget(new ::ModWidgets::ToggleTopmost());
    bottomLayout->addStretch();

    // ========== 5. 把上/中/下添加到BaseTab的中心布局 ==========
    this->m_centerLayout->setContentsMargins(0, 0, 0, 0);
    this->m_centerLayout->setSpacing(0);
    this->m_centerLayout->addWidget(m_setListScrollArea, 1); // 中间（占剩余空间，比例固定）
    this->m_centerLayout->addWidget(m_downWidget);       // 下层（固定）
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
    selectModTabBar->setStyleSheet(R"(
        QTabBar {
            background-color: #eff7ff;
            border-radius: 15px;
            border: none;
        }
        QTabBar::tab {
            background-color: transparent;
            color: #666666;
            padding: 8px 16px;
            border: none;
            border-radius: 16px;
            margin-left: 6px;
            margin-right: 6px;
        }
        QTabBar::tab:selected {
            background-color: #1170d0;
            color: #ffffff;
        }
        QTabBar::tab:!selected {
            margin-top: 2px;
        }
    )");
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
    QObject::connect(selectModTabBar, &QTabBar::tabBarClicked, [selectModTip, selectModTipText_1, selectModTipText_2](int index) {
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
    QVBoxLayout *selectModMainLayout = new QVBoxLayout();
    parent->setLayout(selectModMainLayout);
    // 1.1 布局
    QHBoxLayout* selectModLayout = new QHBoxLayout();
    selectModLayout->setContentsMargins(0, 0, 0, 0);
    selectModLayout->setSpacing(10);
    selectModLayout->setAlignment(Qt::AlignLeft);
    // 1.2 laybal
    QLabel* selectModLabel = new QLabel("选择方法");
    selectModLabel->setFont(QFont("微软雅黑", 12));
    selectModLayout->addWidget(selectModLabel);
    // 1.3 选项卡
    QTabBar *selectModTabBar = new QTabBar();
    selectModTabBar->setStyleSheet(R"(
        QTabBar {
            background-color: #eff7ff;
            border-radius: 15px;
            border: none;
        }
        QTabBar::tab {
            background-color: transparent;
            color: #666666;
            padding: 8px 16px;
            border: none;
            border-radius: 16px;
            margin-left: 6px;
            margin-right: 6px;
        }
        QTabBar::tab:selected {
            background-color: #1170d0;
            color: #ffffff;
        }
        QTabBar::tab:!selected {
            margin-top: 2px;
        }
    )");
    selectModTabBar->addTab("轮盘赌 随机抽取");
    selectModTabBar->addTab("移位因子平衡 随机抽取");
    selectModLayout->addWidget(selectModTabBar);
    selectModMainLayout->addLayout(selectModLayout);
    // 1.4 提示信息
    QString selectModTipText_1 = "   轮盘赌 随机抽取\n"
                               "   基于 轮盘赌选择法（Roulette Wheel Selection） 随机抽取";
    QString selectModTipText_2 = "   移位因子平衡 随机抽取\n"
                               "   基于 移位因子平衡算法 + 轮盘赌选择法 随机抽取";
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
    QObject::connect(selectModTabBar, &QTabBar::tabBarClicked, [selectModTip, selectModTipText_1, selectModTipText_2](int index) {
        if (index == 0) {
            selectModTip->setText(selectModTipText_1);
        } else {
            selectModTip->setText(selectModTipText_2);
        }
    });
}
