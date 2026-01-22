#include "AspectRatioWidget.h"

namespace BaseWidgets {


AspectRatioWidget::AspectRatioWidget(double ratio, QWidget *parent)
    : QWidget(parent), m_aspectRatio(ratio)
{
    // 核心：用布局管理内容，避免手动move/setFixedSize冲突
    QVBoxLayout *contentLayout = new QVBoxLayout(this);
    contentLayout->setContentsMargins(0, 0, 0, 0);
    contentLayout->setAlignment(Qt::AlignCenter); // 布局自动居中，替代手动move
    setLayout(contentLayout);

    // 允许自身随父布局收缩/扩展（关键）
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void AspectRatioWidget::setContentWidget(QWidget *widget)
{
    if (m_contentWidget) {
        layout()->removeWidget(m_contentWidget); // 移除旧控件
        m_contentWidget->deleteLater();
    }

    m_contentWidget = widget;
    if (m_contentWidget) {
        m_contentWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        layout()->addWidget(m_contentWidget); // 交给布局管理
    }
}

void AspectRatioWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event); // 先执行父类resize，保证布局正常更新
    if (!m_contentWidget) return;

    // 计算符合比例的最大可用尺寸（不超过自身当前大小）
    int maxW = event->size().width();
    int maxH = event->size().height();
    int targetW = maxW;
    int targetH = qRound(targetW / m_aspectRatio);

    // 若高度超了，按高度反算宽度（保持比例）
    if (targetH > maxH) {
        targetH = maxH;
        targetW = qRound(targetH * m_aspectRatio);
    }

    // 关键修改：用setMaximumSize限制最大尺寸，而非setFixedSize（允许布局收缩）
    m_contentWidget->setMaximumSize(targetW, targetH);
    m_contentWidget->setMinimumSize(targetW * 0.1, targetH * 0.1); // 允许缩小到10%（可调整
}

    
} // BaseWidgets
