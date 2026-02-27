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

    QStackedWidget *m_stackedWidget = nullptr;

    // 文件导入
    public: void changeToFilePage();

    public: QVBoxLayout *m_fileLayout = nullptr;
    public: QHBoxLayout *m_fileTopWidget = nullptr;

    public: static void ImportFileToSelect(QString filePath);
    public: static void ImportFileToList(QString filePath);

    public: IPT_Base *IPT_FileToSelect = nullptr;
    public: IPT_Base *IPT_FileToList = nullptr;
    public: IPT_Base *IPT_FileBouthDouble = nullptr;

    // 文件夹导入
    public: void changeToDirtPage();

    public: QVBoxLayout* m_dirt_layout = nullptr;
    public: IPT_Base *IPT_DirtToList = nullptr;

    public: static void ImportDirtToList(QString filePath);
};



} // namespace SelectTab_NS




} // namespace CoreControlWidgets




#endif // IMPORTFILE_H