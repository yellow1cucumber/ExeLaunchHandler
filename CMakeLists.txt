cmake_minimum_required(VERSION 3.31)
project(ExeLaunchHandler)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Добавляем переменную для windeployqt
set(WINDEPLOYQT_EXECUTABLE "" CACHE FILEPATH "Path to windeployqt executable")

find_package(Qt5 COMPONENTS
    Core
    Gui
    Widgets
    REQUIRED)

add_subdirectory(results_api)
add_subdirectory(logging)
add_subdirectory(pipes)
add_subdirectory(python_bridge)
add_subdirectory(config)
add_subdirectory(constants)
add_subdirectory(ui)
add_subdirectory(launch)

SET(RESOURCES
    resources/appicon.rc
)

add_executable(ExeLaunchHandler WIN32 main.cpp
    ${RESOURCES}
)

target_link_libraries(ExeLaunchHandler
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets

    ExeLaunchHandler.Pipes
    ExeLaunchHandler.ResultsAPI
    ExeLaunchHandler.Logging
    ExeLaunchHandler.PyPipeBridge
    ExeLaunchHandler.Config
    ExeLaunchHandler.Constants
    ExeLaunchHandler.UI
    ExeLaunchHandler.Launch
)

target_include_directories(ExeLaunchHandler
    PUBLIC
    ${CMAKE_SOURCE_DIR}/third_party/cxxopts
)

add_custom_command(TARGET ExeLaunchHandler POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:ExeLaunchHandler.Pipes>
        $<TARGET_FILE:ExeLaunchHandler.ResultsAPI>
        $<TARGET_FILE:ExeLaunchHandler.Logging>
        $<TARGET_FILE:ExeLaunchHandler.PyPipeBridge>
        $<TARGET_FILE:ExeLaunchHandler.Config>
        $<TARGET_FILE:ExeLaunchHandler.Constants>
        $<TARGET_FILE:ExeLaunchHandler.UI>
        $<TARGET_FILE:ExeLaunchHandler.Launch>
        $<TARGET_FILE_DIR:ExeLaunchHandler>
    COMMENT "Copying dependent DLLs to output directory"
)

if(WINDEPLOYQT_EXECUTABLE)
    add_custom_command(TARGET ExeLaunchHandler POST_BUILD
        COMMAND "${WINDEPLOYQT_EXECUTABLE}" "$<TARGET_FILE:ExeLaunchHandler>"
        COMMENT "Running windeployqt to deploy Qt dependencies"
    )
else()
    message(STATUS "WINDEPLOYQT_EXECUTABLE not set. Skipping Qt deployment.")
endif()