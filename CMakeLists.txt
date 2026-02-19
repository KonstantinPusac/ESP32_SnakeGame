cmake_minimum_required(VERSION 3.19)
project(SnakeGame LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets SerialPort)

qt_standard_project_setup()

qt_add_executable(SnakeGame
    WIN32 MACOSX_BUNDLE
    main.cpp
    MainSnake.cpp
    MainSnake.h
    MainSnake.ui
    GameController.cpp
    GameController.h
    SnakeGame.cpp
    SnakeGame.h
    MainMenu.cpp
    MainMenu.h
    GameScreen.cpp
    GameScreen.h
    SettingsScreen.cpp
    SettingsScreen.h
    StatsScreen.cpp
    StatsScreen.h
)

target_link_libraries(SnakeGame
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::SerialPort
)

include(GNUInstallDirs)

install(TARGETS SnakeGame
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET SnakeGame
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
