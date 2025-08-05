//
// Created by User on 05.08.2025.
//

#include "Priority.h"

#include <stdexcept>

namespace Constants::Processes {
    DWORD toWindowsPRIORITY(const PRIORITY priority) {
        switch (priority) {
            case PRIORITY::Idle: return IDLE_PRIORITY_CLASS;
            case PRIORITY::BelowNormal: return BELOW_NORMAL_PRIORITY_CLASS;
            case PRIORITY::Normal: return NORMAL_PRIORITY_CLASS;
            case PRIORITY::AboveNormal: return ABOVE_NORMAL_PRIORITY_CLASS;
            case PRIORITY::High: return HIGH_PRIORITY_CLASS;
            case PRIORITY::Realtime: return REALTIME_PRIORITY_CLASS;
            default: return NORMAL_PRIORITY_CLASS;
        }
    }

    std::wstring toString(const PRIORITY priority) {
        switch (priority) {
            case PRIORITY::Idle: return L"IDLE_PRIORITY_CLASS";
            case PRIORITY::BelowNormal: return L"BELOW_NORMAL_PRIORITY_CLASS";
            case PRIORITY::Normal: return L"NORMAL_PRIORITY_CLASS";
            case PRIORITY::AboveNormal: return L"ABOVE_NORMAL_PRIORITY_CLASS";
            case PRIORITY::High: return L"HIGH_PRIORITY_CLASS";
            case PRIORITY::Realtime: return L"REALTIME_PRIORITY_CLASS";
            default: return L"NORMAL_PRIORITY_CLASS";
        }
    }

    PRIORITY fromString(const std::wstring &priorityStr) {
        if (priorityStr == L"IDLE_PRIORITY_CLASS") return PRIORITY::Idle;
        if (priorityStr == L"BELOW_NORMAL_PRIORITY_CLASS") return PRIORITY::BelowNormal;
        if (priorityStr == L"NORMAL_PRIORITY_CLASS") return PRIORITY::Normal;
        if (priorityStr == L"ABOVE_NORMAL_PRIORITY_CLASS") return PRIORITY::AboveNormal;
        if (priorityStr == L"HIGH_PRIORITY_CLASS") return PRIORITY::High;
        if (priorityStr == L"REALTIME_PRIORITY_CLASS") return PRIORITY::Realtime;
        throw std::invalid_argument("Invalid priority string");
    }

    PRIORITY fromString(const std::string &priorityStr) {
        return fromString(std::wstring(priorityStr.begin(), priorityStr.end()));
    }
}
