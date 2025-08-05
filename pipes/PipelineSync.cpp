//
// Created by User on 24.07.2025.
//

#include "PipelineSync.h"

#include "Pipe.h"

namespace Pipes {
    PipelineSync::PipelineSync(bool cancelOnFatal) noexcept
        : cancelOnFatal(cancelOnFatal) {
    }

    ResultAPI::Result<void> PipelineSync::Execute() {
        if (this->onStart) this->onStart();

        for (auto &pipe: this->pipes) {
            Logging::Logger::Info("Start to processing pipe: " + std::string{pipe.GetName()});
            const auto result{pipe.Run()};

            this->logResult(pipe.GetName(), result);

            if (result.isFatal() && this->cancelOnFatal) {
                const auto fatalMessage = "Pipeline execution stopped due to fatal error in pipe: " + pipe.GetName();
                return ResultAPI::Result<void>::Fatal(fatalMessage);
            }
        }

        if (this->onFinish) this->onFinish();

        Logging::Logger::Info("Pipeline finished");
        return ResultAPI::Result<void>::Ok("Pipeline executed successfully.");
    }

    std::future<ResultAPI::Result<void> > PipelineSync::ExecuteAsync() {
        return std::async(std::launch::async, &PipelineSync::Execute, this);
    }

    PipelineSync &PipelineSync::AddStage(std::string name,
                                         std::string description,
                                         std::function<ResultAPI::Result<void>()> action) {
        this->pipes.emplace_back(std::move(name), std::move(action), std::move(description));
        return *this;
    }

    PipelineSync &PipelineSync::AddStage(Pipe pipe) {
        this->pipes.emplace_back(std::move(pipe));
        return *this;
    }

    void PipelineSync::logResult(const std::string &pipeName, const ResultAPI::Result<void>& result) const {
        switch (result.getStatus()) {
            case ResultAPI::Status::Ok:
                Logging::Logger::Info("Pipe successfully processed: " + pipeName);
                break;
            case ResultAPI::Status::Warning:
                Logging::Logger::Warning("Pipe processed with warning: " + pipeName + " - " + result.getMessage());
                break;
            case ResultAPI::Status::Error:
                Logging::Logger::Error("Error while processing pipe: " + pipeName + " - " + result.getMessage());
                break;
            case ResultAPI::Status::Fatal:
                Logging::Logger::Critical("Critical error while processing pipe: " + pipeName + " - " + result.getMessage());
                break;
        }
    }
}
