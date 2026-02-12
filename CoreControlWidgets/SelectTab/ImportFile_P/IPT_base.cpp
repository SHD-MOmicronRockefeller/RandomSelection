#include "IPT_base.h"

#include "importFiles.h"

#include "BaseWidgets/BaseCoreWidget/TinyWidget/AutoFitLabel.h"

#include "VariablesStore/globalVariables.h"

CoreControlWidgets::SelectTab_NS::IPT_Base::IPT_Base(QString _ObjectName, std::function<void(QString)> _func, QWidget *parent): QWidget(parent)
{
    this->setAutoFillBackground(true);
    this->setAttribute(Qt::WA_StyledBackground, true);

    this->setObjectName(_ObjectName);
    this->importFunction = std::move(_func);

    //开启拖动
    this->setAcceptDrops(true);

    // 创建布局
    this->m_mainLayout = new QVBoxLayout(this);
    this->m_mainLayout->setContentsMargins(0, 0, 0, 0);
    this->m_mainLayout->setSpacing(0);

    //设置标题标签
    this->m_titleLabel = new BaseWidgets::AutoFitLabel(this, 4);
    // this->m_titleLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->m_mainLayout->addWidget(this->m_titleLabel);

    this->setDefaultStyle();
}

void CoreControlWidgets::SelectTab_NS::IPT_Base::setDefaultText(const QString &title)
{
    this->defaultText = title;
    this->setDefaultStyle();
}

void CoreControlWidgets::SelectTab_NS::IPT_Base::setDefaultStyle()
{
    this->setStyleSheet(QString(R"(
        QWidget#%1{
            border: 2px dashed  #ffffff;
            border-radius: 6px;
            background-color: rgba(155, 208, 255, 0.4);
        }
    )").arg(this->objectName()));

    this->m_titleLabel->setText(defaultText);
    this->m_titleLabel->setStyleSheet("color: #333333;");
}

void CoreControlWidgets::SelectTab_NS::IPT_Base::setTargetText(const QString &title)
{
    this->targetText = title;
}

void CoreControlWidgets::SelectTab_NS::IPT_Base::setTargetStyle()
{
    this->setStyleSheet(QString(R"(
        QWidget#%1{
            border: 2px dashed #1E90FF;
            border-radius: 6px;
            background-color: rgba(155, 208, 255, 0.6);
        }
    )").arg(this->objectName()));

    this->m_titleLabel->setText(targetText);
    this->m_titleLabel->setStyleSheet("color: #1E90FF;");
}

void CoreControlWidgets::SelectTab_NS::IPT_Base::dragEnterEvent(QDragEnterEvent *event)
{
    this->m_isInDrag = true;
    if (not event->mimeData()->hasUrls())
        return;

    QFileInfo fileInfo(event->mimeData()->urls().first().toLocalFile());
    if (not fileInfo.isFile())
        return;

    event->acceptProposedAction();
    this->setTargetStyle();
}

void CoreControlWidgets::SelectTab_NS::IPT_Base::dragLeaveEvent(QDragLeaveEvent *event)
{
    this->m_isInDrag = false;
    Q_UNUSED(event);
    this->setDefaultStyle();

    GlobalVariables* gv = GlobalVariables::getInstance();
    QTimer::singleShot(0, [this, gv](){
        if (
            gv->select_tab->importFile_page->IPT_FileToSelect->m_isInDrag  ||
            gv->select_tab->importFile_page->IPT_FileToList  ->m_isInDrag  ||
            gv->select_tab->importFile_page->IPT_BouthDouble ->m_isInDrag  ||
            gv->select_tab->m_isInDrag
        ) return;
        gv->select_tab->setPage(gv->select_tab->m_oldPage);
    });
}

void CoreControlWidgets::SelectTab_NS::IPT_Base::dropEvent(QDropEvent *event)
{
    this->m_isInDrag = false;
    Q_UNUSED(event);
    this->setDefaultStyle();

    this->m_filePath = event->mimeData()->urls().first().toLocalFile();

    GlobalVariables* gv = GlobalVariables::getInstance();
    gv->select_tab->setPage(gv->select_tab->m_oldPage);

    this->importFunction(this->m_filePath);
}
