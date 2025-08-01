//
// Created by User on 24.07.2025.
//

#ifndef PIPELINESYNC_H
#define PIPELINESYNC_H
#include <future>

#include "IPipeline.h"
#include "Pipe.h"
#include "../logging/Logger.h"
#include "export.h"

namespace Pipes {
    class EXELAUNCHHANDLER_PIPES_API PipelineSync final : public IPipeline {
    public:
        explicit PipelineSync(bool cancelOnFatal) noexcept;

        ~PipelineSync() noexcept override = default;

        [[nodiscard]]
        ResultAPI::Result<void> Execute() override;

        [[nodiscard]]
        std::future<ResultAPI::Result<void>> ExecuteAsync() override;

        [[nodiscard]]
        PipelineSync &AddStage(std::string name,
                               std::optional<std::string> description,
                               std::function<ResultAPI::Result<void>()> action);

        [[nodiscard]]
        PipelineSync &AddStage(Pipe pipe);

    private:
        std::shared_ptr<Logging::Logger> logger;
        bool cancelOnFatal;

        void logResult(const std::string &pipeName, const ResultAPI::Result<void> &result) const;
    };
}

#endif //PIPELINESYNC_H
