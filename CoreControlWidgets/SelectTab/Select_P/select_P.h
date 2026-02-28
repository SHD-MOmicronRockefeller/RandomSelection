#ifndef SELECT_P_H
#define SELECT_P_H

#include "QtPrecompiled.h"



#include "ClassSpace.h"

namespace CoreControlWidgets
{

namespace SelectTab_NS
{

class Select_Page : public QWidget
{
    Q_OBJECT
    public: Select_Page(QWidget *parent = 0);
    public: ~Select_Page();

    public: QVBoxLayout *m_centerLayout = nullptr;


    protected: QWidget *m_topWidget = nullptr;    // 上层固定区域

    protected: BaseWidgets::AspectRatioWidget *m_aspectMidWidget = nullptr; // 中间比例容器
    public: MidWidget* m_midWidget = nullptr;

    protected: QWidget *m_downWidget = nullptr; // 下层固定区域

};



} // namespace SelectTab_NS




} // namespace CoreControlWidgets




#endif // SELECT_P_H