//
// Created by Administrator on 2026/2/26.
//

#ifndef LISTSETOPTION_H
#define LISTSETOPTION_H

//
// Created by Administrator on 2026/2/26.


#include "BaseWidgets/BaseCoreWidget/TinyWidget/AutoFitButton.h"
#include "CoreCalculation/SelectTabFunc/OptionList.hpp"


namespace CoreControlWidgets {


namespace SelectTab_NS {


class ListSetOption : public BaseWidgets::AutoFitButton
{
    public: ListSetOption(CoreCalculation::Base::OptionItem optionItem,QWidget *parent = nullptr); // Constructor

    bool isSelected = true;
    CoreCalculation::Base::OptionItem optionItem;

    public: void changeColor();
    public: void setGreenColor();
    public: void setRedColor();

    protected: void resizeEvent(QResizeEvent *event) override;
};


}


}


#endif //LISTSETOPTION_H