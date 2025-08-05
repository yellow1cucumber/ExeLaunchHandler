cmake_minimum_required(VERSION 3.31)
project(ExeLaunchHandler.UI)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED
)

include_directories(main_window config_managment_widget pipes_tab)

set(SOURCES
        main_window/mainwindow.cpp
        main_window/mainwindow.h
        main_window/mainwindow.ui
        config_managment_widget/configtab.cpp
        config_managment_widget/configtab.h
        config_managment_widget/configtab.ui
        warnings/ErrorDisplay.cpp
        warnings/ErrorDisplay.h
        splash_screen/SplashScreenWrapper.cpp
        splash_screen/SplashScreenWrapper.h
)

add_library(ExeLaunchHandler.UI SHARED ${SOURCES})

target_link_libraries(ExeLaunchHandler.UI
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        ExeLaunchHandler.Config
        ExeLaunchHandler.Constants
)

target_compile_definitions(ExeLaunchHandler.UI
        PRIVATE ExeLaunchHandler_UI_EXPORTS
)
