#ifndef COLLAPSIBLEWIDGET_H
#define COLLAPSIBLEWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QResizeEvent>
#include <QMouseEvent>

class CollapsibleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CollapsibleWidget(const QString& title = "", QWidget *parent = nullptr);

    // 核心接口：设置内容（支持传入控件或布局）
    void setContentWidget(QWidget* widget);
    void setContentLayout(QLayout* layout);

    // 获取当前展开状态
    bool isExpanded() const;

    signals:
        // 展开/收起切换时触发，isExpand=true为展开
        void toggled(bool isExpand);

    public slots:
        // 切换展开/收起状态
        void toggle(bool expand);

    protected:
    // 重写点击事件：点击头部切换状态
    void mousePressEvent(QMouseEvent *event) override;
    // 重写大小变化事件：窗口伸缩时自动同步内容区高度，保持60%占比
    void resizeEvent(QResizeEvent *event) override;

    private:
    void initUI();
    // 计算内容区目标高度：窗口高度的60%
    int getContentTargetHeight() const;

    // UI控件
    QWidget* m_headerWidget;       // 头部（标题+箭头）
    QPushButton* m_arrowBtn;       // 右侧箭头按钮
    QLabel* m_titleLabel;          // 标题文本
    QScrollArea* m_contentArea;    // 内置滚动区域，固定占窗口60%高度
    QWidget* m_contentContainer;   // 内容容器，用于承载用户的列表/控件
    QVBoxLayout* m_mainLayout;     // 主布局

    bool m_isExpanded = false;      // 已固定：默认收起，初始值为false
};

#endif // COLLAPSIBLEWIDGET_H