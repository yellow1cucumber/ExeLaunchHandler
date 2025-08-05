//
// Created by User on 28.07.2025.
//

#ifndef APPCONFIG_H
#define APPCONFIG_H
#include <optional>

#include "../constants/WarnLevels.h"
#include "../constants/Priority.h"
#include "export.h"

namespace Configuration {
    struct EXELAUNCHHANDLER_CONFIG_API LoggerConfig {
        Constants::Warn::WARN_LEVELS logLevel{Constants::Warn::WARN_LEVELS::WARNING};
        std::optional<std::string> logFile{"Log.txt"};
        std::optional<double> logFileMaxSizeMB{std::nullopt}; // in MB
    };

    struct EXELAUNCHHANDLER_CONFIG_API PipesConfig {
        std::string scriptsDir;
        bool runSync{false};
    };

    struct EXELAUNCHHANDLER_CONFIG_API ExeRunnerConfig {
        std::string exePath;
        std::optional<std::string> exeArgs{std::nullopt};
        std::optional<Constants::Processes::PRIORITY> processPriority{Constants::Processes::PRIORITY::Normal};
        bool cancelOnFatalError{false};
    };

    class EXELAUNCHHANDLER_CONFIG_API AppConfig {
    public:
        LoggerConfig loggerConfig;
        PipesConfig pipesConfig;
        Configuration::ExeRunnerConfig exeRunnerConfig;
    };
}

#endif //APPCONFIG_H
