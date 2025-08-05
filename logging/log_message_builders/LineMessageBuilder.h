//
// Created by User on 26.07.2025.
//

#ifndef LINEMESSAGEBUILDER_H
#define LINEMESSAGEBUILDER_H
#include <string_view>

#include "../../constants/WarnLevels.h"
#include "../export.h"

namespace Logging {
    class EXELAUNCHHANDLER_LOGGING_API LineMessageBuilder {
    public:
        [[nodiscard]] std::string Build() const;

        LineMessageBuilder &SetLogLevel(Constants::Warn::WARN_LEVELS logLevel) noexcept;
        LineMessageBuilder &SetMessage(std::string_view message);

    private:
        [[nodiscard]] std::string buildTimestamp() const;
        [[nodiscard]] std::string buildThreadId() const;

        std::string logLevel;
        std::string message;
    };
} // Logging

#endif //LINEMESSAGEBUILDER_H
