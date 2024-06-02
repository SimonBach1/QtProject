cmake_minimum_required(VERSION 3.5)

project(CookieClicker2 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)



set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets LinguistTools REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(TS_FILES CookieClicker2_fr_FR.ts)

set(UI_FILES
    cookieclicker2.ui
    market.ui
    item.ui
)
qt6_wrap_ui(UI_HEADERS ${UI_FILES})

set(PROJECT_SOURCES
        main.cpp
        MoneyManager.h
        ItemManager.h
        clickableImage.h
        clickableImage.cpp
        cookieclicker2.cpp
        cookieclicker2.h
        cookieclicker2.ui
        customdelegate.cpp
        customdelegate.h
        market.ui
        item.ui
        resources.qrc
        ${TS_FILES}
        ${UI_HEADERS}
)

if(Qt${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(CookieClicker2
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET CookieClicker2 APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(CookieClicker2 SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(CookieClicker2
            ${PROJECT_SOURCES}
        )
    endif()

    if(Qt${QT_VERSION_MAJOR} EQUAL 5)
    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
    endif()
endif()

target_link_libraries(CookieClicker2 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(CookieClicker2 PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(CookieClicker2)
endif()
