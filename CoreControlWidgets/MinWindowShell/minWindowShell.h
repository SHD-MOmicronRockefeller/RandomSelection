#ifndef MINWINDOWSHELL_H
#define MINWINDOWSHELL_H

#include "QtPrecompiled.h"

#include "ClassSpace.h"

namespace CoreControlWidgets
{

namespace MinWindow
{

class MinWindowShell : public QWidget
{
    Q_OBJECT
    public: MinWindowShell(QWidget *parent = 0);
    
    public: QVBoxLayout* m_centralLayout = nullptr;
    protected: BaseWidgets::AspectRatioWidget* m_aspectRatioWidget = nullptr; // 宽高比控件
    protected: CoreControlWidgets::SelectTab_NS::MidWidget* m_midWidget = nullptr; // 中间控件

    public: MainWindow::CustomTitleBar *m_customTitleBar = nullptr; // 自定义标题栏
};


} // namespace MinWindow

} // namespace CoreControlWidgets



#endif // MINWINDOWSHELL_H