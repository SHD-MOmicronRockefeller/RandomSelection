#ifndef SELECTTAB_H
#define SELECTTAB_H

#include "QtPrecompiled.h"

#include "BaseWidgets/BaseTab/BaseTab.h"

#include "Select_P/select_P.h"

namespace CoreControlWidgets{
class SelectTab : public BaseWidgets::BaseTab{
    Q_OBJECT
    public: SelectTab(QWidget *parent = nullptr);
    public: ~SelectTab();

    public: SelectTab_NS::Select_Page *select_page = nullptr;
};





} // namespace CoreControlWidgets


#endif // SELECTTAB_H