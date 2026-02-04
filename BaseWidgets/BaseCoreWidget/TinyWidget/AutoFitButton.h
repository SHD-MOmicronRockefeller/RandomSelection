#ifndef RESIZEBUTTON_H
#define RESIZEBUTTON_H

#include <QPushButton>
#include <QResizeEvent>
#include <QFont>
#include <QFontMetrics>
#include <QRect>

namespace BaseWidgets
{

class AutoFitButton : public QPushButton
{
    Q_OBJECT  // Qt控件标准宏，支持信号槽（后续可扩展）
    // 构造函数：支持传入文字和父控件，兼容原有QPushButton使用方式
    public: explicit AutoFitButton(const QString& text, QWidget* parent = nullptr);
    public: explicit AutoFitButton(QWidget* parent = nullptr); // 重载无文字构造

    // 重写尺寸变化事件：按钮大小改变时触发字体适配
    protected: void resizeEvent(QResizeEvent* event) override;
    protected: void initButtonSettings();

    // 核心私有方法：计算并设置适配按钮尺寸的字体大小
    protected: void adjustFontSize();  
    
    protected: QSize minimumSizeHint() const override;
};


} // namespace BaseWidgets




#endif // RESIZEBUTTON_H