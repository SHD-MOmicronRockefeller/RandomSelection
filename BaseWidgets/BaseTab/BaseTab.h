#ifndef BASETAB_H
#define BASETAB_H

#include "QtPrecompiled.h"

#include "BaseWidgets/BaseTab/ControlList.h"

namespace BaseWidgets {


class BaseTab : public QWidget{
    Q_OBJECT
    public: BaseTab(QWidget *parent = nullptr);
    public: ~BaseTab();
    public: void setPage(QWidget *page);

    
    public: BaseElements::ControlList *controlList = nullptr;
    public: QHBoxLayout *m_controLayout = nullptr;
    public: QWidget *m_centerWidget = nullptr;
    public: QVBoxLayout *m_centerLayout = nullptr;
    public: QWidget *m_this_widget = nullptr;

};




} // namespace BaseWidgets


#endif // BASETAB_H