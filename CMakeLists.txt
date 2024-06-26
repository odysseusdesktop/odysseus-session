cmake_minimum_required(VERSION 3.14)

project(odysseus-session LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 COMPONENTS Core Gui DBus REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Gui DBus REQUIRED)
find_package(QHotkey REQUIRED)

add_subdirectory(chotkeys)

add_executable(odysseus-session
  main.cpp
  processmanager.h processmanager.cpp
)

target_link_libraries(odysseus-session Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Gui Qt${QT_VERSION_MAJOR}::DBus qhotkey)

install(TARGETS odysseus-session RUNTIME DESTINATION /usr/bin)
install(FILES odysseus.desktop DESTINATION /usr/share/xsessions)
