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

add_executable(ExeLaunchHandler main.cpp)

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
)

target_include_directories(ExeLaunchHandler
        PUBLIC
        ${CMAKE_SOURCE_DIR}/third_party/cxxopts
)

file(GLOB DLLS
        "${CMAKE_BINARY_DIR}/config/ExeLaunchHandler.*.dll"
        "${CMAKE_BINARY_DIR}/logging/ExeLaunchHandler.*.dll"
        "${CMAKE_BINARY_DIR}/pipes/ExeLaunchHandler.*.dll"
        "${CMAKE_BINARY_DIR}/results_api/ExeLaunchHandler.*.dll"
        "${CMAKE_BINARY_DIR}/python_bridge/ExeLaunchHandler.*.dll"
        "${CMAKE_BINARY_DIR}/constants/ExeLaunchHandler.*.dll"
        "${CMAKE_BINARY_DIR}/ui/ExeLaunchHandler.*.dll"
)

add_custom_command(TARGET ExeLaunchHandler POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${DLLS}
        $<TARGET_FILE_DIR:ExeLaunchHandler>
        COMMENT "Copying DLLs to output directory"
)

if(WINDEPLOYQT_EXECUTABLE)
    add_custom_command(TARGET ExeLaunchHandler POST_BUILD
            COMMAND "${WINDEPLOYQT_EXECUTABLE}" "$<TARGET_FILE:ExeLaunchHandler>"
            COMMENT "Running windeployqt to deploy Qt dependencies"
    )
else()
    message(STATUS "WINDEPLOYQT_EXECUTABLE not set. Skipping Qt deployment.")
endif()
