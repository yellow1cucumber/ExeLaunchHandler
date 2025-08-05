cmake_minimum_required(VERSION 3.16)
project(ExeLaunchHandler.Constants)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES
        export.h
        WarnLevels.h
        WarnLevels.cpp
        Priority.h
        Priority.cpp
)

add_library(ExeLaunchHandler.Constants SHARED ${SOURCES})
target_compile_definitions(ExeLaunchHandler.Constants PRIVATE EXELAUNCHHANDLER_CONSTANTS_EXPORTS)

target_include_directories(ExeLaunchHandler.Constants
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)