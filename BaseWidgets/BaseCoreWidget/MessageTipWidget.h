#ifndef MESSAGETIPWIDGET_H
#define MESSAGETIPWIDGET_H

#include "QtPrecompiled.h"
#include "ClassSpace.h"
#include <QPropertyAnimation>


class MessageTipWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QPoint pos READ pos WRITE move)
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity)

public:
    explicit MessageTipWidget(bool persistent = false, QWidget *parent = nullptr);
    ~MessageTipWidget() override;

    // 位置索引相关
    int slotIndex() const;
    void setSlotIndex(int index);

    // 控件添加接口
    void addWidget(QWidget *widget, Qt::Alignment alignment = Qt::AlignLeft | Qt::AlignVCenter);
    QPushButton *addButton(const QString &text, Qt::Alignment alignment = Qt::AlignRight | Qt::AlignVCenter);
    QLabel *addLabel(const QString &text, Qt::Alignment alignment = Qt::AlignLeft | Qt::AlignVCenter);
    void setText(const QString &text);

    // 状态控制接口
    bool isPersistent() const;
    void setPersistent(bool persistent);
    bool isHandled() const;
    void setHandled(bool handled);
    bool isHiddenByPush() const;
    void setHiddenByPush(bool hidden);
    qreal opacity() const;
    void setOpacity(qreal opacity);

    // 常量定义
    static constexpr int WIDTH = 320;
    static constexpr int HEIGHT = 60;
    static constexpr int AUTO_CLOSE_DURATION = 5000;

signals:
    void tipHandled(); // 消息被处理的信号

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    // 成员变量
    bool m_isPersistent;
    bool m_isHandled;
    bool m_isHiddenByPush;
    qreal m_opacity;
    int m_slotIndex;
    QVBoxLayout *m_mainLayout;
    QHBoxLayout *m_btnLayout;
};


// 消息提示管理器（单例）
class MessageTipManager : public QObject
{
    Q_OBJECT

public:
    static MessageTipManager &instance();
    ~MessageTipManager() override;

    void init(QWidget *mainWindow);
    MessageTipWidget *addMessage(bool persistent = false);
    MessageTipWidget *addMessage(const QString &text, bool persistent = false);

private slots:
    void onMainWindowChanged();
    void checkPersistentTips(); // 检查并填充空位置

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    explicit MessageTipManager(QObject *parent = nullptr);
    MessageTipManager(const MessageTipManager &) = delete;
    MessageTipManager &operator=(const MessageTipManager &) = delete;

    // 核心方法声明
    QPoint calculateTipPos(int slotIndex);
    int findFirstEmptySlot();
    void animateTipIn(MessageTipWidget *tip);

    // 常量定义
    static constexpr int MAX_TIP_COUNT = 3;
    static constexpr int ANIM_DURATION = 300;
    static constexpr int ELASTIC_OFFSET = 8;

    // 成员变量
    QPointer<QWidget> m_mainWindow;
    QPointer<MessageTipWidget> m_tipSlots[MAX_TIP_COUNT];
    QList<QPointer<MessageTipWidget>> m_persistentTips;
};

#endif // MESSAGETIPWIDGET_H