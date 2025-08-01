//
// Created by User on 27.07.2025.
//

#ifndef PYTHONPIPEREGISTRY_H
#define PYTHONPIPEREGISTRY_H
#include <vector>

#include "PipeDefinition.h"
#include "../../../logging/Logger.h"
#include "../../../results_api/Result.h"
#include "../export.h"

namespace PyBridge::Details {
    class EXELAUNCHHANDLER_PYPIPEBRIDGE_API PythonPipeRegistry {
    public:
        static PythonPipeRegistry &init();

        static PythonPipeRegistry &getInstance();

        PythonPipeRegistry(const PythonPipeRegistry &) = delete;

        PythonPipeRegistry &operator=(const PythonPipeRegistry &) = delete;

        PythonPipeRegistry(PythonPipeRegistry &&) = delete;

        PythonPipeRegistry &operator=(PythonPipeRegistry &&) = delete;

        ~PythonPipeRegistry() = default;

        static ResultAPI::Result<void> loadFromDirectory(const std::string &dir);

        void add(PythonPipeDefinition pipeDesc);

        void clear();

        [[nodiscard]]
        const std::vector<PythonPipeDefinition> &getPipes() const noexcept;

    private:
        PythonPipeRegistry();

        std::vector<PythonPipeDefinition> pipes;
        Logging::Logger &logger;

        inline static std::unique_ptr<PythonPipeRegistry> instance;
        inline static std::once_flag initFlag;
    };
}


#endif //PYTHONPIPEREGISTRY_H
