#ifndef IPT_TOLIST_H
#define IPT_TOLIST_H

#include "QtPrecompiled.h"

#include "ClassSpace.h"

#include <functional>

namespace CoreControlWidgets
{

namespace SelectTab_NS
{

class IPT_Base : public QWidget
{
    Q_OBJECT
    
    signals: void dragEntered();  // 子控件进入拖拽
    signals: void dragLeaved();   // 子控件离开拖拽

    public: IPT_Base(QString _ObjectName, std::function<void(QString)> _func, QWidget *parent = 0);

    private: std::function<void(QString)> importFunction;

    private: QVBoxLayout *m_mainLayout = nullptr;
    private: BaseWidgets::AutoFitLabel *m_titleLabel = nullptr;

    private: QString defaultText = "< --- >";
    public: void setDefaultText(const QString &title);
    private: void setDefaultStyle();

    private: QString targetText = "> --- <";
    public: void setTargetText(const QString &title);
    private: void setTargetStyle();

    public: bool m_isInDrag = false; // 是否在拖拽中

    protected: void dragEnterEvent(QDragEnterEvent *event) override;  // 拖入事件
    protected: void dragLeaveEvent(QDragLeaveEvent *event) override;  // 拖动事件

    public: QString m_filePath = "";
    protected: void dropEvent(QDropEvent *event) override;  // 放下事件

};

} // namespace SelectTab_NS

} // namespace CoreControlWidgets


#endif // IPT_TOLIST_H