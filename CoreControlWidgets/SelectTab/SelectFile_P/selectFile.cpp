#include "selectFile.h"

CoreControlWidgets::SelectTab_NS::SelectFile_Page::SelectFile_Page(QWidget *parent): QWidget(parent)
{
    this->m_centerLayout = new QVBoxLayout();
    this->m_centerLayout->setContentsMargins(0, 0, 0, 0);
    this->m_centerLayout->setSpacing(0);
    this->m_centerLayout->setAlignment(Qt::AlignTop);
    this->setLayout(this->m_centerLayout);

    // ========== 2. 构建上层固定区域 ==========
    m_topWidget = new QWidget();
    m_topWidget->setObjectName("SelectFileTab_TopWidget");
    m_topWidget->setStyleSheet("QWidget#SelectFileTab_TopWidget{background: #FFCC00; min-height: 50px;}");
    QHBoxLayout *topLayout = new QHBoxLayout(m_topWidget);
    topLayout->setContentsMargins(10, 0, 10, 0);
    topLayout->addWidget(new QLabel("上层固定区域"));
    topLayout->addStretch();
    topLayout->addWidget(new QPushButton("上层按钮"));


    // ========== 3. 构建中层可变区域 ==========
    m_midWidget = new QWidget();
    m_midWidget->setObjectName("SelectFileTab_MidWidget");
    m_midWidget->setStyleSheet("QWidget#SelectFileTab_MidWidget{background: #FF9933; min-height: 50px;}");
    QHBoxLayout *midLayout = new QHBoxLayout(m_midWidget);
    midLayout->setContentsMargins(10, 10, 10, 10);
    midLayout->setSpacing(10);
    // 左侧文件列表
    m_thisFileGroupBox = new QGroupBox("当前文件");
    QVBoxLayout *thisFileLayout = new QVBoxLayout(m_thisFileGroupBox);
    thisFileLayout->setContentsMargins(0, 0, 0, 0);

    // 中间区域
    QVBoxLayout *thisFileBoxLayout = new QVBoxLayout();
    thisFileBoxLayout->setContentsMargins(0, 0, 0, 0);
    thisFileBoxLayout->setSpacing(0);
    
    m_tempFileGroupBox = new QGroupBox("临时文件");
    QVBoxLayout *tempFileLayout = new QVBoxLayout(m_tempFileGroupBox);
    tempFileLayout->setContentsMargins(0, 0, 0, 0);
    thisFileBoxLayout->addWidget(m_tempFileGroupBox);

    QPushButton *addFileButton = new QPushButton("添加文件");
    thisFileBoxLayout->addWidget(addFileButton);
    
    
    
    // 右侧文件列表
    QVBoxLayout *thatFileBoxLayout = new QVBoxLayout();
    thatFileBoxLayout->setContentsMargins(0, 0, 0, 0);
    thatFileBoxLayout->setSpacing(0);   
    
    m_thatFileGroupBox = new QGroupBox("其它文件");
    QVBoxLayout *thatFileLayout = new QVBoxLayout(m_thatFileGroupBox);
    thatFileLayout->setContentsMargins(0, 0, 0, 0);
    thatFileBoxLayout->addWidget(m_thatFileGroupBox);

    QPushButton *selectDirButton = new QPushButton("选择文件夹");
    thatFileBoxLayout->addWidget(selectDirButton);


    midLayout->addWidget(m_thisFileGroupBox);
    midLayout->addLayout(thisFileBoxLayout);
    midLayout->addLayout(thatFileBoxLayout);

    // ========== 4. 构建下层固定区域 ==========
    m_downWidget = new QWidget();
    m_downWidget->setObjectName("SelectFileTab_DownWidget");
    m_downWidget->setStyleSheet("QWidget#SelectFileTab_DownWidget{background: #FF6699; min-height: 50px;}");
    QHBoxLayout *bottomLayout = new QHBoxLayout(m_downWidget);
    bottomLayout->setContentsMargins(10, 0, 10, 0);
    bottomLayout->addWidget(new QLabel("下层固定区域"));
    bottomLayout->addStretch();
    bottomLayout->addWidget(new QPushButton("下层按钮"));

    // ========== 5. 把上/中/下添加到BaseTab的中心布局 ==========
    this->m_centerLayout->setContentsMargins(0, 0, 0, 0);
    this->m_centerLayout->setSpacing(0);
    this->m_centerLayout->addWidget(m_topWidget);          // 上层（固定）
    this->m_centerLayout->addWidget(m_midWidget, 1); // 中间（占剩余空间，比例固定）
    this->m_centerLayout->addWidget(m_downWidget);       // 下层（固定）
}

CoreControlWidgets::SelectTab_NS::SelectFile_Page::~SelectFile_Page()
{
}
