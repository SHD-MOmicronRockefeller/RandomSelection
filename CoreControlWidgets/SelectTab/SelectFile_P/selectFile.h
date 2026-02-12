#ifndef SELECT_FILE_H
#define SELECT_FILE_H

#include "QtPrecompiled.h"


namespace CoreControlWidgets
{

namespace SelectTab_NS
{

class SelectFile_Page : public QWidget
{
    Q_OBJECT
    public: SelectFile_Page(QWidget *parent = 0);
    public: ~SelectFile_Page();

    public: QVBoxLayout *m_centerLayout = nullptr;


    protected: QWidget *m_topWidget = nullptr;    // 上层固定区域

    protected: QWidget *m_midWidget = nullptr;     // 中层可变区域

    protected: QWidget *m_downWidget = nullptr; // 下层固定区域


    // mid
    public: QGroupBox *m_thisFileGroupBox = nullptr;
    public: QGroupBox *m_tempFileGroupBox = nullptr;
    public: QGroupBox *m_thatFileGroupBox = nullptr;



};



} // namespace SelectTab_NS




} // namespace CoreControlWidgets




#endif // SELECT_FILE_H