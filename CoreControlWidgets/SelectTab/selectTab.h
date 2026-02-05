#ifndef SELECTTAB_H
#define SELECTTAB_H

#include "QtPrecompiled.h"

#include "ClassSpace.h"

#include "BaseWidgets/BaseTab/BaseTab.h"

namespace CoreControlWidgets{
class SelectTab : public BaseWidgets::BaseTab{
    Q_OBJECT
    public: SelectTab(QWidget *parent = nullptr);
    public: ~SelectTab();

    public: SelectTab_NS::Hello_Page *hello_page = nullptr;
    public: SelectTab_NS::Select_Page *select_page = nullptr;
    public: SelectTab_NS::SelectFile_Page *selectFile_page = nullptr;
    public: SelectTab_NS::ListSet_Page *listSet_page = nullptr;
    public: SelectTab_NS::BasicSet_Page *basicSet_page = nullptr;
};





} // namespace CoreControlWidgets


#endif // SELECTTAB_H