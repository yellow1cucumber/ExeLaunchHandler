//
// Created by User on 26.07.2025.
//

#include "ResultBase.h"

namespace ResultAPI {
    ResultBase::ResultBase(const Status s, std::string msg, std::exception_ptr ex)
        : status(s), message(std::move(msg)), ex(std::move(ex)) {
    }


    bool ResultBase::isOk() const noexcept {
        return this->status == Status::Ok;
    }

    bool ResultBase::isWarning() const noexcept {
        return this->status == Status::Warning;
    }

    bool ResultBase::isError() const noexcept {
        return this->status == Status::Error;
    }

    bool ResultBase::isFatal() const noexcept {
        return this->status == Status::Fatal;
    }

    ResultAPI::Status ResultBase::getStatus() const noexcept {
        return this->status;
    }

    const std::string &ResultBase::getMessage() const noexcept {
        return this->message;
    }

    const std::exception_ptr &ResultBase::getException() const noexcept {
        return this->ex;
    }
} // ResultAPI