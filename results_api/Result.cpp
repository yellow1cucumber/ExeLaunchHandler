#include "Result.h"

namespace ResultAPI {
    Result<void>::Result(const Status s, const std::string &msg, const std::exception_ptr &ex)
        : ResultBase(s, msg, ex) {}

    Result<void> Result<void>::Ok(const std::string &message) {
        return {Status::Ok, message};
    }

    Result<void> Result<void>::Warning(const std::string &message) {
        return {Status::Warning, message};
    }

    Result<void> Result<void>::Error(const std::string &message, const std::exception_ptr &ex) {
        return {Status::Error, message, ex};
    }

    Result<void> Result<void>::Fatal(const std::string &message, const std::exception_ptr &ex) {
        return {Status::Fatal, message, ex};
    }
}
