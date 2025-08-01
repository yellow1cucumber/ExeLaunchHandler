//
// Created by User on 26.07.2025.
//

#ifndef RESULTBASE_H
#define RESULTBASE_H
#include <string>

#include "Status.h"
#include "export.h"

namespace ResultAPI {
    class EXELAUNCHHANDLER_RESULTSAPI_API ResultBase {
    public:
        ResultBase() = delete;

        [[nodiscard]] bool isOk() const noexcept;

        [[nodiscard]] bool isWarning() const noexcept;

        [[nodiscard]] bool isError() const noexcept;

        [[nodiscard]] bool isFatal() const noexcept;

        [[nodiscard]] Status getStatus() const noexcept;

        [[nodiscard]] const std::string &getMessage() const noexcept;

        [[nodiscard]] const std::exception_ptr &getException() const noexcept;

    protected:
        Status status;
        std::string message;
        std::exception_ptr ex;

        ResultBase(Status s, std::string msg, std::exception_ptr ex = {});
    };
} // ResultAPI

#endif //RESULTBASE_H
