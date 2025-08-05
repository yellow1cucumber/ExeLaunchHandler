#include "Adapter.h"

#include "PythonPipeRegistry.h"

namespace PyBridge {
    void PyBridge::Adapter::Initialize(const char* argv0) {
        if (!interpreter) {
            interpreter = std::make_unique<py::scoped_interpreter>();
        }

		Logging::Logger::Debug("Initializing PythonPipeRegistry");
        Details::PythonPipeRegistry::init();

        this->setExePathToSys(argv0);
		this->importPipeBridgeModule();

		Logging::Logger::Debug("PythonPipeRegistry initialized successfully");
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
        Details::PythonPipeRegistry::getInstance().clear();
		py::module_::import("gc").attr("collect")();

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
    void PyBridge::Adapter::setExePathToSys(const char* argv)
    {
		Logging::Logger::Debug("Setting executable path to sys.path: " + std::string(argv));
        try
        {
            auto sysModule = py::module_::import("sys");
            sysModule.attr("path").attr("insert")(0, py::str(argv));
            Logging::Logger::Debug("Set executable path to sys.path: " + std::string(argv));
        }
        catch (const std::exception& ex)
        {
            Logging::Logger::Critical("Failed to set executable path to sys.path: " + std::string(argv));
            Logging::Logger::Critical(ex.what());
			throw std::runtime_error("Failed to set executable path to sys.path: " + std::string(argv) + " - " + ex.what());
        }
		Logging::Logger::Debug("Executable path set to sys.path: " + std::string(argv));
    }

    void PyBridge::Adapter::importPipeBridgeModule()
    {
        Logging::Logger::Debug("Trying to import Python module: " + std::string(moduleName));
        try
        {
            const py::module_ mainModule{ py::module_::import(this->moduleName) };
        }
        catch (const std::exception& ex)
        {
            Logging::Logger::Critical("Failed to import Python module: " + std::string(moduleName));
            Logging::Logger::Critical(ex.what());
			throw std::runtime_error("Failed to import Python module: " + std::string(moduleName) + " - " + ex.what());
        }
        Logging::Logger::Debug("Python module imported successfully: " + std::string(moduleName));
    }
} // PyBridge
