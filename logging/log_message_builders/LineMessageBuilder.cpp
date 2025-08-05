//
// Created by User on 26.07.2025.
//

#include "LineMessageBuilder.h"

#include <chrono>
#include <sstream>
#include <thread>

namespace Logging {
    std::string LineMessageBuilder::Build() const {
        thread_local std::string line;
        line.clear();
        line.reserve(100);

        line.append(buildTimestamp());
        line.append(" - ");
        line.append(" [threadId: ");
        line.append(this->buildThreadId());
        line.append("] ");
        line.append(" - ");
        line.append(this->logLevel);
        line.append(": ");
        line.append(this->message);

        return line;
    }

    LineMessageBuilder &LineMessageBuilder::SetLogLevel(const Constants::Warn::WARN_LEVELS logLevel) noexcept {
        switch (logLevel) {
            case Constants::Warn::WARN_LEVELS::DEBUG:
                this->logLevel = "DEBUG";
                break;
            case Constants::Warn::WARN_LEVELS::INFO:
                this->logLevel = "INFO";
                break;
            case Constants::Warn::WARN_LEVELS::WARNING:
                this->logLevel = "WARNING";
                break;
            case Constants::Warn::WARN_LEVELS::ERROR:
                this->logLevel = "ERROR";
                break;
            case Constants::Warn::WARN_LEVELS::CRITICAL:
                this->logLevel = "CRITICAL";
                break;
            default:
                this->logLevel = "Unknown";
        }
        return *this;
    }

    LineMessageBuilder &LineMessageBuilder::SetMessage(std::string_view message) {
        this->message = std::move(message);
        return *this;
    }

    std::string LineMessageBuilder::buildTimestamp() const {
        thread_local char buffer[20];
        const auto now{std::chrono::system_clock::now()};
        const std::time_t nowTime{std::chrono::system_clock::to_time_t(now)};
        std::tm tm{};

        #ifdef _WIN32
            localtime_s(&tm, &nowTime);
        #else
            localtime_r(&nowTime, &tm);
        #endif

        const auto n = std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &tm);
        return n ? std::string(buffer, n) : std::string{};
    }

    std::string LineMessageBuilder::buildThreadId() const {
        const std::thread::id id{std::this_thread::get_id()};
        thread_local std::stringstream ss;
        ss.str("");
        ss.clear();
        ss << id;
        return ss.str();
    }
} // Logging
