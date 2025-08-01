//
// Created by User on 27.07.2025.
//
#pragma once

#include <optional>
#include <string>
#include <pybind11/pybind11.h>
#include "../export.h"

#ifndef PIPEDEFENITION_H
#define PIPEDEFENITION_H

namespace PyBridge::Details {
    struct EXELAUNCHHANDLER_PYPIPEBRIDGE_API PythonPipeDefinition {
        std::string name;
        std::optional<std::string> description;
        pybind11::function func;
    };
}

#endif //PIPEDEFENITION_H
