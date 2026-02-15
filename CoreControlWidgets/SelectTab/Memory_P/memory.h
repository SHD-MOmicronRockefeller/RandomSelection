//
// Created by Administrator on 2026/2/15.
//

#ifndef MEMORY_PAGE_H
#define MEMORY_PAGE_H
#include "QtPrecompiled.h"

namespace CoreControlWidgets
{

namespace SelectTab_NS
{

class Memory_Page : public QWidget
{
    Q_OBJECT
    public: Memory_Page(QWidget *parent = 0);
    public: ~Memory_Page();

    public: QVBoxLayout *m_centerLayout = nullptr;

    protected: QScrollArea *m_optionListScrollArea = nullptr;     // 中层可变区域

    protected: QWidget *m_downWidget = nullptr; // 下层固定区域


};



} // namespace SelectTab_NS




} // namespace CoreControlWidgets


#endif //MEMORY_PAGE_H