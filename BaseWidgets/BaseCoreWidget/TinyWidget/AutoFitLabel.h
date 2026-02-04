#ifndef AUTOFITLABEL_H
#define AUTOFITLABEL_H

#include <QLabel>
#include <QResizeEvent>
#include <QFont>
#include <QFontMetrics>
#include <QRect>

namespace BaseWidgets {

class AutoFitLabel : public QLabel
{
    Q_OBJECT

    // 构造函数：兼容QLabel的使用方式
    public: explicit AutoFitLabel(const QString& text, QWidget* parent = nullptr);
    public: explicit AutoFitLabel(QWidget* parent = nullptr);

    // 重写尺寸变化事件：标签缩放时自动调整字体
    protected: void resizeEvent(QResizeEvent* event) override;

    // 初始化标签基础设置
    private: void initLabelSettings();
    // 核心：计算适配标签尺寸的字体大小
    public: void adjustFontSize();

    protected: QSize minimumSizeHint() const override;
};

} // namespace BaseWidgets

#endif // AUTOFITLABEL_H