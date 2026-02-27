#ifndef LIST_SET_H
#define LIST_SET_H
#include "QtPrecompiled.h"

#include "listSetGroup.h"
#include "CoreCalculation/SelectTabFunc/OptionList.hpp"
#include <functional>

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

    protected: QScrollArea *m_setListScrollArea = nullptr;     // 中层可变区域

    protected: QWidget *m_downWidget = nullptr; // 下层固定区域

    public: std::function<void(CoreCalculation::OptionList)> setOptionList = nullptr;


};



} // namespace SelectTab_NS




} // namespace CoreControlWidgets




#endif // LIST_SET_H