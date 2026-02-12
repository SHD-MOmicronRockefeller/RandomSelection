#ifndef LIST_SET_H
#define LIST_SET_H
#include "QtPrecompiled.h"


namespace CoreControlWidgets
{

namespace SelectTab_NS
{

class ListSet_Page : public QWidget
{
    Q_OBJECT
    public: ListSet_Page(QWidget *parent = 0);
    public: ~ListSet_Page();

    public: QVBoxLayout *m_centerLayout = nullptr;


    protected: QWidget *m_topWidget = nullptr;    // 上层固定区域

    protected: QWidget *m_midWidget = nullptr;     // 中层可变区域

    protected: QWidget *m_downWidget = nullptr; // 下层固定区域


};



} // namespace SelectTab_NS




} // namespace CoreControlWidgets




#endif // LIST_SET_H