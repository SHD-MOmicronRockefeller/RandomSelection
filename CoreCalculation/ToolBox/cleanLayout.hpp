#pragma once

#include "QtPrecompiled.h"

namespace MYFUNCTION {

class CleanLayout {
    public: static void cleanLayout(QLayout* layout) {
        if (not layout) return;
        QLayoutItem* item = nullptr;
        while ((item = layout->takeAt(0)) != nullptr) {
            if (QWidget* widget = item->widget()) widget->deleteLater();
            else if (QLayout* childLayout = item->layout()) {
                cleanLayout(childLayout);
                childLayout->deleteLater();
            }
            else delete item;
        }
        return;
    }
    public: void operator()(QLayout* layout) const {
        cleanLayout(layout);
    }
    public: CleanLayout& operator<<(QLayout* layout) {
        cleanLayout(layout);
        return *this;
    }

};


} // namespace MYFUNCTION