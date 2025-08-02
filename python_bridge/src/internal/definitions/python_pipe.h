//
// Created by User on 02.08.2025.
//

#ifndef PYTHON_PIPE_H
#define PYTHON_PIPE_H
#include <optional>
#include <string>
#include <pybind11/pytypes.h>

#include "src/export.h"

namespace PyBridge::Definitions {

    struct EXELAUNCHHANDLER_PYPIPEBRIDGE_API PythonPipeDefinition {
        std::string name;
        std::optional<std::string> description;
        pybind11::function func;
    };

} // namespace PyBridge::details::definitions

#endif //PYTHON_PIPE_H
