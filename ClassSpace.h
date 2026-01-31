#ifndef CLASSSPACE_H
#define CLASSSPACE_H

namespace ApplicationClass { 
    class ApplicationShell; 
}
namespace BaseWidgets {
    class AspectRatioWidget;
    class BaseTab;
    namespace BaseElements {
        class ControlList;
    }
} // namespace BaseWidgets


namespace CoreControlWidgets{
    class AboutTab;
    class FileTab;
    class SettingTab;


    class SelectTab;
    namespace SelectTab_NS
    {
        class SelectFile_Page;

        class MidWidget;
        class Select_Page;
    }


    
    class MainWindowShell;
    namespace MainWindow {
        class StatusBar;
        class CustomTitleBar;
    }
} // namespace CoreControlWidgets




#endif // CLASSSPACE_H