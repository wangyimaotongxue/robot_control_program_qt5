cmake_minimum_required(VERSION 3.10)

project(leju_robot)

# set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD 17)
set(Qt5_DIR "/opt/qt515/lib/cmake/Qt5")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)



set(Qt5_DIR "/opt/qt515/lib/cmake/Qt5")
find_package(Qt5 5.15 REQUIRED COMPONENTS Widgets Core)
find_package(Qt5Widgets REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(QTERMWIDGET REQUIRED qtermwidget5)

include_directories(
    ${CMAKE_SOURCE_DIR}/include
    /usr/include/qtermwidget5
)

find_library(QTERMWIDGET_LIB 
    NAMES qtermwidget5
    PATHS /usr/lib/x86_64-linux-gnu
    REQUIRED
)

add_executable(window_qt
    src/main.cpp
    src/MainWindow.cpp
    src/kuavo_rosbag.cpp
    src/kuavo_real.cpp
    src/kuavo_real_VR.cpp
    src/kuavo_robot_clean.cpp
    src/kuavo_joint_reset_zero.cpp


    include/MainWindow.hpp
    
)

target_link_libraries(window_qt PRIVATE 
    stdc++fs
    Qt5::Widgets
    ${QTERMWIDGET_LIB} 
    stdc++fs 
    Qt5::Core 
)

