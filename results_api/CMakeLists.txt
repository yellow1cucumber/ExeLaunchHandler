cmake_minimum_required(VERSION 3.31)
project(ExeLaunchHandler.ResultsAPI)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES
        Status.h

        ResultBase.cpp
        ResultBase.h

        Result.h
        Result.cpp
        export.h
)

add_library(ExeLaunchHandler.ResultsAPI SHARED ${SOURCES})
target_compile_definitions(ExeLaunchHandler.ResultsAPI PRIVATE EXELAUNCHHANDLER_RESULTSAPI_EXPORTS)

target_include_directories(ExeLaunchHandler.ResultsAPI
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_definitions(ExeLaunchHandler.ResultsAPI PRIVATE RESULTSAPI_EXPORTS)
