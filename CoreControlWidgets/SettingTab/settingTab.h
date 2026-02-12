#ifndef SETTINGTAB_H
#define SETTINGTAB_H

#include "QtPrecompiled.h"

#include "ClassSpace.h"

#include "BaseWidgets/BaseTab/BaseTab.h"

namespace CoreControlWidgets{
class SettingTab : public BaseWidgets::BaseTab{
    Q_OBJECT
    public: SettingTab(QWidget *parent = nullptr);
};





} // namespace CoreControlWidgets


#endif // SETTINGTAB_H