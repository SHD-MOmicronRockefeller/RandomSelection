#ifndef BASIC_SET_H
#define BASIC_SET_H
#include "QtPrecompiled.h"


namespace CoreControlWidgets
{

namespace SelectTab_NS
{

class BasicSet_Page : public QWidget
{
    Q_OBJECT
    public: BasicSet_Page(QWidget *parent = 0);
    public: ~BasicSet_Page();

    public: QVBoxLayout *m_centerLayout = nullptr;


    protected: QWidget *m_topWidget = nullptr;    // 上层固定区域

    protected: QWidget *m_midWidget = nullptr;     // 中层可变区域

    protected: QWidget *m_downWidget = nullptr; // 下层固定区域


};



} // namespace SelectTab_NS




} // namespace CoreControlWidgets




#endif // BASIC_SET_H