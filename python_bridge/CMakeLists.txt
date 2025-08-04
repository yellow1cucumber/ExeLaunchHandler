cmake_minimum_required(VERSION 3.31)
project(ExeLaunchHandler.PyPipeBridge)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

# Загрузим pybind11 из GitHub
FetchContent_Declare(
    pybind11
    GIT_REPOSITORY https://github.com/pybind/pybind11.git
    GIT_TAG        v2.11.1  # можно обновить до актуального
)

FetchContent_MakeAvailable(pybind11)

# Твои зависимости
add_subdirectory(definitions)
include_directories(logging results_api pipes)

# Исходники библиотеки
set(SOURCES
    PythonPipeRegistry.cpp
    PythonPipeRegistry.h
    Adapter.cpp
    Adapter.h
    export.h
    definitions/export_logger.h
    definitions/python_pipe.h
    definitions/module.cpp
    definitions/register_pipe_fun.h
)

# Создание библиотеки
add_library(ExeLaunchHandler.PyPipeBridge SHARED ${SOURCES})
target_compile_definitions(ExeLaunchHandler.PyPipeBridge PRIVATE EXELAUNCHHANDLER_PYPIPEBRIDGE_EXPORTS)

# Подключение include'ов
target_include_directories(ExeLaunchHandler.PyPipeBridge
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Линковка с зависимостями
target_link_libraries(ExeLaunchHandler.PyPipeBridge
    PUBLIC
        pybind11::embed
        ExeLaunchHandler.ResultsAPI
        ExeLaunchHandler.Logging
        ExeLaunchHandler.Pipes
)
