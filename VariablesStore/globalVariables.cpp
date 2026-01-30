#include "globalVariables.h"

GlobalVariables* GlobalVariables::m_instance = nullptr; // 初始化单例指针
QMutex GlobalVariables::m_mutex;                       // 初始化互斥锁


GlobalVariables *GlobalVariables::getInstance(){
    QMutexLocker locker = QMutexLocker(&GlobalVariables::m_mutex);
    if (GlobalVariables::m_instance == nullptr) {
        GlobalVariables::m_instance = new GlobalVariables();
    }
    return GlobalVariables::m_instance;
}

void GlobalVariables::deleteInstance()
{
    QMutexLocker locker = QMutexLocker(&GlobalVariables::m_mutex);
    if (GlobalVariables::m_instance != nullptr) {
        delete GlobalVariables::m_instance;
        GlobalVariables::m_instance = nullptr;
    }
}
