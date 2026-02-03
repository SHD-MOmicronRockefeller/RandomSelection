#include "MessageTipWidget.h"

#include <QPainter>
#include <QGraphicsDropShadowEffect>
#include <QApplication>
#include <QScreen>
#include <QEasingCurve>
#include <QPushButton>
#include <QLabel>
#include <QSlider>
#include <QSequentialAnimationGroup>
#include <QParallelAnimationGroup>
#include <QTimer>

#include "CoreControlWidgets/MainWindow/mainWindow.h"

#include "VariablesStore/globalVariables.h"

// ==================== MessageTipWidget 实现 ====================
MessageTipWidget::MessageTipWidget(bool persistent, QWidget *parent)
    : QWidget(parent, Qt::FramelessWindowHint | Qt::SubWindow)
    , m_isPersistent(persistent)
    , m_isHandled(false)
    , m_isHiddenByPush(false)
    , m_opacity(1.0)
    , m_slotIndex(-1)
    , m_mainLayout(nullptr)
    , m_btnLayout(nullptr)
{
    setAttribute(Qt::WA_TranslucentBackground);
    setFixedWidth(WIDTH);
    // setFixedSize(WIDTH, HEIGHT);

    // 初始化布局
    m_mainLayout = new QVBoxLayout(this);
    m_mainLayout->setContentsMargins(10, 8, 10, 8);
    m_mainLayout->setSpacing(6);

    m_btnLayout = new QHBoxLayout();
    m_btnLayout->setSpacing(8);
    m_btnLayout->setAlignment(Qt::AlignRight);
    m_mainLayout->addLayout(m_btnLayout);

    // 阴影效果
    auto shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(10);
    shadow->setColor(QColor(0, 0, 0, 80));
    shadow->setOffset(2, 2);
    setGraphicsEffect(shadow);

    // 样式
    setObjectName("MessageTipWidget");
    setStyleSheet(R"(
        QWidget#MessageTipWidget {
            background-color: rgb(66, 209, 228);
            border-radius: 8px;
        }
    )");
}

MessageTipWidget::~MessageTipWidget() = default;

int MessageTipWidget::slotIndex() const
{
    return m_slotIndex;
}

void MessageTipWidget::setSlotIndex(int index)
{
    m_slotIndex = index;
}

void MessageTipWidget::addWidget(QWidget *widget, Qt::Alignment alignment)
{
    if (!widget) return;
    widget->setParent(this);
    if (qobject_cast<QPushButton*>(widget)) {
        m_btnLayout->addWidget(widget);
    } else {
        m_mainLayout->insertWidget(0, widget);
    }
    m_mainLayout->setAlignment(widget, alignment);

    m_mainLayout->activate();   // 强制布局计算
    this->adjustSize();         // 立即更新窗口大小
    this->update();             // 触发重绘，显示控件

    emit sizeChanged();
}

QPushButton *MessageTipWidget::addButton(const QString &text, Qt::Alignment alignment)
{
    auto btn = new QPushButton(text, this);
    QColor hoverColor = m_buttonColor.darker(110);
    btn->setStyleSheet(QString(R"(
        QPushButton {
            background-color: %1;
            color: white;
            border: none;
            padding: 4px 12px;
            border-radius: 4px;
            font-size: 12px;
        }
        QPushButton:hover {
            background-color: %2;
        }
    )").arg(m_buttonColor.name()).arg(hoverColor.name()));
    addWidget(btn, alignment);
    return btn;
}

QLabel *MessageTipWidget::addLabel(const QString &text, Qt::Alignment alignment)
{
    auto label = new QLabel(text, this);

    label->setStyleSheet(QString("color: %1; font-size: 12px;").arg(m_textColor.name()));
    // label->setWordWrap(true);
    addWidget(label, alignment);
    return label;
}

void MessageTipWidget::setText(const QString &text)
{
    addLabel(text);
    this->layout()->activate();
    this->adjustSize();
    this->raise(); // 确保窗口在最上层

    emit sizeChanged();
}

bool MessageTipWidget::isPersistent() const
{
    return m_isPersistent;
}

void MessageTipWidget::setPersistent(bool persistent)
{
    m_isPersistent = persistent;
}

bool MessageTipWidget::isHandled() const
{
    return m_isHandled;
}

void MessageTipWidget::setHandled(bool handled)
{
    if (m_isHandled == handled) return;
    m_isHandled = handled;
    
    if (handled) {
        emit tipHandled();
        // ========== 新增：退出动画完成后触发重排 ==========
        MessageTipManager::getInstance().animateTipOut(this);
    }
}

bool MessageTipWidget::isHiddenByPush() const
{
    return m_isHiddenByPush;
}

void MessageTipWidget::setHiddenByPush(bool hidden)
{
    m_isHiddenByPush = hidden;
    if (hidden) {
        hide();
    } else {
        show();
        setOpacity(0);
    }
}

qreal MessageTipWidget::opacity() const
{
    return m_opacity;
}

void MessageTipWidget::setOpacity(qreal opacity)
{
    m_opacity = opacity;
    setWindowOpacity(opacity);
}

MessageTipWidget* MessageTipWidget::setBackgroundColor(const QColor &color)
{
    m_bgColor = color;
    // 强制重绘，立即生效
    this->update();
    return this;
}

MessageTipWidget* MessageTipWidget::setTextColor(const QColor &color)
{
    m_textColor = color;
    // 遍历所有标签，更新文本颜色
    for (auto widget : findChildren<QLabel*>()) {
        auto label = qobject_cast<QLabel*>(widget);
        if (label) {
            label->setStyleSheet(QString("color: %1; font-size: 14px;").arg(m_textColor.name()));
        }
    }
    return this;
}

MessageTipWidget* MessageTipWidget::setButtonColor(const QColor &color)
{
    m_buttonColor = color;
    // 计算hover色（自动加深10%）
    QColor hoverColor = color.darker(110);
    // 遍历所有按钮，更新样式
    for (auto widget : findChildren<QPushButton*>()) {
        auto btn = qobject_cast<QPushButton*>(widget);
        if (btn) {
            btn->setStyleSheet(QString(R"(
                QPushButton {
                    background-color: %1;
                    color: white;
                    border: none;
                    padding: 4px 12px;
                    border-radius: 4px;
                    font-size: 12px;
                }
                QPushButton:hover {
                    background-color: %2;
                }
            )").arg(m_buttonColor.name()).arg(hoverColor.name()));
        }
    }
    return this;
}


void MessageTipWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    
    QBrush brush(m_bgColor);
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);
    painter.drawRoundedRect(rect(), 8, 8);
}

// ==================== MessageTipManager 实现 ====================
MessageTipManager &MessageTipManager::getInstance()
{
    static MessageTipManager instance;
    return instance;
}

MessageTipManager::MessageTipManager(QObject *parent)
    : QObject(parent)
    , m_mainWindow(nullptr)
{
    // 初始化固定位置数组
    for (int i = 0; i < MAX_TIP_COUNT; ++i) {
        m_tipSlots[i] = nullptr;
    }
}

MessageTipManager::~MessageTipManager() = default;

void MessageTipManager::init(QWidget *mainWindow)
{
    if (m_mainWindow == mainWindow) return;
    m_mainWindow = mainWindow;

    auto mainWin = qobject_cast<CoreControlWidgets::MainWindowShell*>(mainWindow);
    if (mainWin) {
        connect(mainWin, &CoreControlWidgets::MainWindowShell::windowChanged, this, &MessageTipManager::onMainWindowChanged);
    } else {
        mainWindow->installEventFilter(this);
    }
}

int MessageTipManager::findFirstEmptySlot()
{
    for (int i = 0; i < MAX_TIP_COUNT; ++i) {
        if (!m_tipSlots[i] || m_tipSlots[i]->isHandled()) {
            return i;
        }
    }
    return -1;
}

QPoint MessageTipManager::calculateTipPos(int slotIndex)
{
    if (slotIndex < 0 || slotIndex >= MAX_TIP_COUNT) return QPoint(0, 0);
    if (!m_mainWindow) return QPoint(0, 0);

    // 主窗口客户区（centralWidget优先）
    QRect clientRect = m_mainWindow->rect();
    const int margin = 10; // 消息与主窗口边缘的间距
    const int spacing = 10; // 消息之间的间距

    // X坐标：主窗口右侧内边距（固定）
    int x = clientRect.right() - MessageTipWidget::WIDTH - margin;

    int totalHeightOffset = 0;
    // 先计算前面slot的总高度（含间距）
    for (int i = 0; i < slotIndex; ++i) {
        if (m_tipSlots[i] && !m_tipSlots[i]->isHandled() && !m_tipSlots[i]->isHiddenByPush()) {
            totalHeightOffset += m_tipSlots[i]->height() + spacing;
        } else {
            // 占位高度（无消息时用默认值，避免位置错乱）
            totalHeightOffset += 60 + spacing;
        }
    }

    // Y坐标：主窗口底部 - 当前消息高度 - 边距 - 前面消息的总高度
    int currentTipHeight = 60; // 默认高度（未渲染时）
    if (m_tipSlots[slotIndex] && !m_tipSlots[slotIndex]->isHandled()) {
        currentTipHeight = m_tipSlots[slotIndex]->height();
    }
    int y = clientRect.bottom() - currentTipHeight - margin - totalHeightOffset;

    // 边界保护：防止超出可视区域
    x = qMax(margin, x);
    y = qMax(margin, y);

    return QPoint(x, y);
}

void MessageTipManager::animateTipIn(MessageTipWidget *tip)
{
    if (!tip || tip->slotIndex() < 0 || !m_mainWindow) return;

    tip->layout()->activate();
    tip->adjustSize();
    tip->show(); // 确保窗口可见

    QPoint targetPos = calculateTipPos(tip->slotIndex());
    QPoint startPos = QPoint(m_mainWindow->width() + 50, targetPos.y());
    QPoint elasticPos = QPoint(targetPos.x() - ELASTIC_OFFSET, targetPos.y());

    tip->move(startPos);
    tip->setOpacity(0);

    auto animGroup = new QSequentialAnimationGroup(this);
    int totalDuration = ANIM_DURATION;

    auto anim1 = new QPropertyAnimation(tip, "pos", this);
    anim1->setDuration(totalDuration * 0.7);
    anim1->setStartValue(startPos);
    anim1->setEndValue(elasticPos);
    anim1->setEasingCurve(QEasingCurve::OutCubic);

    auto anim2 = new QPropertyAnimation(tip, "pos", this);
    anim2->setDuration(totalDuration * 0.3);
    anim2->setStartValue(elasticPos);
    anim2->setEndValue(targetPos);
    anim2->setEasingCurve(QEasingCurve::OutBounce);

    animGroup->addAnimation(anim1);
    animGroup->addAnimation(anim2);

    auto opacityAnim = new QPropertyAnimation(tip, "opacity", this);
    opacityAnim->setDuration(totalDuration);
    opacityAnim->setStartValue(0.0);
    opacityAnim->setEndValue(1.0);
    opacityAnim->setEasingCurve(QEasingCurve::InQuad);

    auto parallelGroup = new QParallelAnimationGroup(this);
    parallelGroup->addAnimation(animGroup);
    parallelGroup->addAnimation(opacityAnim);

    connect(parallelGroup, &QParallelAnimationGroup::finished, this, [tip]() {
        tip->layout()->activate();
        tip->adjustSize();
        tip->raise();
    });

    parallelGroup->start(QAbstractAnimation::DeleteWhenStopped);
}


void MessageTipManager::animateTipOut(MessageTipWidget *tip)
{
    if (!tip || !m_mainWindow || tip->isHidden()) return;

    // 强制更新布局，获取真实高度
    tip->layout()->activate();
    tip->adjustSize();

    // 退出动画起始位置（当前显示位置）
    QPoint startPos = tip->pos();
    // 目标位置：主窗口右侧外（完全滑出可视区域）
    QPoint endPos = QPoint(m_mainWindow->width() + 50, startPos.y());
    // 轻微弹性过度位置（先向左滑一点，再向右滑出）
    QPoint elasticPos = QPoint(startPos.x() + 8, startPos.y());

    const int totalDuration = ANIM_DURATION; // 与入场动画时长一致（300ms）

    // 1. 位置动画序列（弹性滑出）
    QSequentialAnimationGroup *posAnimGroup = new QSequentialAnimationGroup(this);
    
    // 第一段：轻微左滑（弹性前奏）
    QPropertyAnimation *anim1 = new QPropertyAnimation(tip, "pos", this);
    anim1->setDuration(totalDuration * 0.2);
    anim1->setStartValue(startPos);
    anim1->setEndValue(elasticPos);
    anim1->setEasingCurve(QEasingCurve::OutCubic);

    // 第二段：快速向右滑出主窗口
    QPropertyAnimation *anim2 = new QPropertyAnimation(tip, "pos", this);
    anim2->setDuration(totalDuration * 0.8);
    anim2->setStartValue(elasticPos);
    anim2->setEndValue(endPos);
    anim2->setEasingCurve(QEasingCurve::InCubic);

    posAnimGroup->addAnimation(anim1);
    posAnimGroup->addAnimation(anim2);

    // 2. 透明度动画（同步淡出）
    QPropertyAnimation *opacityAnim = new QPropertyAnimation(tip, "opacity", this);
    opacityAnim->setDuration(totalDuration);
    opacityAnim->setStartValue(1.0);
    opacityAnim->setEndValue(0.0);
    opacityAnim->setEasingCurve(QEasingCurve::OutQuad);

    // 3. 并行执行两个动画
    QParallelAnimationGroup *exitAnimGroup = new QParallelAnimationGroup(this);
    exitAnimGroup->addAnimation(posAnimGroup);
    exitAnimGroup->addAnimation(opacityAnim);

    // ========== 核心修改：动画结束后执行「填充持久化消息 + 重排位置」 ==========
    connect(exitAnimGroup, &QParallelAnimationGroup::finished, this, [this, tip]() {
        // 步骤1：安全删除窗口
        if (tip && !tip->isHidden()) {
            tip->hide();
        }
        tip->deleteLater();

        // 步骤2：填充持久化消息（如有）
        this->checkPersistentTips();

        // 步骤3：重排所有消息位置（向下对齐填补空位，适配动态高度）
        this->rearrangeAllTips();
    });

    // 启动退出动画
    exitAnimGroup->start(QAbstractAnimation::DeleteWhenStopped);
}

void MessageTipManager::rearrangeAllTips()
{
    if (!m_mainWindow) return;

    // 步骤1：收集所有活跃消息（未处理、未被顶掉），并强制更新高度
    QList<QPointer<MessageTipWidget>> activeTips;
    for (int slot = 0; slot < MAX_TIP_COUNT; ++slot) {
        auto tip = m_tipSlots[slot];
        if (tip && !tip->isHandled() && !tip->isHiddenByPush()) {
            // 强制更新布局，确保高度是最新的（动态高度关键）
            tip->layout()->activate();
            tip->adjustSize();
            activeTips.append(tip);
        }
    }

    // 步骤2：清空原有slot（准备重新分配）
    for (int slot = 0; slot < MAX_TIP_COUNT; ++slot) {
        m_tipSlots[slot] = nullptr;
    }

    // 步骤3：从主窗口底部开始，向下对齐排列所有活跃消息
    const int margin = 10; // 消息与主窗口边缘的间距
    const int spacing = 10; // 消息之间的间距
    QRect clientRect = m_mainWindow->rect();
    
    // 起始Y坐标：主窗口底部 - 边距（向下对齐的基准点）
    int currentY = clientRect.bottom() - margin;

    // 反向遍历：从最后一条消息（最上方）开始，向上计算位置，保证最下方消息紧贴主窗口底部
    for (int i = activeTips.size() - 1; i >= 0; --i) {
        auto tip = activeTips[i];
        if (!tip) continue;

        // 步骤4：重新计算每个消息的位置（适配动态高度）
        int tipWidth = MessageTipWidget::WIDTH;
        int tipHeight = tip->height(); // 动态高度，非固定值

        // 向上偏移当前消息的高度（向下对齐核心）
        currentY -= tipHeight;
        // 计算最终位置（X固定，Y为当前偏移）
        QPoint tipPos(
            clientRect.right() - tipWidth - margin, // X坐标：主窗口右侧内边距
            currentY // Y坐标：向下对齐后的位置
        );

        // 边界保护：不超出主窗口顶部
        if (tipPos.y() < margin) {
            tipPos.setY(margin);
        }

        // 步骤5：重新分配slot + 更新位置（平滑移动，可选）
        int newSlot = activeTips.size() - 1 - i; // 最下方消息对应slot0
        if (newSlot < MAX_TIP_COUNT) {
            tip->setSlotIndex(newSlot);
            m_tipSlots[newSlot] = tip;
        }

        // 可选：添加位置过渡动画（避免瞬移，更流畅）
        QPropertyAnimation *posAnim = new QPropertyAnimation(tip, "pos", this);
        posAnim->setDuration(200); // 过渡动画时长
        posAnim->setStartValue(tip->pos());
        posAnim->setEndValue(tipPos);
        posAnim->setEasingCurve(QEasingCurve::OutCubic);
        posAnim->start(QAbstractAnimation::DeleteWhenStopped);

        // 确保消息在最上层
        tip->raise();

        // 步骤6：预留消息之间的间距
        currentY -= spacing;
    }
}

// MessageTipWidget *MessageTipManager::addMessage(bool persistent)
// {
//     int emptySlot = findFirstEmptySlot();
//     if (emptySlot == -1) {
//         emptySlot = MAX_TIP_COUNT - 1;
//         auto oldTip = m_tipSlots[emptySlot];
//         if (oldTip) {
//             if (oldTip->isPersistent() && !oldTip->isHandled()) {
//                 oldTip->setHiddenByPush(true);
//                 m_persistentTips.append(oldTip);
//             } else {
//                 oldTip->setHandled(true); // 触发退出动画，动画结束后重排
//             }
//             m_tipSlots[emptySlot] = nullptr;
//         }
//     }

//     auto tip = new MessageTipWidget(persistent, m_mainWindow);
//     tip->setSlotIndex(emptySlot);
//     tip->setOpacity(1.0);
    
//     // 强制更新布局，确保高度正确
//     tip->layout()->activate();
//     tip->adjustSize();
//     tip->show();
//     tip->raise();

//     // 绑定高度变化信号 → 重排位置（动态高度适配）
//     connect(tip, &MessageTipWidget::sizeChanged, this, &MessageTipManager::rearrangeAllTips);

//     // ========== 核心修改：仅清空slot，重排逻辑移到动画结束后 ==========
//     connect(tip, &MessageTipWidget::tipHandled, this, [this, tip]() {
//         int slot = tip->slotIndex();
//         if (slot >= 0 && slot < MAX_TIP_COUNT) {
//             m_tipSlots[slot] = nullptr; // 仅清空slot，不触发重排
//         }
//         // 移除：this->checkPersistentTips();
//     });

//     m_tipSlots[emptySlot] = tip;
//     // 延迟启动入场动画（给布局渲染留时间）
//     QTimer::singleShot(10, this, [this, tip]() {
//         tip->setOpacity(0.0);
//         animateTipIn(tip);
//     });

//     if (!persistent) {
//         QTimer::singleShot(MessageTipWidget::AUTO_CLOSE_DURATION, this, [this, tip]() {
//             if (!tip || tip->isPersistent() || tip->isHandled()) return;
//             tip->setHandled(true); // 触发退出动画，动画结束后重排
//         });
//     }

//     return tip;
// }

// 重载的 addMessage 函数无需修改（会调用上面的基础函数）
MessageTipWidget *MessageTipManager::addMessage(const QString &text, bool persistent)
{
    auto tip = addMessage(persistent);
    tip->setText(text);
    return tip;
}

// 基础重载：添加滞留时间参数
MessageTipWidget *MessageTipManager::addMessage(bool persistent, int stayTimeMs)
{
    int emptySlot = findFirstEmptySlot();
    if (emptySlot == -1) {
        emptySlot = MAX_TIP_COUNT - 1;
        auto oldTip = m_tipSlots[emptySlot];
        if (oldTip) {
            if (oldTip->isPersistent() && !oldTip->isHandled()) {
                oldTip->setHiddenByPush(true);
                m_persistentTips.append(oldTip);
            } else {
                oldTip->setHandled(true); // 触发退出动画
            }
            m_tipSlots[emptySlot] = nullptr;
        }
    }

    auto tip = new MessageTipWidget(persistent, m_mainWindow);
    tip->setSlotIndex(emptySlot);
    tip->setOpacity(1.0);
    
    // 强制更新布局，确保高度正确
    tip->layout()->activate();
    tip->adjustSize();
    tip->show();
    tip->raise();

    // 绑定高度变化信号 → 重排位置
    connect(tip, &MessageTipWidget::sizeChanged, this, &MessageTipManager::rearrangeAllTips);

    // 仅清空slot，重排逻辑移到动画结束后
    connect(tip, &MessageTipWidget::tipHandled, this, [this, tip]() {
        int slot = tip->slotIndex();
        if (slot >= 0 && slot < MAX_TIP_COUNT) {
            m_tipSlots[slot] = nullptr;
        }
    });

    m_tipSlots[emptySlot] = tip;
    // 延迟启动入场动画
    QTimer::singleShot(10, this, [this, tip]() {
        tip->setOpacity(0.0);
        animateTipIn(tip);
    });

    // ========== 核心逻辑：非持久化时使用滞留时间，持久化忽略 ==========
    if (!persistent) {
        // 校验滞留时间（避免传入0或负数，默认用5000ms）
        int actualStayTime = (stayTimeMs > 0) ? stayTimeMs : MessageTipWidget::AUTO_CLOSE_DURATION;
        // 按滞留时间设置自动关闭
        QTimer::singleShot(actualStayTime, this, [this, tip]() {
            if (!tip || tip->isPersistent() || tip->isHandled()) return;
            tip->setHandled(true); // 触发退出动画
        });
    }
    // 持久化时，不执行任何自动关闭逻辑（忽略滞留时间）

    return tip;
}

// 带文本重载：透传滞留时间参数
MessageTipWidget *MessageTipManager::addMessage(const QString &text, bool persistent, int stayTimeMs)
{
    // 调用基础重载，透传persistent和stayTimeMs
    auto tip = addMessage(persistent, stayTimeMs);
    tip->setText(text);
    return tip;
}

void MessageTipManager::checkPersistentTips()
{
    // 步骤1：清理无效持久化消息
    m_persistentTips.erase(std::remove_if(m_persistentTips.begin(), m_persistentTips.end(),
                                          [](const QPointer<MessageTipWidget> &p) {
                                              return !p || p->isHandled();
                                          }),
                           m_persistentTips.end());

    // 步骤2：填充持久化消息到空位置（仅当有持久化消息时）
    if (!m_persistentTips.isEmpty()) {
        int emptySlot = findFirstEmptySlot();
        if (emptySlot != -1) {
            auto persistentTip = m_persistentTips.takeFirst();
            if (!persistentTip || persistentTip->isHandled()) return;

            persistentTip->setSlotIndex(emptySlot);
            persistentTip->setHiddenByPush(false);
            m_tipSlots[emptySlot] = persistentTip;
            animateTipIn(persistentTip);
        }
    }

    rearrangeAllTips();
}

void MessageTipManager::onMainWindowChanged()
{
    if (!m_mainWindow) return;

    rearrangeAllTips();
}

bool MessageTipManager::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == m_mainWindow.data()) {
        // 响应主窗口移动、调整大小、显示/隐藏事件
        if (event->type() == QEvent::Move || 
            event->type() == QEvent::Resize ||
            event->type() == QEvent::Show) {
            onMainWindowChanged();
        }
    }
    return QObject::eventFilter(watched, event);
}