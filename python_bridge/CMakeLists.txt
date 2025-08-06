cmake_minimum_required(VERSION 3.31)
project(ExeLaunchHandler.PyPipeBridge)

set(CMAKE_CXX_STANDARD 17)

find_package(Python3 COMPONENTS Interpreter Development REQUIRED)

message(STATUS "Using Python: ${Python3_EXECUTABLE}")
message(STATUS "Python include dir: ${Python3_INCLUDE_DIRS}")
message(STATUS "Python library: ${Python3_LIBRARIES}")

include(FetchContent)
FetchContent_Declare(
        pybind11
        GIT_REPOSITORY https://github.com/pybind/pybind11.git
        GIT_TAG        v2.11.1
)
FetchContent_MakeAvailable(pybind11)

add_subdirectory(definitions)
include_directories(logging results_api pipes)

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

add_library(ExeLaunchHandler.PyPipeBridge SHARED ${SOURCES})
target_compile_definitions(ExeLaunchHandler.PyPipeBridge PRIVATE EXELAUNCHHANDLER_PYPIPEBRIDGE_EXPORTS)

target_include_directories(ExeLaunchHandler.PyPipeBridge
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(ExeLaunchHandler.PyPipeBridge
        PUBLIC
        pybind11::embed
        Python3::Python
        ExeLaunchHandler.ResultsAPI
        ExeLaunchHandler.Logging
        ExeLaunchHandler.Pipes
)

add_custom_command(TARGET ExeLaunchHandler.PyPipeBridge POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${Python3_RUNTIME_LIBRARY}
        $<TARGET_FILE_DIR:ExeLaunchHandler>
)
