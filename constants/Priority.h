//
// Created by User on 05.08.2025.
//

#ifndef PRIORITY_H
#define PRIORITY_H
#include <string>

#include "export.h"
#include "windows.h"

namespace Constants::Processes {
    enum class PRIORITY {
        Idle = 0,
        BelowNormal = 1,
        Normal = 2,
        AboveNormal = 3,
        High = 4,
        Realtime = 5
    };

    EXELAUNCHHANDLER_CONSTANTS_API DWORD toWindowsPRIORITY(const PRIORITY priority);

    EXELAUNCHHANDLER_CONSTANTS_API std::wstring toWString(const PRIORITY priority);

    EXELAUNCHHANDLER_CONSTANTS_API std::string toString(const PRIORITY priority);

    EXELAUNCHHANDLER_CONSTANTS_API PRIORITY fromString(const std::wstring &priorityStr);

    EXELAUNCHHANDLER_CONSTANTS_API PRIORITY fromString(const std::string &priorityStr);
} // namespace Constants::Processes

#endif //PRIORITY_H
