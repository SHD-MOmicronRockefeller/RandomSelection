#ifndef SELECTTAB_H
#define SELECTTAB_H

#include "QtPrecompiled.h"

namespace BaseWidgets {


class ControlList : public QWidget{
    Q_OBJECT
    public: ControlList(QWidget *parent = nullptr);
    public: ~ControlList();

    public: QVBoxLayout* mainLayout = nullptr;

    private: void initLayout(); // 初始化布局
    private: void initWidgets(); // 初始化控件
    private: void initStyle(); // 初始化样式
    
};




} // namespace BaseWidgets


#endif // SELECTTAB_H