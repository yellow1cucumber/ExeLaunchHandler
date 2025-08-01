cmake_minimum_required(VERSION 3.31)
project(ExeLaunchHandler.Logging)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES
        Logger.cpp
        Logger.h

        log_message_builders/LineMessageBuilder.cpp
        log_message_builders/LineMessageBuilder.h
        export.h
)

add_library(ExeLaunchHandler.Logging SHARED ${SOURCES})
target_compile_definitions(ExeLaunchHandler.Logging PRIVATE EXELAUNCHHANDLER_LOGGING_EXPORTS)

target_include_directories(ExeLaunchHandler.Logging
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)