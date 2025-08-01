cmake_minimum_required(VERSION 3.31)
project(ExeLaunchHandler.Pipes)

set(CMAKE_CXX_STANDARD 17)

SET(SOURCES
        IPipe.h
        IPipeline.h

        Pipe.h
        Pipe.cpp

        PipelineSync.cpp
        PipelineSync.h
        export.h
)

add_library(ExeLaunchHandler.Pipes SHARED ${SOURCES})
target_compile_definitions(ExeLaunchHandler.Pipes PRIVATE EXELAUNCHHANDLER_PIPES_EXPORTS)

target_include_directories(ExeLaunchHandler.Pipes
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(ExeLaunchHandler.Pipes
        ExeLaunchHandler.ResultsAPI
        ExeLaunchHandler.Logging
)

