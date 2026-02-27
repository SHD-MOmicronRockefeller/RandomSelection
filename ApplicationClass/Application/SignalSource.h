#include "QtPrecompiled.h"

class SignalSource : public QObject 
{
    Q_OBJECT
    // 全局访问接口声明
    public: static SignalSource* getInstance();
    public: static void deleteInstance();

    private: static SignalSource* m_instance;


    // 私有构造、析构、拷贝、赋值
    private: SignalSource() = default;
    private: ~SignalSource() = default;
    private: SignalSource(const SignalSource&) = delete;
    private: SignalSource& operator=(const SignalSource&) = delete;

    signals: void WindowTopmostToggled();
    signals: void SelectTab_ListSet_ChangeOption(unsigned int index, bool isSelected);

};