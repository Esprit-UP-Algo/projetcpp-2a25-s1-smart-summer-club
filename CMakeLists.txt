cmake_minimum_required(VERSION 3.16)
project(smart-summer-club LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Trouver Qt6 avec les composants requis
find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Sql PrintSupport)

# Qt Charts est optionnel - si disponible, on l'utilise
find_package(Qt6 COMPONENTS Charts QUIET)
set(QT_CHARTS_AVAILABLE ${Qt6Charts_FOUND})

# LinguistTools est optionnel
find_package(Qt6 COMPONENTS LinguistTools QUIET)

qt_standard_project_setup()

# Définir les sources
set(SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    inscription.cpp
    inscription.h
    databasemanager.cpp
    databasemanager.h
    databaseconfigdialog.cpp
    databaseconfigdialog.h
)

# Créer l'exécutable
qt_add_executable(smart-summer-club
    WIN32 MACOSX_BUNDLE
    ${SOURCES}
)

# Ajouter les traductions seulement si LinguistTools est disponible
if(Qt6LinguistTools_FOUND)
    file(GLOB TS_FILES "*.ts")
    if(TS_FILES)
        qt_add_translations(
            TARGETS smart-summer-club
            TS_FILES ${TS_FILES}
        )
    endif()
endif()

# Lier les bibliothèques Qt
target_link_libraries(smart-summer-club
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::Sql
        Qt::PrintSupport
)

# Ajouter Qt Charts seulement si disponible
if(QT_CHARTS_AVAILABLE)
    target_link_libraries(smart-summer-club PRIVATE Qt::Charts)
    target_compile_definitions(smart-summer-club PRIVATE QT_CHARTS_AVAILABLE=1)
    message(STATUS "Qt Charts trouvé - graphiques activés")
else()
    message(WARNING "Qt Charts non trouvé - les graphiques seront désactivés")
    message(STATUS "Pour activer les graphiques, installez Qt Charts via Qt Maintenance Tool")
endif()

# Installation (optionnel)
include(GNUInstallDirs)

install(TARGETS smart-summer-club
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# Script de déploiement
qt_generate_deploy_app_script(
    TARGET smart-summer-club
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})

# Ne pas ajouter mariem si le dossier n'existe pas ou n'a pas de CMakeLists.txt
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/mariem/CMakeLists.txt")
    add_subdirectory(mariem)
endif()
