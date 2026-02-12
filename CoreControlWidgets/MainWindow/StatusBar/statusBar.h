#ifndef STATUSBAR_H
#define STATUSBAR_H


#include "QtPrecompiled.h"

#include "ClassSpace.h"
// StatusBar.h
namespace CoreControlWidgets {

namespace MainWindow {

class StatusBar : public QWidget {
    Q_OBJECT
    public: StatusBar(QWidget* parent = nullptr);
    public: ~StatusBar();

    // 左侧区域
    private: QWidget* m_leftArea;
    protected: QHBoxLayout* leftLayout;
    protected: QMap<QWidget*, QWidget*> leftWidgets;
    public: void addLeftWidget(QWidget* widget);
    public: void removeLeftWidget(QWidget* widget, bool deleteWidget = true);
    
    // 右侧区域
    private: QWidget* m_rightArea;
    protected: QHBoxLayout* rightLayout;
    protected: QMap<QWidget*, QWidget*> rightWidgets;
    public: void addRightWidget(QWidget* widget);
    public: void removeRightWidget(QWidget* widget, bool deleteWidget = true);
    
    protected: void resizeEvent(QResizeEvent *event) override;
};

}

}

#endif // STATUSBAR_H