cmake_minimum_required(VERSION 3.14)

project(KukaRobot LANGUAGES CXX)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}/Plugins)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}/Plugins)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}/Plugins)

find_package(Qt6 COMPONENTS Network REQUIRED)

#添加头文件目录
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../Interface)

#配置插件名称
qt_add_plugin(KukaRobot
    CLASS_NAME KukaRobot
)

#添加资源文件
qt_add_resources(KukaRobot  jsonresources
    PREFIX "/file"
    FILES KukaRobot.json
)

#添加文件
target_sources(KukaRobot  PRIVATE
    kukaplugin.cpp
    kukaplugin.h
    robotsocket.cpp
    robotsocket.h
    tinyxml2.cpp
    tinyxml2.h
)

#链接库
target_link_libraries(KukaRobot  PUBLIC
    Qt6::Network
)

