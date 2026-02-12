#pragma once
#include <QObject>
#include <QMutex>
#include <QThread>
#include <QQueue>
#include <functional>
#include <QVariant>
#include <QDebug>
#include <limits>
#include <QAtomicInteger>
#include <QMetaObject>

#define MainThreadReady() Console::getInstance()->emit mainThreadReady()

#define Task const unsigned long long
#define newTask Console::getInstance()->buyTaskId()

#define PushTask(task) Console::getInstance()->addTask([=]() mutable {\
        task\
})

#define SendResult(taskId, result) Console::getInstance()->sendResult(taskId, QVariant::fromValue(result))

#define GetResult(dataType) _result.value<dataType>()

#define ReturnTask(taskId, handle_Func) QObject::connect(Console::getInstance(), &Console::taskResultReturned, [=](unsigned long long _taskId, QVariant _result) {\
    if (_taskId == taskId) { \
        handle_Func();\
    } \
})


class Console;

class ResultSender
{

    private: Console* m_console = nullptr;          // 关联的Console实例
    private: unsigned long long m_taskId = 0;       // 任务ID
    private: QVariant m_result;                     // 任务结果

            // 构造函数：绑定Console和任务ID
    public: ResultSender(Console* console, unsigned long long taskId, QVariant result = QVariant());

            // 重载<<运算符，支持非数组类型
    public: template <typename T>
            typename std::enable_if<!std::is_array<T>::value, ResultSender&>::type
            operator<<(const T& value);

            // 数组特化：处理字符串字面量
    public: template <size_t N>
            ResultSender& operator<<(const char (&value)[N]);
    
    public: ResultSender& operator<<(const char* value);
    public: ~ResultSender();
};

class Console : public QObject
{
    Q_OBJECT

    private: static inline Console* m_instance = nullptr;  // 静态单例实例
    private: static inline QMutex m_mutex;                 // 单例锁
    private: QThread* m_workThread = nullptr;              // 工作线程指针
    private: QMutex m_queueMutex;                          // 任务队列线程安全锁
    private: static inline QAtomicInteger<unsigned long long> m_nextTaskId = 1; // 下一个任务ID
    private: QQueue<std::function<void()>> m_taskQueue;    // 任务队列
    private: bool m_isMainThreadReady = false;             // 主线程准备就绪标志

    private: Console(QObject *parent = nullptr);
    private: ~Console() override;
    private: Console(const Console&) = delete;
    private: Console& operator=(const Console&) = delete;

    signals: void mainThreadReady();                       // 主线程准备就绪信号（由外部手动发送）
    signals: void taskResultReturned(unsigned long long taskId, QVariant result); // 任务结果信号

    private slots: void onMainThreadReady();               // 主线程就绪槽
    private slots: void onProcessTasks();                  // 处理任务队列

    public: static Console* getInstance();
    public: static void deleteInstance();
    public: unsigned long long buyTaskId();
    public: Console* addTask(std::function<void()> task);
    public: Console& operator<<(std::function<void()> task);
    public: ResultSender sendResult(unsigned long long taskId, QVariant result = QVariant());
};

// ===================== ResultSender 实现 =====================
inline ResultSender::ResultSender(Console* console, unsigned long long taskId, QVariant result)
    : m_console(console), m_taskId(taskId), m_result(result) {}

template <typename T>
typename std::enable_if<!std::is_array<T>::value, ResultSender&>::type
ResultSender::operator<<(const T& value) {
    m_result = QVariant::fromValue(value);
    return *this;
}

// 特化:处理字符串字面量
template <size_t N>
inline ResultSender& ResultSender::operator<<(const char (&value)[N]) {
    m_result = QVariant(QString::fromUtf8(value, N));
    return *this;
}

// 特化:处理const char*指针
inline ResultSender& ResultSender::operator<<(const char* value) {
    if (value) {
        m_result = QVariant(QString::fromUtf8(value));
    }
    return *this;
}

inline ResultSender::~ResultSender() {
    if (m_console && m_result.isValid() && m_taskId > 0) {
        QMetaObject::invokeMethod(m_console, [m_console = m_console, taskId = m_taskId, result = m_result]() {
            emit m_console->taskResultReturned(taskId, result);
        }, Qt::QueuedConnection);
    }
}


// ===================== Console 实现 =====================
inline Console* Console::getInstance() {
    if (m_instance == nullptr) {
        QMutexLocker locker(&m_mutex);
        if (m_instance == nullptr) {
            m_instance = new Console();
        }
    }
    return m_instance;
}

inline void Console::deleteInstance() {
    QMutexLocker locker(&m_mutex);
    if (m_instance != nullptr) {
        delete m_instance;
        m_instance = nullptr;
    }
}

inline Console::Console(QObject *parent) : QObject(parent) {
    // 创建工作线程，避免成员变量析构顺序问题
    m_workThread = new QThread(this);
    this->moveToThread(m_workThread);
    m_workThread->start();

    // 保留信号连接：仅接收自身的mainThreadReady信号
    connect(this, &Console::mainThreadReady, this, &Console::onMainThreadReady, Qt::QueuedConnection);
}

inline Console::~Console() {
    if (m_workThread && m_workThread->isRunning()) {
        m_workThread->quit();
        m_workThread->wait(8888);
    }
}

inline void Console::onMainThreadReady() {
    m_isMainThreadReady = true;

    // 主线程就绪后，检查任务队列并触发处理
    QMutexLocker locker(&m_queueMutex);
    if (!m_taskQueue.isEmpty()) {
        QMetaObject::invokeMethod(this, "onProcessTasks", Qt::QueuedConnection);
    }
}

inline void Console::onProcessTasks() {
    // 每次只处理一个任务，避免长时间占用锁
    std::function<void()> task; {
        QMutexLocker locker(&m_queueMutex);
        if (!m_taskQueue.isEmpty()) {
            task = m_taskQueue.dequeue();
        }
    }

    // 解锁后执行任务，避免锁持有时间过长
    if (task) {
        try {
            task();
            QThread::msleep(0);
        } catch (...) {
            // 异常捕获，发送错误结果
            ResultSender(this, std::numeric_limits<unsigned long long>::max()) << "计算任务执行出错";
        }
    }

    // 如果队列还有任务且主线程已就绪，继续触发处理
    QMutexLocker locker(&m_queueMutex);
    if (m_isMainThreadReady && !m_taskQueue.isEmpty()) {
        QMetaObject::invokeMethod(this, "onProcessTasks", Qt::QueuedConnection);
    }
}

inline unsigned long long Console::buyTaskId() {
    return m_nextTaskId.fetchAndAddRelaxed(1);
}

inline Console *Console::addTask(std::function<void()> task) {
    if (!task) { return nullptr; }

    // 主线程未就绪时，仅添加任务不触发执行
    {
        QMutexLocker locker(&m_queueMutex);
        m_taskQueue.enqueue(task);
    }

    if (m_isMainThreadReady) {
        // 主线程就绪时，触发任务处理
        QMetaObject::invokeMethod(this, "onProcessTasks", Qt::QueuedConnection);
    }

    return this;
}

inline Console& Console::operator<<(std::function<void()> task) {
    this->addTask(task);
    return *this;
}

inline ResultSender Console::sendResult(unsigned long long taskId, QVariant result) {
    return ResultSender(this, taskId, result);
}