#ifndef IMPORTFILE_H
#define IMPORTFILE_H
#include "QtPrecompiled.h"

#include "ClassSpace.h"


namespace CoreControlWidgets
{

namespace SelectTab_NS
{

class ImportFile_Page : public QWidget
{
    Q_OBJECT
    public: ImportFile_Page(QWidget *parent = 0);
    public: ~ImportFile_Page() = default;

    public: QVBoxLayout *m_centerLayout = nullptr;

    public: QHBoxLayout *m_topWidget = nullptr;

    public: static void ImportFileToSelect(QString filePath);
    public: static void ImportFileToList(QString filePaths);

    public: IPT_Base *IPT_FileToSelect = nullptr;
    public: IPT_Base *IPT_FileToList = nullptr;
    public: IPT_Base *IPT_BouthDouble = nullptr;
};



} // namespace SelectTab_NS




} // namespace CoreControlWidgets




#endif // IMPORTFILE_H