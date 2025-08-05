//
// Created by User on 06.08.2025.
//
#pragma once

#include "Adapter.h"
#include <iostream>
#include <QApplication>

#include "AppConfig.h"
#include "ConfigManager.h"
#include "cxxopts.hpp"
#include "Logger.h"
#include "PipelineSync.h"
#include "ProcessLauncher.h"
#include "converting/JsonSerializer.h"
#include "ui/main_window/mainwindow.h"

namespace App {
    inline cxxopts::Options createOptions() {
        cxxopts::Options options{
            "ExeLaunchHandler",
            "Application for managing and launching executables with logging and configuration support"
        };

        options.add_options()
                ("c,config", "Config file path", cxxopts::value<std::string>())
                ("h,help", "Show help message")
                ("u,ui", "Enable UI mode", cxxopts::value<bool>()->default_value("false")->implicit_value("true"));

        return options;
    }


    inline bool shouldShowHelp(const int argc, char *argv[]) {
        auto options = createOptions();
        const auto result = options.parse(argc, argv);
        return result.count("help") > 0;
    }

    inline void printHelp() {
        const auto options = createOptions();
        std::cout << options.help() << std::endl;
    }

    inline std::string getConfigPath(const int argc, char *argv[]) {
        auto options = createOptions();
        const auto result = options.parse(argc, argv);
        return result["config"].as<std::string>();
    }

    inline bool isUIModeEnabled(const int argc, char *argv[]) {
        auto options = createOptions();
        const auto result = options.parse(argc, argv);
        return result["ui"].as<bool>();
    }

    inline Configuration::AppConfig initApplication(const std::string &configPath) {
        Configuration::ConfigManager::init(
            std::make_unique<Configuration::Converting::JsonSerializer>(),
            configPath
        );

        auto &configManager = Configuration::ConfigManager::getInstance();
        configManager.loadFromFile(configPath);

        Logging::Logger::init(configManager.getCached()->loggerConfig);
        Logging::Logger::Info("Application loaded with configuration: " + configPath);

        return configManager.getCached().value_or(Configuration::AppConfig());
    }

    inline int runUIMode() {
        Logging::Logger::Info("Loaded in UI mode");
        UI::MainWindow mainWindow;
        mainWindow.show();
        return QApplication::exec();
    }

    inline bool runPipeline(const std::string &configPath) {
        Logging::Logger::Debug("Python bridge initialization start");

        PyBridge::Adapter adapter;
        adapter.Initialize(configPath.c_str());

        const auto &scriptsDir = Configuration::ConfigManager::getInstance()
                .getCached()->pipesConfig.scriptsDir;
        adapter.LoadScriptsFromDir(scriptsDir);

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

        const auto &result = pipelineSync.Execute();
        adapter.Finalize();

        if (result.isOk()) {
            Logging::Logger::Info("Pipeline executed successfully");
            return true;
        }
        Logging::Logger::Error("Pipeline execution failed: " + result.getMessage());
        return false;
    }

    inline bool launchProcess(const Configuration::AppConfig &config) {
        constexpr Launch::ProcessLauncher launcher;
        return launcher.launchDetached(config.exeRunnerConfig);
    }
}
