#ifndef SELECTTAB_H
#define SELECTTAB_H

#include "QtPrecompiled.h"

#include "BaseWidgets/BaseTab/BaseTab.h"

#include "midWidget.h"

#include "BaseWidgets/BaseCoreWidget/AspectRatioWidget.h"

namespace CoreControlWidgets{
class SelectTab : public BaseWidgets::BaseTab{
    Q_OBJECT
    public: SelectTab(QWidget *parent = nullptr);
    public: ~SelectTab();

    protected: QWidget *m_topWidget = nullptr;    // 上层固定区域

    protected: BaseWidgets::AspectRatioWidget *m_aspectMidWidget = nullptr; // 中间比例容器
    protected: SelectTab_NS::MidWidget* m_midWidget = nullptr;

    protected: QWidget *m_bottomWidget = nullptr; // 下层固定区域
};





} // namespace CoreControlWidgets


#endif // SELECTTAB_H