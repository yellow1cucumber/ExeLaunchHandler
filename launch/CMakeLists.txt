cmake_minimum_required(VERSION 3.31)
project(ExeLaunchHandler.Launch)

set(CMAKE_CXX_STANDARD 17)

SET(SOURCES
        ProcessLauncher.cpp
        ProcessLauncher.h
        ProcessLauncher.cpp
        ProcessLauncher.h
)

add_library(ExeLaunchHandler.Launch SHARED ${SOURCES})
target_compile_definitions(ExeLaunchHandler.Launch PRIVATE EXELAUNCHHANDLER_LAUNCH_EXPORTS)

target_include_directories(ExeLaunchHandler.Launch
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(ExeLaunchHandler.Launch
        ExeLaunchHandler.Config
        ExeLaunchHandler.ResultsAPI
        ExeLaunchHandler.Logging
)

