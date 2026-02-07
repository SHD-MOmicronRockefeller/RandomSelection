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
    public: SelectTab_NS::ImportFile_Page *importFile_page = nullptr;

    public: SelectTab_NS::Select_Page *select_page = nullptr;
    public: SelectTab_NS::SelectFile_Page *selectFile_page = nullptr;
    public: SelectTab_NS::ListSet_Page *listSet_page = nullptr;
    public: SelectTab_NS::BasicSet_Page *basicSet_page = nullptr;

    public: QWidget *m_oldPage = nullptr; // 处理拖拽事件时，记录上一个页面
    protected: void dragEnterEvent(QDragEnterEvent *event) override; // 拖拽事件：文件拖入
    protected: void dragLeaveEvent (QDragLeaveEvent *event) override; // 拖拽事件：文件离开

    public: bool m_isInDrag = false;
    protected: void dropEvent(QDropEvent *event) override; // 拖拽事件：文件释放
};





} // namespace CoreControlWidgets


#endif // SELECTTAB_H