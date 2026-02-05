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
    class AutoFitLabel;
    class AutoFitButton;
} // namespace BaseWidgets

class MessageTipWidget;
class MessageTipManager;

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
        
        class ListSet_Page;
        class BasicSet_Page;

        class Hello_Page;
    }

    class MainWindowShell;
    namespace MainWindow {
        class StatusBar;
        class CustomTitleBar;
    }

    namespace MinWindow{
        class MinWindowShell;
    } // namespace MinWindow

    
    
} // namespace CoreControlWidgets

namespace ModWidgets {
    class ToggleTopmost;    
} // namespace ModWidgets





#endif // CLASSSPACE_H