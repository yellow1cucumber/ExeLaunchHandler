//
// Created by User on 05.08.2025.
//

#include "ErrorDisplay.h"

#include <qmessagebox.h>

namespace UI {
    void  ErrorDisplay::showError(const std::string &summary, const std::string &message) {
        QMessageBox::critical(nullptr,
                              QString::fromStdString(summary),
                              QString::fromStdString(message));
    }
}

