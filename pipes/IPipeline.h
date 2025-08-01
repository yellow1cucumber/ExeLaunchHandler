//
// Created by User on 24.07.2025.
//

#ifndef PIPELINE_H
#define PIPELINE_H
#include <functional>

#include "Pipe.h"
#include "export.h"

namespace Pipes {

class EXELAUNCHHANDLER_PIPES_API IPipeline {
public:
    virtual ~IPipeline() noexcept = default;

    [[nodiscard]]
    virtual ResultAPI::Result<void> Execute() = 0;

    [[nodiscard]]
    virtual std::future<ResultAPI::Result<void>> ExecuteAsync() = 0;

    std::function<void()> onStart;
    std::function<void()> onFinish;

protected:
    std::vector<Pipe> pipes;
};
} // Pipes

#endif //PIPELINE_H
