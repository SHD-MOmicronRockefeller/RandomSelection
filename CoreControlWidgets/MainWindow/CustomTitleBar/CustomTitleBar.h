#ifndef CUSTOMTITLEBAR_H
#define CUSTOMTITLEBAR_H

#include "QtPrecompiled.h"


#include "ClassSpace.h"
namespace CoreControlWidgets {

namespace MainWindow {

class CustomTitleBar : public QFrame
{
    Q_OBJECT
    public: explicit CustomTitleBar(QWidget *parent = nullptr);
    public: ~CustomTitleBar();
    //public: void setTitleText(const QString &text);

    // 窗口相关
    protected: QPushButton *thisTabBtn = nullptr; // 最小化按钮

    // 图标设置颜色
    protected: QIcon setIconColor(QIcon icon, QColor color); // 设置图标颜色

    // 窗口函数
    protected: void onMinimizeClicked(); // 最小化按钮点击槽函数
    protected: void onSettingClicked(); // 设置按钮点击槽函数
    protected: void onMaximizeClicked(); // 最大化按钮点击槽函数
    protected: void onCloseClicked(); // 关闭按钮点击槽函数

    // 页面函数
    protected: void closeThisTab(); // 关闭当前标签页
public: void onMidBtnClicked(QString objectName = "", bool canRun = true); // 中间按钮点击槽函数
    protected: void onMidBtnClicked_randomSelect();// 随机选择按钮点击槽函数
    protected: void onMidBtnClicked_fileEdit(); // 文件编辑按钮点击槽函数
    protected: void onMidBtnClicked_setting(); // 设置按钮点击槽函数
    protected: void onMidBtnClicked_about(); // 关于程序按钮点击槽函数

    //自定义函数
    protected: void setMainWindowMaximized(); // 设置主窗口
    protected: void setMainWindowminimized(); // 设置主窗口最小化;
    
    // 重写父类函数
    protected: void mousePressEvent(QMouseEvent *event) override; // 鼠标按下事件
    protected: void mouseMoveEvent(QMouseEvent *event) override; // 鼠标移动事件
    protected: void mouseReleaseEvent(QMouseEvent *event) override; // 鼠标释放事件
    protected: void paintEvent(QPaintEvent *event) override; // 绘制事件
    protected: void mouseDoubleClickEvent(QMouseEvent *event) override; // 鼠标双击事件

    // 初始化
    protected: void initLayout(); // 初始化布局
    protected: void initWidgets(); // 初始化控件
    protected: void initStyle(); // 初始化样式

    // 布局成员
    protected: QHBoxLayout *m_mainLayout = nullptr; // 中心布局
    protected: QHBoxLayout *m_leftLayout = nullptr; // 左侧布局
    protected: QHBoxLayout *m_midLayout = nullptr; // 中间布局
    protected: QHBoxLayout *m_rightLayout = nullptr; // 右侧布局

    // 控件成员
    protected: QPushButton *m_iconBtn = nullptr; // 图标标签
    protected: QLabel *m_titleLabel = nullptr; // 标题标签
    protected: QMap<QString, QPushButton *> m_midBtns; // 中间按钮列表
    protected: QPushButton *m_btnMin = nullptr; // 最小化按钮
    protected: QPushButton *m_btnSetting = nullptr; // 设置按钮
    protected: QPushButton *m_btnMax = nullptr; // 最大化按钮
    protected: QPushButton *m_btnClose = nullptr; // 关闭按钮

    // 拖动相关
    protected: bool m_isDragging = false; // 是否正在拖动
    protected: bool m_isMaximized = false; // 是否最大化
    protected: QSize m_windowSize; // 窗口大小
    protected: QPoint m_dragStartPos; // 鼠标按下时的位置
    protected: QPoint m_dragStartGlobalPos; // 鼠标释放时的位置
};

} // namespace MainWindow

} // namespace CoreControlWidgets

#endif // CUSTOMTITLEBAR_H