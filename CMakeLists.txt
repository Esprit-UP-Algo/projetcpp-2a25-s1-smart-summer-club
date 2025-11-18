cmake_minimum_required(VERSION 3.19)
project(smart-summer-club LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets LinguistTools Sql Charts)

qt_standard_project_setup()

qt_add_executable(smart-summer-club
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    inscription.cpp
    inscription.h
    databasemanager.cpp
    databasemanager.h
)

qt_add_translations(
    TARGETS smart-summer-club
    TS_FILES smart-summer-club_en_GB.ts
)

target_link_libraries(smart-summer-club
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::Sql
        Qt::Charts
)

include(GNUInstallDirs)

install(TARGETS smart-summer-club
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET smart-summer-club
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
add_subdirectory(mariem)
