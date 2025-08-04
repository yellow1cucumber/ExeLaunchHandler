#include "WarnLevels.h"

#include <stdexcept>

namespace Constants {
    std::string toString(const WARN_LEVELS warnLevel) {
        switch (warnLevel) {
            case WARN_LEVELS::DEBUG: return "Debug";
            case WARN_LEVELS::INFO: return "Info";
            case WARN_LEVELS::WARNING: return "Warning";
            case WARN_LEVELS::ERROR: return "Error";
            case WARN_LEVELS::CRITICAL: return "Critical";
            case WARN_LEVELS::FATAL: return "Fatal";
            default: return "UNKNOWN";
        }
    }

    WARN_LEVELS fromString(const std::string& level) {
        if (level == "Debug") return WARN_LEVELS::DEBUG;
        if (level == "Info") return WARN_LEVELS::INFO;
        if (level == "Warning") return WARN_LEVELS::WARNING;
        if (level == "Error") return WARN_LEVELS::ERROR;
        if (level == "Critical") return WARN_LEVELS::CRITICAL;
        if (level == "Fatal") return WARN_LEVELS::FATAL;
        throw std::invalid_argument("Unknown warn level: " + level);
    }
}