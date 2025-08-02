//
// Created by User on 02.08.2025.
//

#ifndef REGISTER_PIPE_FUN_H
#define REGISTER_PIPE_FUN_H

#include <pybind11/pybind11.h>

#include "python_pipe.h"
#include "src/internal/PythonPipeRegistry.h"

namespace py = pybind11;

namespace PyBridge::Definitions {
    inline void export_register_pipe(py::module_ &m) {
        m.def("register_pipe",
              [](const std::string &name,
                 py::function& func,
                 const std::optional<std::string> &desc) {
                  Details::PythonPipeRegistry::getInstance().add(
                      PythonPipeDefinition{name, desc, std::move(func)}
                  );
              },
              py::arg("name"),
              py::arg("func"),
              py::arg("description") = std::nullopt);
    }
}

#endif //REGISTER_PIPE_FUN_H
