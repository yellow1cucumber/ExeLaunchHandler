#pragma once
#include <string>
#include <optional>
#include <exception>
#include <stdexcept>

#include "export.h"
#include "ResultBase.h"

namespace ResultAPI {
    template<typename T>
    class Result final : public ResultBase {
    public:
        static Result Ok(const T &value, const std::string &message = {}) {
            return Result(Status::Ok, value, message);
        }

        static Result Warning(const T &value, const std::string &message) {
            return Result(Status::Warning, value, message);
        }

        static Result Error(const std::string &message, const std::exception_ptr &ex = {}) {
            return Result(Status::Error, std::nullopt, message, ex);
        }

        static Result Fatal(const std::string &message, const std::exception_ptr &ex = {}) {
            return Result(Status::Fatal, std::nullopt, message, ex);
        }

        [[nodiscard]] const T &getValue() const {
            if (!value.has_value()) {
                throw std::runtime_error("Attempted to access value of Result that does not contain a value.");
            }
            return value.value();
        }

        [[nodiscard]] T &getValue() {
            if (!value.has_value()) {
                throw std::runtime_error("Attempted to access value of Result that does not contain a value.");
            }
            return value.value();
        }

    private:
        std::optional<T> value;

        Result(Status s, std::optional<T> val, const std::string &msg, const std::exception_ptr &ex = {})
            : ResultBase(s, msg, ex), value(std::move(val)) {}
    };

    template<>
    class EXELAUNCHHANDLER_RESULTSAPI_API Result<void> final : public ResultBase {
    public:
        static Result Ok(const std::string &message = {});

        static Result Warning(const std::string &message);

        static Result Error(const std::string &message, const std::exception_ptr &ex = {});

        static Result Fatal(const std::string &message, const std::exception_ptr &ex = {});

    private:
        Result(Status s, const std::string &msg, const std::exception_ptr &ex = {});
    };
} // namespace ResultAPI
