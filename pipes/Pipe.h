//
// Created by User on 24.07.2025.
//

#ifndef PIPE_H
#define PIPE_H
#include <functional>
#include <string>

#include "IPipe.h"
#include "export.h"

namespace Pipes {
    class EXELAUNCHHANDLER_PIPES_API Pipe final : public IPipe {
    public:
        explicit Pipe(std::string name,
                      const std::function<ResultAPI::Result<void>()> &action,
                      std::string description);

        Pipe(const Pipe &) = default;

        Pipe &operator=(const Pipe &) = default;

        Pipe(Pipe &&) = default;

        Pipe &operator=(Pipe &&) = default;

        [[nodiscard]]
        const std::string &GetName() const noexcept;

        [[nodiscard]]
        const std::string &GetDescription() const noexcept;

        [[nodiscard]]
        ResultAPI::Result<void> Run() override;

    private:
        std::string name;
        std::string description;
        std::function<ResultAPI::Result<void>()> action;
    };
} // Pipes

#endif //PIPE_H
