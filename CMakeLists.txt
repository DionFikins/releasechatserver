cmake_minimum_required(VERSION 3.12)

project(releasechat VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_COMPILER_IS_GNUCC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
endif()

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
endif()

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools Sql)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.hpp
        mainwindow.ui
        DataBaseConnection.hpp
        DataBaseConnection.cpp
        publicchat.cpp
        publicchat.hpp
        publicchat.ui
        privatechat.cpp
        privatechat.hpp
        privatechat.ui
        ${TS_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(releasechat
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(releasechat SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(releasechat
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

find_package(PostgreSQL REQUIRED)

target_include_directories(releasechat PRIVATE ${PostgreSQL_INCLUDE_DIRS})

target_link_libraries(releasechat PRIVATE Qt6::Sql)
target_link_libraries(releasechat PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(releasechat PRIVATE ${PostgreSQL_LIBRARIES})

set_target_properties(releasechat PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS releasechat
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(releasechat)
endif()
