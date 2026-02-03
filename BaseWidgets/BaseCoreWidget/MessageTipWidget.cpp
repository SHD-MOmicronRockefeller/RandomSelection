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
    setFixedSize(WIDTH, HEIGHT);

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
}

QPushButton *MessageTipWidget::addButton(const QString &text, Qt::Alignment alignment)
{
    auto btn = new QPushButton(text, this);
    btn->setStyleSheet(R"(
        QPushButton {
            background-color: #5865F2;
            color: white;
            border: none;
            padding: 4px 12px;
            border-radius: 4px;
            font-size: 12px;
        }
        QPushButton:hover {
            background-color: #4752C4;
        }
    )");
    addWidget(btn, alignment);
    return btn;
}

QLabel *MessageTipWidget::addLabel(const QString &text, Qt::Alignment alignment)
{
    auto label = new QLabel(text, this);
    label->setStyleSheet("color: #FFFFFF; font-size: 14px;");
    label->setWordWrap(true);
    addWidget(label, alignment);
    return label;
}

void MessageTipWidget::setText(const QString &text)
{
    addLabel(text);
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
    m_isHandled = handled;
    if (handled) {
        emit tipHandled();
        auto opacityAnim = new QPropertyAnimation(this, "opacity", this);
        opacityAnim->setDuration(200);
        opacityAnim->setStartValue(1.0);
        opacityAnim->setEndValue(0.0);
        connect(opacityAnim, &QPropertyAnimation::finished, this, &QWidget::deleteLater);
        opacityAnim->start(QPropertyAnimation::DeleteWhenStopped);
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

void MessageTipWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QBrush brush(QColor(40, 40, 40, 230));
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);
    painter.drawRoundedRect(rect(), 8, 8);
}

// ==================== MessageTipManager 实现 ====================
MessageTipManager &MessageTipManager::instance()
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

    // ===== 核心修改：基于主窗口客户区计算相对坐标 =====
    // 获取主窗口客户区（去掉标题栏/边框的实际可显示区域）
    // QRect clientRect = m_mainWindow->centralWidget() ? m_mainWindow->centralWidget()->rect() : m_mainWindow->rect();
    QRect clientRect = m_mainWindow->rect();
    
    const int margin = 10; // 消息与主窗口边缘的间距
    const int spacing = 10; // 消息之间的间距
    
    // 计算X坐标：主窗口客户区右侧 - 消息宽度 - 间距
    int x = clientRect.right() - MessageTipWidget::WIDTH - margin;
    // 计算Y坐标：主窗口客户区底部 - 消息高度 - 间距 - 每个位置的偏移
    int baseY = clientRect.bottom() - MessageTipWidget::HEIGHT - margin;
    int y = baseY - (MessageTipWidget::HEIGHT + spacing) * slotIndex;

    // 边界保护：避免消息超出主窗口可视区域
    if (x < margin) x = margin;
    if (y < margin) y = margin;

    return QPoint(x, y);
}

void MessageTipManager::animateTipIn(MessageTipWidget *tip)
{
    if (!tip || tip->slotIndex() < 0 || !m_mainWindow) return;

    QPoint targetPos = calculateTipPos(tip->slotIndex());
    // 初始位置：主窗口右侧外（相对坐标），保证从右向左滑入
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

    parallelGroup->start(QAbstractAnimation::DeleteWhenStopped);
}

MessageTipWidget *MessageTipManager::addMessage(bool persistent)
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
                oldTip->setHandled(true);
            }
            m_tipSlots[emptySlot] = nullptr;
        }
    }

    auto tip = new MessageTipWidget(persistent, m_mainWindow);
    tip->setSlotIndex(emptySlot);
    tip->setOpacity(0);
    tip->show();

    connect(tip, &MessageTipWidget::tipHandled, this, [this, tip]() {
        int slot = tip->slotIndex();
        if (slot >= 0 && slot < MAX_TIP_COUNT) {
            m_tipSlots[slot] = nullptr;
        }
        this->checkPersistentTips();
    });

    m_tipSlots[emptySlot] = tip;
    animateTipIn(tip);

    if (!persistent) {
        QTimer::singleShot(MessageTipWidget::AUTO_CLOSE_DURATION, this, [this, tip]() {
            if (!tip || tip->isPersistent() || tip->isHandled()) return;
            tip->setHandled(true);
        });
    }

    return tip;
}

MessageTipWidget *MessageTipManager::addMessage(const QString &text, bool persistent)
{
    auto tip = addMessage(persistent);
    tip->setText(text);
    return tip;
}

void MessageTipManager::checkPersistentTips()
{
    // 清理无效持久化消息
    m_persistentTips.erase(std::remove_if(m_persistentTips.begin(), m_persistentTips.end(),
                                          [](const QPointer<MessageTipWidget> &p) {
                                              return !p || p->isHandled();
                                          }),
                           m_persistentTips.end());

    // 填充空位置
    for (int slot = 0; slot < MAX_TIP_COUNT; ++slot) {
        if (!m_tipSlots[slot] || m_tipSlots[slot]->isHandled()) {
            if (!m_persistentTips.isEmpty()) {
                auto persistentTip = m_persistentTips.takeFirst();
                if (!persistentTip || persistentTip->isHandled()) continue;

                persistentTip->setSlotIndex(slot);
                persistentTip->setHiddenByPush(false);
                m_tipSlots[slot] = persistentTip;
                animateTipIn(persistentTip);
            }
        }
    }
}

void MessageTipManager::onMainWindowChanged()
{
    if (!m_mainWindow) return;

    // 遍历所有消息位置，更新相对主窗口的坐标
    for (int slot = 0; slot < MAX_TIP_COUNT; ++slot) {
        auto tip = m_tipSlots[slot];
        if (tip && !tip->isHandled() && !tip->isHiddenByPush()) {
            // 直接设置相对主窗口的坐标（无需mapToGlobal）
            tip->move(calculateTipPos(slot));
            // 确保消息窗口显示在主窗口之上（子窗口层级）
            tip->raise();
        }
    }
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