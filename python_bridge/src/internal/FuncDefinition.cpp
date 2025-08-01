//
// Created by User on 27.07.2025.
//

#include <pybind11/pytypes.h>
#include <pybind11/detail/common.h>

#include "PythonPipeRegistry.h"


namespace py = pybind11;

namespace PyBridge::Details {
    PYBIND11_MODULE(pipebridge, m) {
        m.doc() = "Pipe registration bridge";
        m.def("register_pipe",
              [](const std::string &name,
                 py::function func,
                 const std::optional<std::string> &desc) {
                  PythonPipeRegistry::getInstance().add(
                      PythonPipeDefinition{name, desc, std::move(func)}
                  );
              },
              py::arg("name"), py::arg("func"), py::arg("description") = std::nullopt);
    }
}
