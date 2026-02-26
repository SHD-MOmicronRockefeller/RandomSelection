#ifndef MMRYITEM_H
#define MMRYITEM_H

#include "QtPrecompiled.h"
#include "ClassSpace.h"

#include "BaseWidgets/BaseCoreWidget/LayoutWidget.h"
#include "CoreCalculation/SelectTabFunc/OptionList.hpp"

namespace CoreControlWidgets {

namespace SelectTab_NS {

class MmryItem : public LayoutWidget
{
    Q_OBJECT
    public: explicit MmryItem(CoreCalculation::Base::OptionItem, QWidget *parent = nullptr);

    public: QHBoxLayout* mainLayout = nullptr;

    public: QLabel* selectedTimesLabel_Val = nullptr;

    public: CoreCalculation::Base::OptionItem optionItem;
    public: bool addOption(CoreCalculation::Base::OptionItem optionItem);
};



} // namespace SelectTab_NS




} // namespace CoreControlWidgets


#endif // MMRYITEM_H
