#ifndef CUSTOMTITLEBAR_H
#define CUSTOMTITLEBAR_H

#include "QtPrecompiled.h"

namespace MainWindow {

class CustomTitleBar : public QWidget
{
    Q_OBJECT  // 必须保留！缺失会导致信号无法识别
public:
    explicit CustomTitleBar(QWidget *parent = nullptr);
    void setTitleText(const QString &text);

// 信号必须声明在 signals: 区段
signals:
    void sigMinimize();       // 最小化信号
    void sigClose();          // 关闭信号（必须和实现中一致）
    void sigSetting();        // 设置信号（必须和实现中一致）
    void sigMidBtnClicked(int index); // 中间按钮点击信号（带参数）

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    void initLayout();
    void initWidgets();
    void initStyle();

    // 布局成员
    QHBoxLayout *m_mainLayout = nullptr;
    QHBoxLayout *m_leftLayout = nullptr;
    QHBoxLayout *m_midLayout = nullptr;
    QHBoxLayout *m_rightLayout = nullptr;

    // 控件成员
    QLabel *m_iconLabel = nullptr;
    QLabel *m_titleLabel = nullptr;
    QList<QPushButton *> m_midBtns;
    QPushButton *m_btnSetting = nullptr;
    QPushButton *m_btnMin = nullptr;
    QPushButton *m_btnClose = nullptr;

    // 拖动相关
    bool m_isDragging = false;
    QPoint m_dragStartPos;
};

} // namespace MainWindow

#endif // CUSTOMTITLEBAR_H