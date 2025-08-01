//
// Created by User on 24.07.2025.
//

#ifndef IPIPE_H
#define IPIPE_H
#include "../results_api/Result.h"

#include "export.h"

namespace Pipes {
    class EXELAUNCHHANDLER_PIPES_API IPipe {
    public:
        virtual ~IPipe() = default;

        [[nodiscard]]
        virtual ResultAPI::Result<void> Run() = 0;

        std::function<void()> onStart;
        std::function<void()> onFinish;

        std::function<void()> onError;
        std::function<void()> onWarning;
        std::function<void()> onSuccess;

    protected:
        std::optional<ResultAPI::Result<void>> runStatus { std::nullopt };
    };
}

#endif //IPIPE_H
