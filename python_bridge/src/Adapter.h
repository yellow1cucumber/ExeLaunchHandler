//
// Created by User on 27.07.2025.
//

#ifndef ADAPTER_H
#define ADAPTER_H
#include "../../results_api/Result.h"
#include <pybind11/pybind11.h>
#include <pybind11/embed.h>

#include "../../pipes/Pipe.h"
#include "export.h"
#include "Logger.h"

namespace py = pybind11;

namespace PyBridge {
    class EXELAUNCHHANDLER_PYPIPEBRIDGE_API Adapter {
    public:
        void Initialize(const Logging::Logger &logger);

        void LoadScriptsFromDir(const std::string &dir) const;

        void Finalize();

        static ResultAPI::Result<void> CallPython(const py::function &func);

        std::vector<Pipes::Pipe> GetRegisteredPipes();

        static constexpr const char* moduleName{ "pipebridge" };
    private:
        std::unique_ptr<py::scoped_interpreter> interpreter;
    };
} // PyBridge

#endif //ADAPTER_H
