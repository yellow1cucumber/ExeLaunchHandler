//
// Created by User on 26.07.2025.
//

#include "Logger.h"

#include <filesystem>
#include <thread>

namespace Logging {
    Logger::Logger(const Configuration::LoggerConfig &config) : config(config) {
        std::string logFilePath = this->config.logFile.value_or("log.txt");

        if (this->config.logFileMaxSizeMB.has_value() && this->isOutOfMemoryBudget()) {
            std::filesystem::remove(logFilePath);
        }

        this->logFile = std::make_unique<std::ofstream>(logFilePath, std::ios::app);
        if (!this->logFile->is_open()) {
            throw std::runtime_error("Failed to open log file: " + logFilePath);
        }
    }

    bool Logger::isOutOfMemoryBudget() const noexcept {
        if (!this->config.logFile.has_value()) return false;
        if (!std::filesystem::exists(this->config.logFile.value())) return false;
        if (!this->config.logFileMaxSizeMB.has_value()) return false;

        const std::uintmax_t sizeInBytes = std::filesystem::file_size(this->config.logFile.value());
        const std::uintmax_t sizeInMB = sizeInBytes / (1024 * 1024);
        return sizeInMB > this->config.logFileMaxSizeMB.value();
    }


    Logger &Logger::init(const Configuration::LoggerConfig &config) {
        std::call_once(initOnce, [&]() {
            instance.reset(new Logger(config));
        });
        return *instance;
    }

    bool Logger::isInitialized() noexcept {
        return Logger::instance ? true : false;
    }

    Logger &Logger::getInstance() {
        if (!instance) {
            throw std::logic_error("Logger not initialized. Call Logger::init() first.");
        }
        return *Logger::instance;
    }

    void Logger::Log(const Constants::Warn::WARN_LEVELS &logLevel, const std::string_view &message) {
        if (logLevel < this->config.logLevel) {
            return;
        }

        std::lock_guard lock(writeMutex);

        if (this->logFile && this->logFile->is_open()) {
            const auto logLine{
                this->builder.SetLogLevel(logLevel)
                .SetMessage(message)
                .Build()
            };

            *this->logFile << logLine << std::endl;
            this->logFile->flush();
        } else {
            throw std::runtime_error("Log file is not open.");
        }
    }

    void Logger::Debug(std::string_view message) {
        Logger::instance->Log(Constants::Warn::WARN_LEVELS::DEBUG, message);
    }

    void Logger::Info(std::string_view message) {
        Logger::instance->Log(Constants::Warn::WARN_LEVELS::INFO, message);
    }

    void Logger::Warning(std::string_view message) {
        Logger::instance->Log(Constants::Warn::WARN_LEVELS::WARNING, message);
    }

    void Logger::Error(std::string_view message) {
        #undef ERROR;
        Logger::instance->Log(Constants::Warn::WARN_LEVELS::ERROR, message);
    }

    void Logger::Critical(std::string_view message) {
        Logger::instance->Log(Constants::Warn::WARN_LEVELS::CRITICAL, message);
    }

    Logger::~Logger() noexcept {
        if (this->logFile && this->logFile->is_open()) {
            this->logFile->close();
        }
        this->logFile.reset();
    }
} // Logging
