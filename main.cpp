#include "python_bridge/Adapter.h"

#include <iostream>
#include <QApplication>

#include "cxxopts.hpp"
#include "Logger.h"
#include "PipelineSync.h"
#include "ProcessLauncher.h"
#include "config/ConfigManager.h"
#include "config/converting/JsonSerializer.h"
#include "ui/main_window/mainwindow.h"
#include "ui/splash_screen/SplashScreenWrapper.h"
#include "ui/warnings/ErrorDisplay.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    std::unique_ptr<UI::SplashScreenWrapper> splashScreenManager;

    cxxopts::Options options{
        "ExeLaunchHandler",
        "Application for managing and launching executables with logging and configuration support"
    };

    options.add_options()
            ("c,config", "Config file path", cxxopts::value<std::string>())
            ("h,help", "Show help message")
            ("u,ui", "Enable UI mode", cxxopts::value<bool>()->default_value("false")->implicit_value("true"));

    const auto result = options.parse(argc, argv);

    if (result["help"].as<bool>()) {
        std::cout << options.help();
        return 0;
    }

    const auto configPath = result["config"].as<std::string>();
    if (configPath.empty()) {
        std::cerr << "Configuration path not found" << std::endl;
        return 1;
    }

    if (const auto uiMode = result["ui"].as<bool>(); !uiMode) {
        splashScreenManager = std::make_unique<UI::SplashScreenWrapper>();
        splashScreenManager->show();
    }

    Configuration::ConfigManager::init(std::make_unique<Configuration::Converting::JsonSerializer>(), configPath);
    Configuration::ConfigManager &configManager{Configuration::ConfigManager::getInstance()};
    configManager.loadFromFile(configPath);

    Logging::Logger::init(configManager.getCached()->loggerConfig);
    Logging::Logger::Info("Application loaded with configuration: " + configPath);
    auto &logger{Logging::Logger::getInstance()};

    if (result["ui"].as<bool>()) {
        Logging::Logger::Info("Loaded in UI mode");

        UI::MainWindow mainWindow;
        mainWindow.show();

        return QApplication::exec();
    }

    Logging::Logger::Debug("Python bridge initialization start");
    PyBridge::Adapter adapter;
    adapter.Initialize(argv[0]);
    adapter.LoadScriptsFromDir(configManager.getCached()->pipesConfig.scriptsDir);
    Logging::Logger::Debug("Python bridge initialization complete");

    Pipes::PipelineSync pipelineSync{false};
    for (auto &pipe: adapter.GetRegisteredPipes()) {
        Logging::Logger::Info("Registered pipe: " + pipe.GetName());

        pipe.onStart = [pipe]() {
            Logging::Logger::Info("Pipe started: " + pipe.GetName());
        };
        pipe.onFinish = [pipe]() {
            Logging::Logger::Info("Pipe finished: " + pipe.GetName());
        };

        pipelineSync.AddStage(pipe);
    }

    const auto &executionResult{pipelineSync.Execute()};

    adapter.Finalize();
    executionResult.isOk()
        ? Logging::Logger::Info("Pipeline executed successfully")
        : Logging::Logger::Error("Pipeline execution failed: " + executionResult.getMessage());

    constexpr Launch::ProcessLauncher launcher;
    const Configuration::AppConfig &exeConfig{configManager.getCached().value_or(Configuration::AppConfig())};

    // delay region;
    if (splashScreenManager) {
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    const auto launchStatus{launcher.launchDetached(exeConfig.exeRunnerConfig)};
    launchStatus
        ? Logging::Logger::Info("Process launched successfully")
        : Logging::Logger::Error("Failed to launch process");

    if (splashScreenManager) {
        splashScreenManager->hide();
    }

    if (!launchStatus) {
        UI::ErrorDisplay::showError("Не удалось запустить процесс",
                                    "Запустите приложение вручную, дайте сисадмину банку редбула и заставьте его починить это");
    }
}
