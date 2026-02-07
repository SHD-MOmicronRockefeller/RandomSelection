#include "IPT_base.h"
#include "BaseWidgets/BaseCoreWidget/TinyWidget/AutoFitLabel.h"

using namespace CoreControlWidgets::SelectTab_NS;

IPT_Base::IPT_Base(QString _ObjectName, std::function<void(QString)> _func, QWidget *parent): QWidget(parent)
{
    this->setAutoFillBackground(true);
    this->setAttribute(Qt::WA_StyledBackground, true);
    this->setObjectName(_ObjectName);
    this->importFunction = std::move(_func);
    this->setAcceptDrops(true);

    this->m_mainLayout = new QVBoxLayout(this);
    this->m_mainLayout->setContentsMargins(0, 0, 0, 0);
    this->m_mainLayout->setSpacing(0);

    this->m_titleLabel = new BaseWidgets::AutoFitLabel(this, 4);
    this->m_mainLayout->addWidget(this->m_titleLabel);
    this->setDefaultStyle();
}

void IPT_Base::setDefaultText(const QString &title)
{
    this->defaultText = title;
    this->setDefaultStyle();
}

void IPT_Base::setDefaultStyle()
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

void IPT_Base::setTargetText(const QString &title)
{
    this->targetText = title;
}

void IPT_Base::setTargetStyle()
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

void IPT_Base::dragEnterEvent(QDragEnterEvent *event)
{
    this->m_isInDrag = true;
    emit dragEntered();  // 发射进入拖拽信号
    qDebug() << "进入" << this->objectName();
    if (!event->mimeData()->hasUrls()) return;

    QFileInfo fileInfo(event->mimeData()->urls().first().toLocalFile());
    if (!fileInfo.isFile()) return;

    event->acceptProposedAction();
    this->setTargetStyle();
}

void IPT_Base::dragLeaveEvent(QDragLeaveEvent *event)
{
    this->m_isInDrag = false;
    emit dragLeaved();   // 发射离开拖拽信号
    qDebug() << "离开" << this->objectName();
    Q_UNUSED(event);
    this->setDefaultStyle();
}

void IPT_Base::dropEvent(QDropEvent *event)
{
    qDebug() << "拖拽" << this->objectName();
    this->m_isInDrag = false;
    emit dragLeaved();   // 放下后也发射离开信号
    Q_UNUSED(event);
    this->setDefaultStyle();

    this->m_filePath = event->mimeData()->urls().first().toLocalFile();
    this->importFunction(this->m_filePath);
}