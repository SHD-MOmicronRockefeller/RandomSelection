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

    public: QHBoxLayout *m_centerLayout = nullptr;

    public: QGroupBox *m_thisFileGroupBox = nullptr;
    public: QGroupBox *m_tempFileGroupBox = nullptr;
    public: QGroupBox *m_thatFileGroupBox = nullptr;

};



} // namespace SelectTab_NS




} // namespace CoreControlWidgets




#endif // SELECT_FILE_H