#include "AspectRatioWidget.h"

namespace BaseWidgets {


AspectRatioWidget::AspectRatioWidget(QWidget *parent, double ratio)
    : QWidget(parent), m_aspectRatio(ratio)
{

    QVBoxLayout *contentLayout = new QVBoxLayout(this);
    contentLayout->setContentsMargins(0, 0, 0, 0);
    contentLayout->setAlignment(Qt::AlignCenter);
    setLayout(contentLayout);

    // 允许自身随父布局收缩/扩展
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

    // 计算符合比例的最大可用尺寸
    int maxW = event->size().width();
    int maxH = event->size().height();
    int targetW = maxW;
    int targetH = qRound(targetW / m_aspectRatio);

    // 若高度超了，按高度反算宽度
    if (targetH > maxH) {
        targetH = maxH;
        targetW = qRound(targetH * m_aspectRatio);
    }

    // 关键修改：用setMaximumSize限制最大尺寸
    m_contentWidget->setMaximumSize(targetW, targetH);
    m_contentWidget->setMinimumSize(targetW * 0.1, targetH * 0.1); // 允许缩小到10%
}

    
} // BaseWidgets
