//
// Created by User on 02.08.2025.
//
#include "export_logger.h"
#include "register_pipe_fun.h"
#include "pybind11/pybind11.h"

namespace py = pybind11;

namespace PyBridge::Definitions {

    PYBIND11_MODULE(pipebridge, m) {
        m.doc() = "Python Pipe Bridge Module";
        m.attr("__version__") = "0.1.0";
        m.attr("__author__") = "Nikita Sadovskiy (yellow1cucumber)";
        m.attr("__license__") = "MIT";
        m.attr("__description__") = "A bridge for Python pipes in C++ applications";

        // 0 - Exporting the logger
        export_logger(m);

        // 1 - Registering the pipe function
        export_register_pipe(m);
    }

} // namespace PyBridge::details::definitions