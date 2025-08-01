//
// Created by User on 27.07.2025.
//

#include "PythonPipeRegistry.h"

#include <filesystem>

namespace py = pybind11;
namespace fs = std::filesystem;

namespace PyBridge::Details {
    PythonPipeRegistry &PythonPipeRegistry::init() {
        std::call_once(initFlag, [&]() {
            instance.reset(new PythonPipeRegistry());
        });
        return *instance;
    }

    PythonPipeRegistry &PythonPipeRegistry::getInstance() {
        if (!instance) {
            throw std::runtime_error("PythonPipeRegistry is not initialized. Call init() first.");
        }
        return *instance;
    }

    ResultAPI::Result<void> PythonPipeRegistry::loadFromDirectory(const std::string &dir) {
        if (!instance) {
            throw std::runtime_error("PythonPipeRegistry is not initialized. Call init() first.");
        }

        instance->clear();

        const py::module_ sys = py::module::import("sys");
        sys.attr("path").cast<py::list>().append(dir);

        for (const auto &entry: fs::directory_iterator{dir}) {
            if (entry.path().extension() == ".py") {
                try {
                    py::module_::import(entry.path().stem().string().c_str());
                } catch (const py::error_already_set &e) {
                    const auto errorMessage = "Failed to import Python module: " + entry.path().string() + " Error: " + std::string(e.what());
                    instance->logger.Error(errorMessage);
                    return ResultAPI::Result<void>::Error(errorMessage, std::current_exception());
                }
            }
        }
        return ResultAPI::Result<void>::Ok();
    }

    void PythonPipeRegistry::add(PythonPipeDefinition pipeDesc) {
        this->pipes.push_back(std::move(pipeDesc));
    }

    void PythonPipeRegistry::clear() {
        this->pipes.clear();
    }

    const std::vector<PythonPipeDefinition> &PythonPipeRegistry::getPipes() const noexcept {
        return this->pipes;
    }

    PythonPipeRegistry::PythonPipeRegistry() : logger(Logging::Logger::getInstance()) {
    }
}
