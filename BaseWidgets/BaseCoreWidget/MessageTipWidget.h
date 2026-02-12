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

    public: explicit MessageTipWidget(bool persistent = false, QWidget *parent = nullptr);
    public: ~MessageTipWidget() override;

    // 位置索引相关
    public: int slotIndex() const;
    public: void setSlotIndex(int index);

    // 控件添加接口
    public: void addWidget(QWidget *widget, Qt::Alignment alignment = Qt::AlignLeft | Qt::AlignVCenter);
    public: QPushButton *addButton(const QString &text, Qt::Alignment alignment = Qt::AlignRight | Qt::AlignVCenter);
    public: QLabel *addLabel(const QString &text, Qt::Alignment alignment = Qt::AlignLeft | Qt::AlignVCenter);
    public: void setText(const QString &text);

    // 状态控制接口
    public: bool isPersistent() const;
    public: void setPersistent(bool persistent);
    public: bool isHandled() const;
    public: void setHandled(bool handled);
    public: bool isHiddenByPush() const;
    public: void setHiddenByPush(bool hidden);
    public: qreal opacity() const;
    public: void setOpacity(qreal opacity);

    public: MessageTipWidget* setBackgroundColor(const QColor &color);
    public: MessageTipWidget* setTextColor(const QColor &color);
    public: MessageTipWidget* setButtonColor(const QColor &color);

    // 常量定义
    public: static constexpr int WIDTH = 320;
    // public: static constexpr int HEIGHT = 60;
    public: static constexpr int AUTO_CLOSE_DURATION = 5000;

    signals: void tipHandled(); // 消息被处理的信号
    signals: void sizeChanged(); // 尺寸变化的信号


    protected: void paintEvent(QPaintEvent *event) override;

    // 成员变量
    private: bool m_isPersistent;
    private: bool m_isHandled;
    private: bool m_isHiddenByPush;
    private: qreal m_opacity;
    private: int m_slotIndex;
    private: QVBoxLayout *m_mainLayout;
    private: QHBoxLayout *m_btnLayout;

    private: QColor m_bgColor = QColor(40, 40, 40, 230);       // 默认背景色（深灰半透明）
    private: QColor m_textColor = QColor(255, 255, 255);       // 默认文本色（白色）
    private: QColor m_buttonColor = QColor(88, 101, 242);      // 默认按钮色（紫色
};


// 消息提示管理器（单例）
class MessageTipManager : public QObject
{
    Q_OBJECT

    public: static MessageTipManager &getInstance();
    public: ~MessageTipManager() override;

    public: void init(QWidget *mainWindow);
    public: MessageTipWidget *addMessage(const QString &text, bool persistent);
    public: MessageTipWidget *addMessage(bool persistent = false, int stayTimeMs = MessageTipWidget::AUTO_CLOSE_DURATION);
    public: MessageTipWidget *addMessage(const QString &text, bool persistent, int stayTimeMs);


    private slots: void onMainWindowChanged();
    private slots: void checkPersistentTips(); // 检查并填充空位置

    protected: bool eventFilter(QObject *watched, QEvent *event) override;

    private: explicit MessageTipManager(QObject *parent = nullptr);
    private: MessageTipManager(const MessageTipManager &) = delete;
    private: MessageTipManager &operator=(const MessageTipManager &) = delete;

    // 核心方法声明
    private: QPoint calculateTipPos(int slotIndex);
    private: int findFirstEmptySlot();

    public: void animateTipIn(MessageTipWidget *tip);
    public: void animateTipOut(MessageTipWidget *tip);

    // 常量定义
    private: static constexpr int MAX_TIP_COUNT = 5;
    private: static constexpr int ANIM_DURATION = 300;
    private: static constexpr int ELASTIC_OFFSET = 8;

    // 成员变量
    private: QPointer<QWidget> m_mainWindow;
    private: QPointer<MessageTipWidget> m_tipSlots[MAX_TIP_COUNT];
    private: QList<QPointer<MessageTipWidget>> m_persistentTips;
    public:  void rearrangeAllTips();
};

#endif // MESSAGETIPWIDGET_H