#include "AutoFitLabel.h"

namespace BaseWidgets {

// 带文字构造函数
AutoFitLabel::AutoFitLabel(const QString& text, QWidget* parent)
    : QLabel(text, parent)
{
    initLabelSettings();
}

// 无文字构造函数
AutoFitLabel::AutoFitLabel(QWidget* parent)
    : QLabel(parent)
{
    initLabelSettings();
}

// 初始化标签：布局主导尺寸，文字不撑大标签
void AutoFitLabel::initLabelSettings()
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding); // 布局分配尺寸
    setMinimumSize(0, 0); // 屏蔽文字对最小尺寸的影响
    setContentsMargins(0, 0, 0, 0); // 边框无效
    setTextInteractionFlags(Qt::NoTextInteraction); // 禁止编辑
    setAlignment(Qt::AlignCenter); // 文字居中
    setWordWrap(false); // 禁止换行（避免文字换行打乱布局）

    QFont font = this->font();
    font.setFamily("Microsoft YaHei"); // 微软雅黑，适配中文
    setFont(font);
}

// 尺寸变化时触发字体适配
void AutoFitLabel::resizeEvent(QResizeEvent* event)
{
    QLabel::resizeEvent(event);
    adjustFontSize();
}

// 计算标签内可显示的最大字体大小
void AutoFitLabel::adjustFontSize()
{
    if (text().isEmpty()) return;

    QFont font = this->font();
    QRect labelContentRect = this->contentsRect();
    if (labelContentRect.isEmpty()) return;

    // 中文适配：放宽字体上限（宽/4、高/2）
    int maxFontSize = qMin(labelContentRect.width() / 4, labelContentRect.height() / 2);
    int minFontSize = 0;
    if (maxFontSize < minFontSize) maxFontSize = minFontSize;

    int bestFontSize = minFontSize;
    for (int fontSize = maxFontSize; fontSize >= minFontSize; fontSize--)
    {
        font.setPointSize(fontSize);
        QFontMetrics fm(font);

        QRect textRect = fm.boundingRect(
            labelContentRect,
            Qt::AlignCenter | Qt::TextWordWrap,
            text()
        );

        textRect = textRect.adjusted(2, 2, -2, -2); // 向内缩2px，去掉额外空白

        // 95%阈值，平衡中文显示大小和溢出
        int widthThreshold = labelContentRect.width() * 0.95;
        int heightThreshold = labelContentRect.height() * 0.95;

        bool widthFit = textRect.width() <= widthThreshold;
        bool heightFit = textRect.height() <= heightThreshold;

        if (widthFit && heightFit)
        {
            bestFontSize = fontSize;
            break;
        }
    }

    font.setPointSize(bestFontSize);
    setFont(font);
}

QSize AutoFitLabel::minimumSizeHint() const
{
    return QSize(0, 0);
}

} // namespace BaseWidgets