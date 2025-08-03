#include "python_bridge/Adapter.h"

#include <iostream>
#include <QApplication>

#include "cxxopts.hpp"
#include "Logger.h"
#include "PipelineSync.h"
#include "config/ConfigManager.h"
#include "config/converting/JsonSerializer.h"
#include "ui/main_window/mainwindow.h"

int main(int argc, char *argv[]) {
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

    Configuration::ConfigManager::init(std::make_unique<Configuration::Converting::JsonSerializer>(), configPath);
    Configuration::ConfigManager &configManager{Configuration::ConfigManager::getInstance()};
    configManager.loadFromFile(configPath);

    Logging::Logger::init(configManager.getCached()->loggerConfig);
    Logging::Logger::Info("Application loaded with configuration: " + configPath);

    if (result["ui"].as<bool>()) {
        Logging::Logger::Info("Loaded in UI mode");
        QApplication a(argc, argv);

        UI::MainWindow mainWindow;
        mainWindow.show();

        return QApplication::exec();
    }

    Logging::Logger::Debug("Python bridge initialization start");
    PyBridge::Adapter adapter;
    adapter.Initialize(Logging::Logger::getInstance());
    adapter.LoadScriptsFromDir(configManager.getCached()->pipesConfig.scriptsDir);
    Logging::Logger::Debug("Python bridge initialization complete");

    Pipes::PipelineSync pipelineSync{ false };
    for (auto &pipe : adapter.GetRegisteredPipes()) {
        Logging::Logger::Info("Registered pipe: " + pipe.GetName());

        pipe.onStart = [&pipe]() {
            Logging::Logger::Info("Pipe started: " + pipe.GetName());
        };
        pipe.onFinish = [&pipe]() {
            Logging::Logger::Info("Pipe finished: " + pipe.GetName());
        };

        pipelineSync.AddStage(pipe);
    }

    const auto& executionResult = pipelineSync.Execute();

    adapter.Finalize();
    if (executionResult.isOk()) {
        return 0;
    }
    return 1;

    // TODO:
    // add pipes execution logic;
    // add tab for scripts listing;
    // add more logging information;
    // prettify main.cpp
    // make python adapter singleton or make list of pipes static
}
