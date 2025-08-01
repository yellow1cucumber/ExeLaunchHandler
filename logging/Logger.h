//
// Created by User on 26.07.2025.
//

#ifndef LOGGER_H
#define LOGGER_H
#include <fstream>
#include <memory>
#include <mutex>

#include "../config/AppConfig.h"
#include "log_message_builders/LineMessageBuilder.h"

#include "export.h"

namespace Logging {
    class EXELAUNCHHANDLER_LOGGING_API Logger {
    public:
        static Logger& init(const Configuration::LoggerConfig& config);
        static bool isInitialized() noexcept;

        [[nodiscard]]
        static Logger& getInstance();

        void Log(const Constants::WARN_LEVELS &logLevel, const std::string_view& message);

        static void Debug(std::string_view message);
        static void Info(std::string_view message);
        static void Warning(std::string_view message);
        static void Error(std::string_view message);
        static void Critical(std::string_view message);

        Logger(const Logger&) = delete;
        Logger& operator=(const Logger&) = delete;
        Logger(Logger&&) = delete;
        Logger& operator=(Logger&&) = delete;

        ~Logger() noexcept;

    private:
        explicit Logger(const Configuration::LoggerConfig& config);

        inline static std::unique_ptr<Logger> instance;
        inline static std::once_flag initOnce;

        const Configuration::LoggerConfig& config;
        LineMessageBuilder builder;

        std::mutex writeMutex;
        std::unique_ptr<std::ofstream> logFile;
    };
} // Logging

#endif //LOGGER_H
