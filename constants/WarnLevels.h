//
// Created by User on 28.07.2025.
//

#ifndef WARNLEVELS_H
#define WARNLEVELS_H

#include <string>
#include <stdexcept>

#include "export.h"

namespace Constants {
    enum class WARN_LEVELS {
        DEBUG = 0,
        INFO = 1,
        WARNING = 2,
        ERROR = 3,
        CRITICAL = 4,
        FATAL = 5
    };

    EXELAUNCHHANDLER_CONSTANTS_API std::string toString(const WARN_LEVELS warnLevel);

    EXELAUNCHHANDLER_CONSTANTS_API WARN_LEVELS fromString(const std::string& level);
}

#endif //WARNLEVELS_H
