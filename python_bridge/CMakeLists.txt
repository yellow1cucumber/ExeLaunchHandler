cmake_minimum_required(VERSION 3.15)
project(ExeLaunchHandler.PyPipeBridge)

set(CMAKE_CXX_STANDARD 17)

find_package(Python3 COMPONENTS Interpreter Development REQUIRED)

# Получаем путь до cmake-модулей pybind11
execute_process(
        COMMAND "${Python3_EXECUTABLE}" -m pybind11 --cmakedir
        OUTPUT_VARIABLE PYBIND11_CMAKE_DIR
        OUTPUT_STRIP_TRAILING_WHITESPACE
)

list(APPEND CMAKE_PREFIX_PATH "${PYBIND11_CMAKE_DIR}")
find_package(pybind11 CONFIG REQUIRED)

include_directories(logging results_api pipes)

set(SOURCES
        src/internal/PythonPipeRegistry.cpp
        src/internal/PythonPipeRegistry.h
        src/Adapter.cpp
        src/Adapter.h
        src/export.h
        src/internal/definitions/export_logger.h
        src/internal/definitions/python_pipe.h
        src/internal/definitions/module.cpp
        src/internal/definitions/register_pipe_fun.h
)

add_library(ExeLaunchHandler.PyPipeBridge SHARED ${SOURCES})
target_compile_definitions(ExeLaunchHandler.PyPipeBridge PRIVATE EXELAUNCHHANDLER_PYPIPEBRIDGE_EXPORTS)

target_include_directories(ExeLaunchHandler.PyPipeBridge
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(ExeLaunchHandler.PyPipeBridge
        PUBLIC pybind11::embed
        PUBLIC ExeLaunchHandler.ResultsAPI ExeLaunchHandler.Logging ExeLaunchHandler.Pipes
)
