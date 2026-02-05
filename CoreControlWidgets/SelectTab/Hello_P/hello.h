#ifndef HELLO_H
#define HELLO_H

#include "QtPrecompiled.h"

#include "ClassSpace.h"

#include "BaseWidgets/BaseTab/BaseTab.h"

namespace CoreControlWidgets
{

namespace SelectTab_NS
{

class Hello_Page : public QWidget
{
    Q_OBJECT
    public: Hello_Page(QWidget *parent = 0);
    public: ~Hello_Page();

    public: QVBoxLayout *m_centerLayout = nullptr;


    protected: QWidget *m_topWidget = nullptr;    // 上层固定区域

    protected: QWidget *m_midWidget = nullptr;     // 中层可变区域

    protected: QWidget *m_downWidget = nullptr; // 下层固定区域

};


} // namespace CoreControlWidgets

} // namespace SelectTab_NS


#endif // HELLO_H