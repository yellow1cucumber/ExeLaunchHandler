//
// Created by User on 31.07.2025.
//

#ifndef CONFIGTAB_H
#define CONFIGTAB_H

#include <qmessagebox.h>

#include "../export.h"
#include "ConfigManager.h"
#include "converting/JsonSerializer.h"
#include <qfiledialog.h>

namespace UI {
    QT_BEGIN_NAMESPACE

    namespace Ui {
        class ConfigTab;
    }

    QT_END_NAMESPACE

    class EXELAUNCHHANDLER_UI_API ConfigTab final : public QWidget {
        Q_OBJECT

    public:
        explicit ConfigTab(QWidget *parent = nullptr);

        ~ConfigTab() override;

    public slots:
        void applyConfig() const;

    private:
        Ui::ConfigTab *ui;

        Configuration::ConfigManager &configManager;

        void loadConfiguration() const;

        void loadLoggerConfigForm(const Configuration::AppConfig &config) const;

        void loadPipesConfigForm(const Configuration::AppConfig &config) const;

        void loadExeRunnerConfigForm(const Configuration::AppConfig &config) const;

        void bindControlButtons();
        void bindFileDialogButtons();

        const QStringList warningLevels = {
            QString::fromStdString(Constants::toString(Constants::WARN_LEVELS::DEBUG)),
            QString::fromStdString(Constants::toString(Constants::WARN_LEVELS::INFO)),
            QString::fromStdString(Constants::toString(Constants::WARN_LEVELS::WARNING)),
            QString::fromStdString(Constants::toString(Constants::WARN_LEVELS::ERROR)),
            QString::fromStdString(Constants::toString(Constants::WARN_LEVELS::CRITICAL)),
            QString::fromStdString(Constants::toString(Constants::WARN_LEVELS::FATAL))
        };
    };
}; // UI

#endif //CONFIGTAB_H
