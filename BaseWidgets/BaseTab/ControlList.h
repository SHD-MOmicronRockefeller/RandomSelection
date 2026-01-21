#ifndef CONTROLLIST_H
#define CONTROLLIST_H

#include "QtPrecompiled.h"

namespace BaseWidgets {

namespace BaseElements {

class ControlList : public QWidget{
    Q_OBJECT
    public: ControlList(QWidget *parent = nullptr);
    public: ~ControlList();
    
    protected: QVBoxLayout* m_centerLayout = nullptr;


    public: QLabel * pushLable(QLabel *lbl = nullptr);
    public: QPushButton * pushButton(QPushButton *btn = nullptr);

    public: QPushButton *thisTabButton = nullptr;
    
};

} // namespace BaseElements


} // namespace BaseWidgets


#endif // CONTROLLIST_H