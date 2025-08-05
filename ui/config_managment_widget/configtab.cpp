//
// Created by User on 31.07.2025.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ConfigTab.h" resolved

#include "configtab.h"

#include "ConfigManager.h"
#include "ui_ConfigTab.h"
#include <qdebug.h>

#include "Logger.h"

namespace UI {
    ConfigTab::ConfigTab(QWidget *parent) : QWidget(parent), ui(new Ui::ConfigTab),
                                            configManager(Configuration::ConfigManager::getInstance()) {
        ui->setupUi(this);
        this->loadConfiguration();
        this->bindControlButtons();
        this->bindFileDialogButtons();
    }

    void ConfigTab::loadConfiguration() const {
        if (!this->configManager.getCached().has_value()) {
            this->configManager.loadFromFile();
        }
        const auto &config{this->configManager.getCached().value()};

        this->loadLoggerConfigForm(config);
        this->loadPipesConfigForm(config);
        this->loadExeRunnerConfigForm(config);
    }

    void ConfigTab::loadLoggerConfigForm(const Configuration::AppConfig &config) const {
        this->ui->warningLevelComboBox->clear();
        this->ui->warningLevelComboBox->addItems(this->warningLevels);
        this->ui->warningLevelComboBox->setToolTip(
            "Select the log level for the application. Higher levels will include lower levels.");
        this->ui->warningLevelComboBox->setCurrentIndex(
            this->warningLevels.indexOf(QString::fromStdString(Constants::Warn::toString(config.loggerConfig.logLevel)))
        );

        this->ui->logFilePathLineEdit->setText(QString::fromStdString(config.loggerConfig.logFile.value()));
        this->ui->logFilePathLineEdit->setToolTip(
            "Specify the path to the log file. If not specified, 'log.txt' will be used.");

        this->ui->logFileMaxSize->setValue(config.loggerConfig.logFileMaxSizeMB.value_or(1.0));
        this->ui->logFileMaxSize->setToolTip(
            "Set the maximum size of the log file in MB. If the file exceeds this size, it will be rotated.");
    }

    void ConfigTab::loadPipesConfigForm(const Configuration::AppConfig &config) const {
        this->ui->scriptsDirPathLineEdit->setText(QString::fromStdString(config.pipesConfig.scriptsDir));
        this->ui->scriptsDirPathLineEdit->setToolTip("Specify the directory where the scripts are located.");

        this->ui->runSyncCheckBox->setChecked(config.pipesConfig.runSync);
        this->ui->runSyncCheckBox->setToolTip(
            "Enable this option to run scripts synchronously. If disabled, scripts will run asynchronously.");
    }

    void ConfigTab::loadExeRunnerConfigForm(const Configuration::AppConfig &config) const {
        this->ui->exePathLineEdit->setText(QString::fromStdString(config.exeRunnerConfig.exePath));
        this->ui->exePathLineEdit->setToolTip(
            "Specify the path to the executable file that will be run by the application.");

        this->ui->exeRunArgsTextEdit->setText(QString::fromStdString(config.exeRunnerConfig.exeArgs.value_or("")));
        this->ui->exeRunArgsTextEdit->setToolTip(
            "Specify the arguments that will be passed to the executable file when it is run.");

        this->ui->processPriorityComboBox->clear();
        this->ui->processPriorityComboBox->addItems(this->exeLaunchPriorityLevels);
        this->ui->processPriorityComboBox->setToolTip(
            "Select the priority level for the executable process. Higher levels will give more CPU time to the process.");
        this->ui->processPriorityComboBox->setCurrentIndex(
            this->exeLaunchPriorityLevels.indexOf(
                QString::fromStdWString(Constants::Processes::toWString(
                    config.exeRunnerConfig.processPriority.value_or(Constants::Processes::PRIORITY::Normal))))
        );
    }

    void ConfigTab::bindControlButtons() {
        QObject::connect(this->ui->loadFromFileButton, &QPushButton::clicked, this, [this]() {
            const auto caption = "Select From File";
            const auto filter = "Configuration Files (*.json);;All Files (*)";

            if (const QString filePath{
                QFileDialog::getOpenFileName(nullptr, caption, QString(), filter)
            }; !filePath.isEmpty()) {
                try {
                    this->configManager.loadFromFile(filePath.toStdString());
                    this->loadConfiguration();
                } catch (const std::exception &e) {
                    const auto msg{
                        QString("Failed to load configuration from file: %1").arg(e.what())
                    };
                    QMessageBox::warning(this, "Error", msg);
                }
            }
        });

        QObject::connect(this->ui->saveButton, &QPushButton::clicked, this, [this]() {
            try {
                this->applyConfig();
                QMessageBox::information(this, "Success", "Configuration saved successfully.");
            } catch (const std::exception &e) {
                const auto msg{QString("Failed to save configuration: %1").arg(e.what())};
                QMessageBox::critical(this, "Error", msg);
            }
        });
    }

    void ConfigTab::bindFileDialogButtons() {
        QObject::connect(this->ui->logFilePathExplorerButton, &QPushButton::clicked, this, [this]() {
            const auto caption = "Select Log File Path";
            const auto filter = "Log Files (*.log);;All Files (*)";

            if (const QString filePath{QFileDialog::getSaveFileName(nullptr, caption, QString(), filter)}; !filePath.
                isEmpty()) {
                this->ui->logFilePathLineEdit->setText(filePath);
            }
        });

        QObject::connect(this->ui->scriptsDirExplorerButton, &QPushButton::clicked, this, [this]() {
            const auto caption = "Select Scripts Directory";
            const auto filter = "Directories (*)";

            if (const QString dirPath{
                QFileDialog::getExistingDirectory(nullptr, caption, QString(),
                                                  QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks)
            }; !dirPath.isEmpty()) {
                this->ui->scriptsDirPathLineEdit->setText(dirPath);
            }
        });

        QObject::connect(this->ui->exePathExplorerButton, &QPushButton::clicked, this, [this]() {
            const auto caption = "Select Executable Path";
            const auto filter = "Executable Files (*.exe);;All Files (*)";

            if (const QString exePath{QFileDialog::getOpenFileName(nullptr, caption, QString(), filter)}; !exePath.
                isEmpty()) {
                this->ui->exePathLineEdit->setText(exePath);
            }
        });
    }

    ConfigTab::~ConfigTab() {
        delete ui;
    }

    void ConfigTab::applyConfig() const {
        Configuration::AppConfig config;
        config.loggerConfig.logLevel = Constants::Warn::fromString(
            this->ui->warningLevelComboBox->currentText().toStdString());
        config.loggerConfig.logFile = this->ui->logFilePathLineEdit->text().toStdString();
        config.loggerConfig.logFileMaxSizeMB = this->ui->logFileMaxSize->value();

        config.pipesConfig.scriptsDir = this->ui->scriptsDirPathLineEdit->text().toStdString();
        config.pipesConfig.runSync = this->ui->runSyncCheckBox->isChecked();

        config.exeRunnerConfig.exePath = this->ui->exePathLineEdit->text().toStdString();
        config.exeRunnerConfig.exeArgs = this->ui->exeRunArgsTextEdit->toPlainText().toStdString();
        config.exeRunnerConfig.processPriority = Constants::Processes::fromString(
            this->ui->processPriorityComboBox->currentText().toStdWString()
        );

        const auto &configManager{&Configuration::ConfigManager::getInstance()};
        configManager->save(std::nullopt, config);
    }
} // UI
