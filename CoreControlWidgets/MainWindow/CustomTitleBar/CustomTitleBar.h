#ifndef CUSTOMTITLEBAR_H
#define CUSTOMTITLEBAR_H

#include "QtPrecompiled.h"

#include "CoreControlWidgets/MainWindow/mainWindow.h"
namespace CoreControlWidgets {

namespace MainWindow {

class CustomTitleBar : public QFrame
{
    Q_OBJECT
public:
    public: explicit CustomTitleBar(QWidget *parent = nullptr);
    //public: void setTitleText(const QString &text);

    // 窗口函数
    public: void onMinimizeClicked(); // 最小化按钮点击槽函数
    public: void onSettingClicked(); // 设置按钮点击槽函数
    public: void onMaximizeClicked(); // 最大化按钮点击槽函数
    public: void onCloseClicked(); // 关闭按钮点击槽函数

    // 页面函数
    public: void onMidBtnClicked(int index); // 中间按钮点击槽函数
    public: void onMidBtnClicked_randomSelect();// 随机选择按钮点击槽函数
    public: void onMidBtnClicked_fileEdit(); // 文件编辑按钮点击槽函数
    public: void onMidBtnClicked_baibao(); // 百宝盒子按钮点击槽函数
    public: void onMidBtnClicked_about(); // 关于程序按钮点击槽函数

    //自定义函数
    public: void setMainWindowNormal(); // 设置主窗口
    
    // 重写父类函数
    protected: void mousePressEvent(QMouseEvent *event) override; // 鼠标按下事件
    protected: void mouseMoveEvent(QMouseEvent *event) override; // 鼠标移动事件
    protected: void mouseReleaseEvent(QMouseEvent *event) override; // 鼠标释放事件
    protected: void paintEvent(QPaintEvent *event) override; // 绘制事件
    protected: void mouseDoubleClickEvent(QMouseEvent *event) override; // 鼠标双击事件

    // 私有方法
    private: void initLayout(); // 初始化布局
    private: void initWidgets(); // 初始化控件
    private: void initStyle(); // 初始化样式

    // 布局成员
    private: QHBoxLayout *m_mainLayout = nullptr; // 中心布局
    private: QHBoxLayout *m_leftLayout = nullptr; // 左侧布局
    private: QHBoxLayout *m_midLayout = nullptr; // 中间布局
    private: QHBoxLayout *m_rightLayout = nullptr; // 右侧布局

    // 控件成员
    private: QLabel *m_iconLabel = nullptr; // 图标标签
    private: QLabel *m_titleLabel = nullptr; // 标题标签
    private: QMap<QString, QPushButton *> m_midBtns; // 中间按钮列表
    private: QPushButton *m_btnMin = nullptr; // 最小化按钮
    private: QPushButton *m_btnSetting = nullptr; // 设置按钮
    private: QPushButton *m_btnMax = nullptr; // 最大化按钮
    private: QPushButton *m_btnClose = nullptr; // 关闭按钮

    // 拖动相关
    private: bool m_isDragging = false; // 是否正在拖动
    private: QPoint m_dragStartPos; // 鼠标按下时的位置
};

} // namespace MainWindow

} // namespace CoreControlWidgets

#endif // CUSTOMTITLEBAR_H