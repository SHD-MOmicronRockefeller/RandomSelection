#ifndef BASETAB_H
#define BASETAB_H

#include "QtPrecompiled.h"

#include "BaseWidgets/BaseTab/ControlList.h"

namespace BaseWidgets {


class BaseTab : public QWidget{
    Q_OBJECT
    public: BaseTab(QWidget *parent = nullptr);
    public: ~BaseTab();
    public: BaseElements::ControlList *controlList = nullptr;
    public: QHBoxLayout *m_controLayout = nullptr;
    public: QWidget *m_centerWidget = nullptr;
    public: QVBoxLayout *m_centerLayout = nullptr;
};




} // namespace BaseWidgets


#endif // BASETAB_H