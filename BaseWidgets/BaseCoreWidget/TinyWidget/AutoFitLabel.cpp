#include "AutoFitLabel.h"

namespace BaseWidgets {

// 带文字构造函数
AutoFitLabel::AutoFitLabel(const QString& text, int _subSize, QWidget* parent)
    : QLabel(text, parent), m_subSize(_subSize)
{
    initLabelSettings();
}

// 无文字构造函数
AutoFitLabel::AutoFitLabel(QWidget* parent, int _subSize)
    : QLabel(parent), m_subSize(_subSize)
{
    initLabelSettings();
}

// 初始化标签：核心是禁止自动换行，支持手动换行
void AutoFitLabel::initLabelSettings()
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setMinimumSize(0, 0);
    setContentsMargins(0, 0, 0, 0);
    setTextInteractionFlags(Qt::NoTextInteraction);
    setAlignment(Qt::AlignCenter); 
    setWordWrap(false); // 关键：禁止控件自动换行（只认手动\n）

    QFont font = this->font();
    font.setFamily("Microsoft YaHei"); // 适配中文
    setFont(font);
}

// 尺寸变化时触发字体适配
void AutoFitLabel::resizeEvent(QResizeEvent* event)
{
    QLabel::resizeEvent(event);
    adjustFontSize();
}

// 核心：计算适配手动换行文本的字体大小
void AutoFitLabel::adjustFontSize()
{
    if (text().isEmpty()) return;

    QFont font = this->font();
    QRect labelContentRect = this->contentsRect();
    if (labelContentRect.isEmpty()) return;

    // 1. 修正qMin类型不匹配问题（int和double不能直接比较）
    int maxFontSize = qMin<int>(
        labelContentRect.width() / 5,          // 宽度维度最大字体上限
        static_cast<int>(labelContentRect.height() / 2.2) // 高度维度（转int）
    );
    const int minFontSize = 8; // 字体最小保底，避免过小
    if (maxFontSize < minFontSize) maxFontSize = minFontSize;

    int bestFontSize = minFontSize;
    // 从大到小遍历，找到最大的适配字体（保证最优）
    for (int fontSize = maxFontSize; fontSize >= minFontSize; fontSize--)
    {
        font.setPointSize(fontSize);
        QFontMetrics fm(font);

        // 2. 关键：仅保留对齐方式，去掉TextWordWrap → 支持\n手动换行、禁止自动换行
        QRect textRect = fm.boundingRect(
            labelContentRect,
            Qt::AlignCenter, // 只保留居中对齐，不指定自动换行枚举
            text()           // 会识别字符串中的\n，按手动换行计算尺寸
        );

        // 3. 空白补偿：抵消复杂字符串的间距
        textRect = textRect.adjusted(4, 4, -4, -4);

        // 4. 收紧阈值：避免长文本/多行文本书写过大
        int widthThreshold = labelContentRect.width() * 0.88;
        int heightThreshold = labelContentRect.height() * 0.90;

        // 同时满足宽度、高度适配
        bool widthFit = textRect.width() <= widthThreshold;
        bool heightFit = textRect.height() <= heightThreshold;

        if (widthFit && heightFit)
        {
            bestFontSize = fontSize;
            break; // 从大到小找，第一个符合的就是最大可用尺寸
        }
    }

    // 最终字体大小：适配值 - 偏移值（保留灵活调整）
    int finalFontSize = bestFontSize - m_subSize;
    if (finalFontSize < minFontSize) finalFontSize = minFontSize;
    font.setPointSize(finalFontSize);
    setFont(font);
}

QSize AutoFitLabel::minimumSizeHint() const
{
    return QSize(0, 0);
}

} // namespace BaseWidgets