#include "Initialization.h"

#include "VariablesStore/globalVariables.h"

#include "CoreCalculation/TitleFunc/titleFunc.h"

#include "CoreCalculation/Application/rs_version.h"

namespace Initialization {

void initialize_values()
{
    RS_Version::getInstance()->setVersion() << "3.0.0"; // 版本号

    GlobalVariables* gv = GlobalVariables::getInstance();
    
    // 分步初始化UI成员（确保在QApplication就绪后）

    gv->window_size[0] = gv->main_window_width;
    gv->window_size[1] = gv->main_window_height;

    // 第一梯队
    if (!gv->custom_title_bar)      gv->custom_title_bar    = new CoreControlWidgets::MainWindow::CustomTitleBar();                         // 标题栏
    if (!gv->status_bar)            gv->status_bar          = new CoreControlWidgets::MainWindow::StatusBar();                              // 状态栏
    if (!gv->select_tab)            gv->select_tab          = new CoreControlWidgets::SelectTab();                                          // 选择页面 
    if (!gv->file_tab)              gv->file_tab            = new CoreControlWidgets::FileTab();                                            // 文件页面
    if (!gv->setting_tab)           gv->setting_tab         = new CoreControlWidgets::SettingTab();                                         // 设置页面
    if (!gv->about_tab)             gv->about_tab           = new CoreControlWidgets::AboutTab();                                           // 关于页面

    // 第二梯队
    if (!gv->main_window_shell)     gv->main_window_shell   = new CoreControlWidgets::MainWindowShell();                                    // 主窗口
    if (!gv->min_custom_title_bar)  gv->min_custom_title_bar= new CoreControlWidgets::MainWindow::CustomTitleBar();                         // 迷你标题栏
    if (!gv->min_window_widget)     gv->min_window_widget   = new CoreControlWidgets::MinWindow::MinWindowShell();                          // 迷你窗口

    // 第三梯队
    if (!gv->window_stack) {
        gv->window_stack = new QStackedWidget();

        gv->window_stack->addWidget(gv->main_window_widget);   // 索引0：主窗口
        gv->window_stack->addWidget(gv->min_window_widget);    // 索引1：迷你窗口
    }
    gv->main_window_shell->setCentralWidget(gv->window_stack);
}

void initialize_settings()
{
    GlobalVariables* gv = GlobalVariables::getInstance();
    // 默认显示主窗口
    gv->window_stack->setCurrentIndex(0);
    gv->main_window_shell->show();


    gv->main_window_shell->resize(gv->main_window_width, gv->main_window_height);
    gv->main_window_shell->show();

    // 设置默认选择页面
    gv->main_window_shell->m_centralLayout->addWidget(gv->select_tab);
    gv->this_tab_widget = gv->select_tab;

    // 添加状态栏
    gv->main_window_shell->m_titleLayout->addWidget(gv->status_bar);
    gv->status_bar->addLeftWidget(new QLabel("__状态栏左侧__"));
    gv->status_bar->addRightWidget(new QLabel("__状态栏右侧__"));

    // 设置非迷你窗口
    MY_FUNC::setMainWindow();

    // 设置迷你窗口图标
    gv->min_custom_title_bar->m_btnSetting->setIcon(QIcon(":/ICONS/icons/TitleIcons/_MinWindowButtonM.png"));

    // 初始化消息管理器
    MessageTipManager::getInstance().init(gv->main_window_shell);


    // 后续 ///////////////////////////

    gv->main_window_shell->m_customTitleBar->onMidBtnClicked_clicked(0); // 切换到默认选择页面

    // 设置原始尺寸
    gv->main_window_shell->resize(gv->main_window_width, gv->main_window_height);

    // 移动到屏幕中心
    QScreen* screen = gv->main_window_shell->screen();
    if (!screen) screen = QGuiApplication::primaryScreen();
    QRect screenRect = screen->availableGeometry();

    int screenCenterX = screenRect.x() + screenRect.width() / 2;
    int screenCenterY = screenRect.y() + screenRect.height() / 2;

    int windowWidth = gv->main_window_shell->width();
    int windowHeight = gv->main_window_shell->height();
    int windowX = screenCenterX - windowWidth / 2;
    int windowY = screenCenterY - windowHeight / 2;

    gv->main_window_shell->move(windowX, windowY);

}

void after_event_loop_started()
{
    QTimer::singleShot(0, []() {
        MessageTipManager::getInstance().addMessage(QString("欢迎使用 Random Selection [别急，我马上走]"), false)
            ->setBackgroundColor(MorandiPink)
            ->setTextColor(FontColor1);
    });
}

} // namespace Initialization