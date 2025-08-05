//
// Created by User on 28.07.2025.
//

#include "JsonSerializer.h"

#include <fstream>

#include "Priority.h"

namespace Configuration::Converting {
    const Configuration::AppConfig JsonSerializer::fromFile(const std::string &filePath) {
        std::ifstream configFile(filePath);
        if (!configFile.is_open()) {
            throw std::runtime_error("Could not open configuration file: " + filePath);
        }
        nlohmann::json jsonConfig;
        configFile >> jsonConfig;

        AppConfig appConfig;
        JsonSerializer::fromJson(jsonConfig, appConfig);
        return appConfig;
    }

    void JsonSerializer::toFile(const std::string &filePath, const AppConfig &config) {
        std::ofstream configFile(filePath);
        if (!configFile.is_open()) {
            throw std::runtime_error("Could not open configuration file for writing: " + filePath);
        }

        const nlohmann::json jsonConfig = JsonSerializer::toJson(config);
        configFile << jsonConfig.dump(4);
        configFile.close();
    }

    void JsonSerializer::fromJson(const nlohmann::json &json, AppConfig &config) {
        JsonSerializer::fromJson(json["loggerConfig"], config.loggerConfig);
        JsonSerializer::fromJson(json["pipesConfig"], config.pipesConfig);
        JsonSerializer::fromJson(json["exeRunnerConfig"], config.exeRunnerConfig);
    }

    nlohmann::json JsonSerializer::toJson(const AppConfig &config) {
        nlohmann::json json;
        json["loggerConfig"] = JsonSerializer::toJson(config.loggerConfig);
        json["pipesConfig"] = JsonSerializer::toJson(config.pipesConfig);
        json["exeRunnerConfig"] = JsonSerializer::toJson(config.exeRunnerConfig);
        return json;
    }

    void JsonSerializer::fromJson(const nlohmann::json &json, LoggerConfig &config) {
        const auto logLevelRaw{json.at("logLevel").get<std::string>()};
        config.logLevel = Constants::Warn::fromString(logLevelRaw);

        if (!json.contains("logFile")) {
            config.logFile = "logs/log.txt";
        }
        json.at("logFile").get_to(config.logFile);

        if (json.contains("logFileMaxFileMB")) {
            json.at("logFileMaxFileMB").get_to(config.logFileMaxSizeMB);
        }
    }

    void JsonSerializer::fromJson(const nlohmann::json &json, PipesConfig &config) {
        if (!json.contains("scriptsDir")) {
            throw std::invalid_argument("scriptsDir is required in PipesConfig and must be string");
        }
        json.at("scriptsDir").get_to(config.scriptsDir);

        if (json.contains("runSync")) {
            json.at("runSync").get_to(config.runSync);
        }
    }

    void JsonSerializer::fromJson(const nlohmann::json &json, ExeRunnerConfig &config) {
        if (!json.contains("exePath")) {
            throw std::invalid_argument("exePath is required in ExeRunnerConfig and must be string");
        }
        json.at("exePath").get_to(config.exePath);

        if (json.contains("exeArgs")) {
            json.at("exeArgs").get_to(config.exeArgs);
        }

        if (json.contains("processPriority")) {
            const auto priorityStr = json.at("processPriority").get<std::string>();
            config.processPriority = Constants::Processes::fromString(priorityStr);
        }

        if (json.contains("cancelOnFatalError")) {
            json.at("cancelOnFatalError").get_to(config.cancelOnFatalError);
        }
    }

    nlohmann::json JsonSerializer::toJson(const LoggerConfig &config) {
        nlohmann::json logJson;
        logJson["logLevel"] = Constants::Warn::toString(config.logLevel);
        if (config.logFile.has_value()) {
            logJson["logFile"] = config.logFile.value();
        };
        if (config.logFileMaxSizeMB.has_value()) {
            logJson["logFileMaxFileMB"] = config.logFileMaxSizeMB.value();
        }
        return logJson;
    }

    nlohmann::json JsonSerializer::toJson(const PipesConfig &config) {
        nlohmann::json pipesJson;
        pipesJson["scriptsDir"] = config.scriptsDir;
        pipesJson["runSync"] = config.runSync;
        return pipesJson;
    }

    nlohmann::json JsonSerializer::toJson(const ExeRunnerConfig &config) {
        nlohmann::json exeRunnerJson;
        exeRunnerJson["exePath"] = config.exePath;
        if (config.exeArgs.has_value()) {
            exeRunnerJson["exeArgs"] = config.exeArgs.value();
        }
        if (config.processPriority.has_value()) {
            exeRunnerJson["processPriority"] = config.processPriority.value();
        }
        exeRunnerJson["cancelOnFatalError"] = config.cancelOnFatalError;
        return exeRunnerJson;
    }
}
