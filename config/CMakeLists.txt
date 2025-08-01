cmake_minimum_required(VERSION 3.16)
project(ExeLaunchHandler.Config)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES
        AppConfig.h
        converting/ISerializer.h
        converting/JsonSerializer.cpp
        converting/JsonSerializer.h
        export.h
        ConfigManager.cpp
        ConfigManager.h
)

add_library(ExeLaunchHandler.Config SHARED ${SOURCES})
target_compile_definitions(ExeLaunchHandler.Config PRIVATE EXELAUNCHHANDLER_CONFIG_EXPORTS)

target_include_directories(ExeLaunchHandler.Config
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/third_party/json
)

target_link_libraries(ExeLaunchHandler.Config
        ExeLaunchHandler.Constants
        ExeLaunchHandler.ResultsAPI
        ExeLaunchHandler.Logging
)
