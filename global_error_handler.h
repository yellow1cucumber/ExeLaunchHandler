// GlobalErrorHandler.h
#pragma once

#include <csignal>
#include <exception>
#include <iostream>
#include "Logger.h"
#include "ui/warnings/ErrorDisplay.h"

namespace ErrorHandler {
    inline void showFatalError(const std::string &message) {
        if (Logging::Logger::isInitialized()) {
            Logging::Logger::Error("Fatal error: " + message);
        } else {
            std::cerr << "Fatal error: " << message << std::endl;
        }

        UI::ErrorDisplay::showError("Фатальная ошибка", message);
    }

    inline void terminateHandler() {
        if (const auto ex = std::current_exception()) {
            try {
                std::rethrow_exception(ex);
            } catch (const std::exception &e) {
                showFatalError("Uncaught exception: " + std::string(e.what()));
            } catch (...) {
                showFatalError("Unknown uncaught exception");
            }
        } else {
            showFatalError("Terminate called without active exception");
        }
    }

    inline void signalHandler(const int signal) {
        std::string msg;
        switch (signal) {
            case SIGSEGV: msg = "Segmentation fault (SIGSEGV)";
                break;
            case SIGABRT: msg = "Abort signal (SIGABRT)";
                break;
            case SIGFPE: msg = "Floating point exception (SIGFPE)";
                break;
            case SIGILL: msg = "Illegal instruction (SIGILL)";
                break;
            default: msg = "Unknown signal: " + std::to_string(signal);
                break;
        }

        showFatalError(msg);
    }

    inline void installGlobalHandlers() {
        std::set_terminate(terminateHandler);

        std::signal(SIGSEGV, signalHandler);
        std::signal(SIGABRT, signalHandler);
        std::signal(SIGFPE, signalHandler);
        std::signal(SIGILL, signalHandler);
    }
} // namespace ErrorHandler
