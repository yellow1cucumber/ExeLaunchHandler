//
// Created by User on 27.07.2025.
//

#include "Adapter.h"

#include "internal/PythonPipeRegistry.h"

namespace PyBridge {
    void Adapter::Initialize() {
        if (!interpreter) {
            interpreter = std::make_unique<py::scoped_interpreter>();
        }
        Details::PythonPipeRegistry::init();
    }

    void Adapter::LoadScriptsFromDir(const std::string &dir) const {
        try {
            Details::PythonPipeRegistry::loadFromDirectory(dir);
        } catch (const std::exception &e) {
            const auto errorMsg = "Failed to load scripts from directory: " + dir + " - " + e.what();
            Logging::Logger::Error(errorMsg);
            throw std::runtime_error(errorMsg);
        }
    }

    void Adapter::Finalize() {
        interpreter.reset();
    }

    ResultAPI::Result<void> Adapter::CallPython(const py::function &func) {
        try {
            py::gil_scoped_acquire gil;
            const py::object ret{func()};

            if (ret.is_none())
                return ResultAPI::Result<void>::Ok();

            if (py::isinstance<py::dict>(ret)) {
                const py::dict result = ret.cast<py::dict>();
                const std::string status{result.contains("status") ? py::str(result["status"]) : "ok"};
                const std::string msg{result.contains("message") ? py::str(result["message"]) : ""};

                if (status == "ok") return ResultAPI::Result<void>::Ok(msg);
                if (status == "warning")return ResultAPI::Result<void>::Warning(msg);
                if (status == "error") return ResultAPI::Result<void>::Error(msg);
                if (status == "fatal") return ResultAPI::Result<void>::Fatal(msg);
            }
            return ResultAPI::Result<void>::Ok("Unknown Python return");
        } catch (const py::error_already_set &e) {
            return ResultAPI::Result<void>::Error(e.what());
        }
    }

    std::vector<Pipes::Pipe> Adapter::GetRegisteredPipes() {
        std::vector<Pipes::Pipe> pipes;

        for (const auto &[name, description, pyFunc]: Details::PythonPipeRegistry::getInstance().getPipes()) {
            pipes.emplace_back(
                name,
                [func = pyFunc]() -> ResultAPI::Result<void> {
                    return CallPython(func);
                },
                description
            );
        }
        return pipes;
    }
} // PyBridge
