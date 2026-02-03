#ifndef QTPRECOMPILED_H
#define QTPRECOMPILED_H

#include <QAction>
#include <QActionGroup>
#include <QApplication>
#include <QBitmap>
#include <QBoxLayout>
#include <QBrush>
#include <QButtonGroup>
#include <QCalendarWidget>
#include <QCheckBox>
#include <QClipboard>
#include <QColor>
#include <QColorDialog>
#include <QComboBox>
#include <QCompleter>
#include <QCoreApplication>
#include <QCursor>
#include <QDate>
#include <QDateEdit>
#include <QDateTime>
#include <QDateTimeEdit>
#include <QDesktopServices>
#include <QDialog>
#include <QDialogButtonBox>
#include <QDial>
#include <QDir>
#include <QDockWidget>
#include <QDoubleSpinBox>
#include <QDrag>
#include <QDropEvent>
#include <QElapsedTimer>
#include <QErrorMessage>
#include <QFile>
#include <QFileDialog>
#include <QFileSystemModel>
#include <QFont>
#include <QFontComboBox>
#include <QFontDialog>
#include <QFormLayout>
#include <QFrame>
#include <QGesture>
#include <QGestureEvent>
#include <QGraphicsDropShadowEffect>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGridLayout>
#include <QGroupBox>
#include <QHeaderView>
#include <QHBoxLayout>
#include <QIcon>
#include <QImage>
#include <QInputDialog>
#include <QKeyEvent>
#include <QLabel>
#include <QLineEdit>
#include <QList>
#include <QListWidget>
#include <QListWidgetItem>
#include <QMainWindow>
#include <QMap>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QMetaObject>
#include <QMouseEvent>
#include <QMovie>
#include <QMutex>
#include <QObject>
#include <QPaintEvent>
#include <QPalette>
#include <QPen>
#include <QPicture>
#include <QPixmap>
#include <QPoint>
#include <QPolygon>
#include <QPolygonF>
#include <QProgressBar>
#include <QProgressDialog>
#include <QPushButton>
#include <QRadioButton>
#include <QRawFont>
#include <QRegion>
#include <QScrollArea>
#include <QScrollBar>
#include <QScreen>
#include <QShortcut>
#include <QSize>
#include <QSizePolicy>
#include <QSlider>
#include <QSpacerItem>
#include <QSplitter>
#include <QSpinBox>
#include <QStack>
#include <QStackedWidget>
#include <QStatusBar>
#include <QString>
#include <QStringList>
#include <QStyle>
#include <QStyleFactory>
#include <QStyleOption>
#include <QTabBar>
#include <QTabWidget>
#include <QTableView>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QTextBrowser>
#include <QTextEdit>
#include <QTextStream>
#include <QThread>
#include <QTime>
#include <QTimeEdit>
#include <QTimer>
#include <QToolBar>
#include <QToolButton>
#include <QTreeView>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QUrl>
#include <QVBoxLayout>
#include <QVariant>
#include <QVector>
#include <QWidget>
#include <QWheelEvent>
#include <QWindow>

// 莫兰迪色系（低饱和，柔和高级）
#define MorandiPink QColor(245, 183, 177, 240)    // rgba(245, 183, 177, 0.94) 柔粉
#define MorandiBlue QColor(143, 188, 187, 235)    // rgba(143, 188, 187, 0.92) 雾蓝
#define MorandiGreen QColor(165, 180, 129, 220)   // rgba(165, 180, 129, 0.86) 鼠尾草绿
#define MorandiPurple QColor(193, 154, 170, 210)  // rgba(193, 154, 170, 0.82) 灰紫
#define MorandiYellow QColor(224, 176, 105, 200)  // rgba(224, 176, 105, 0.78) 奶油黄

// 轻奢冷调（科技感/商务风）
#define LuxuryCyan QColor(80, 175, 250, 230)      // rgba(80, 175, 250, 0.90) 清透青蓝
#define LuxuryIndigo QColor(102, 112, 188, 225)   // rgba(102, 112, 188, 0.88) 靛蓝灰
#define LuxurySlate QColor(76, 86, 106, 245)      // rgba(76, 86, 106, 0.96) 高级石板灰
#define LuxuryTeal QColor(45, 152, 142, 215)      // rgba(45, 152, 142, 0.84) 墨绿青

// 暖调高级色（温馨/质感）
#define WarmApricot QColor(250, 214, 195, 228)    // rgba(250, 214, 195, 0.89) 杏仁暖橙
#define WarmCream QColor(252, 246, 238, 250)      // rgba(252, 246, 238, 0.98) 奶油白（低透明度时做背景）
#define WarmTerracotta QColor(204, 119, 70, 205)  // rgba(204, 119, 70, 0.80) 陶土棕

// 低饱和中性色（通用百搭）
#define NeutralGray1 QColor(245, 245, 247, 255)   // rgba(245, 245, 247, 1) 超浅灰（背景）
#define NeutralGray2 QColor(150, 153, 160, 240)   // rgba(150, 153, 160, 0.94) 中灰（边框/分割线）
#define NeutralGray3 QColor(82, 86, 90, 235)      // rgba(82, 86, 90, 0.92) 深灰（文本）

// 字体颜色
#define FontColor1 QColor(26, 29, 53, 255)        // rgba(26, 29, 53, 1) 靛蓝黑
#define FontColor2 QColor(34, 36, 10, 255)        // rgb(34, 36, 10) 靛蓝灰


#endif // QTPRECOMPILED_H