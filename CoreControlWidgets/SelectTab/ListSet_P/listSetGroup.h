//
// Created by Administrator on 2026/2/26.
//

#ifndef LISTSETGROUP_H
#define LISTSETGROUP_H

#include "BaseWidgets/BaseCoreWidget/LayoutWidget.h"
#include "CoreCalculation/DoubleFileClass/ReadFile/ImportFile.h"
#include "listSetOption.h"


namespace CoreControlWidgets {


namespace SelectTab_NS {


class ListSetGroup : public LayoutWidget
{
    public: ListSetGroup(QString group, CoreCalculation::OptionList optionList,QWidget *parent = nullptr); // Constructor

    public: QVBoxLayout* titleLayouts; // Title layout
    public: QFrame* mainFrame;
    public: QVBoxLayout* mainLayout;

    public: QList<ListSetOption*> buttonList;

};


}


}


#endif //LISTSETGROUP_H