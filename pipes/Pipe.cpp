//
// Created by User on 24.07.2025.
//

#include "Pipe.h"

#include "../logging/Logger.h"

namespace Pipes {
    Pipe::Pipe(std::string name,
                const std::function<ResultAPI::Result<void>()> &action,
                std::string description)
    : name(std::move(name)), description(std::move(description)), action(action) {}

    const std::string &Pipe::GetName() const noexcept {
        return this->name;
    }

    const std::string &Pipe::GetDescription() const noexcept {
        return this->description.empty() ? "No description provided" : this->description;
    }

    ResultAPI::Result<void> Pipe::Run() {
        if (this->onStart) this->onStart();

        this->runStatus.emplace(this->action());

        if (this->runStatus->isError()) {
            if (this->onError) this->onError();
        }

        if (this->runStatus->isWarning()) {
            if (this->onWarning) this->onWarning();
        }

        if (this->onSuccess) this->onSuccess();

        if (this->onFinish) this->onFinish();

        return this->runStatus.value_or(ResultAPI::Result<void>::Error("Failed to assign run result to pipe run status"));
    }
} // Pipes