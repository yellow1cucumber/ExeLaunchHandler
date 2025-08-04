//
// Created by User on 02.08.2025.
//

#ifndef EXPORT_LOGGER_H
#define EXPORT_LOGGER_H

#include <pybind11/pybind11.h>

#include "Logger.h"

namespace py = pybind11;

namespace PyBridge::Definitions {
    inline void export_logger(const py::module_ &m) {
        py::class_<Logging::Logger>(m, "Logger")
            .def_static("debug", &Logging::Logger::Debug, py::arg("message"))
            .def_static("info", &Logging::Logger::Info, py::arg("message"))
            .def_static("warning", &Logging::Logger::Warning, py::arg("message"))
            .def_static("error", &Logging::Logger::Error, py::arg("message"))
            .def_static("critical", &Logging::Logger::Critical, py::arg("message"));
    }
} // namespace PyBridge::Definitions

#endif //EXPORT_LOGGER_H
