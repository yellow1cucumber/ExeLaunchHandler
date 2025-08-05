cmake_minimum_required(VERSION 3.31)
project(pipebridge LANGUAGES CXX)

find_package(Python3 COMPONENTS Interpreter Development REQUIRED)

include_directories(logging pipes python_bridge)

pybind11_add_module(pipebridge module.cpp)

target_link_libraries(pipebridge
    PUBLIC
        ExeLaunchHandler.Logging
        ExeLaunchHandler.Pipes
        ExeLaunchHandler.PyPipeBridge
)

set_target_properties(pipebridge PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)
