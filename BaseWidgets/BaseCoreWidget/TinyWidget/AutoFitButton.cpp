#include "AutoFitButton.h"

namespace BaseWidgets {

// 构造函数1：带文字参数
AutoFitButton::AutoFitButton(const QString& text, int _subSize, QWidget* parent)
    : QPushButton(text, parent) , m_subSize(_subSize)
{
    initButtonSettings();
}

// 构造函数2：无文字参数（兼容默认构造场景）
AutoFitButton::AutoFitButton(QWidget* parent)
    : QPushButton(parent)
{
    initButtonSettings();
}

// 初始化按钮基础设置（抽离通用逻辑，避免重复）
void AutoFitButton::initButtonSettings()
{
    // 布局主导尺寸：不固定宽高，由布局拉伸因子控制
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    // 屏蔽文字对最小尺寸的影响，布局可自由分配空间
    setMinimumSize(0, 0);
    // 文字默认居中（优化视觉效果）
    this->setStyleSheet(R"(
        QPushButton {
            /* 正常状态 - 白色主体 */
            background-color: #FFFFFF;
            border: 1px solid transparent; /* 透明边框，避免位移 */
            border-radius: 3px; /* 轻微圆角，贴近PCL2风格 */
            padding: 6px 12px; /* 内边距，根据需求调整 */
            color: #333333; /* 文字颜色 */
        }

        QPushButton:hover {
            /* 悬停状态 - 轻微淡蓝边 */
            border: 1px solid #E0F0FF; /* 极浅淡蓝，不突兀 */
        }

        QPushButton:pressed {
            /* 点击状态 - 略深一点的淡蓝边，强化反馈 */
            border: 1px solid #D0E8FF;
            background-color: #F8FBFF; /* 点击时背景轻微变浅，增强交互感 */
        }

        /* 禁用状态可选（按需添加） */
        QPushButton:disabled {
            background-color: #F5F5F5;
            color: #AAAAAA;
            border-color: transparent;
        }
    )");

    QFont font = this->font();
    font.setFamily("Microsoft YaHei");
    setFont(font);
}

// 尺寸变化事件：按钮缩放时自动适配字体
void AutoFitButton::resizeEvent(QResizeEvent* event)
{
    QPushButton::resizeEvent(event); // 调用父类方法，确保基础功能正常
    adjustFontSize(); // 触发字体适配逻辑
}

// 核心逻辑：计算按钮内可显示的最大字体大小
void AutoFitButton::adjustFontSize()
{
    if (text().isEmpty()) return;

    QFont font = this->font();
    QRect btnContentRect = this->contentsRect();
    if (btnContentRect.isEmpty()) return;

    // 中文适配：放宽字体上限（宽/4、高/2）
    int maxFontSize = qMin(btnContentRect.width() / 4, btnContentRect.height() / 2);
    int minFontSize = 0;
    if (maxFontSize < minFontSize) maxFontSize = minFontSize;

    int bestFontSize = minFontSize;
    for (int fontSize = maxFontSize; fontSize >= minFontSize; fontSize--)
    {
        font.setPointSize(fontSize);
        QFontMetrics fm(font);

        QRect textRect = fm.boundingRect(
            btnContentRect,
            Qt::AlignCenter | Qt::TextWordWrap,
            text()
        );

        textRect = textRect.adjusted(2, 2, -2, -2); // 向内缩2px

        // 95%阈值，避免中文偏小/溢出
        int widthThreshold = btnContentRect.width() * 0.95;
        int heightThreshold = btnContentRect.height() * 0.95;

        bool widthFit = textRect.width() <= widthThreshold;
        bool heightFit = textRect.height() <= heightThreshold;

        if (widthFit && heightFit)
        {
            bestFontSize = fontSize - m_subSize;
            break;
        }
    }

    font.setPointSize(bestFontSize);
    setFont(font);
}

QSize AutoFitButton::minimumSizeHint() const
{
    return QSize(0, 0);
}

} // namespace BaseWidgets