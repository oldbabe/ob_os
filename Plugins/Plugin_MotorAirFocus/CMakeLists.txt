cmake_minimum_required(VERSION 3.14)

project(FocusDevice LANGUAGES CXX)

find_package(Qt6 COMPONENTS SerialPort REQUIRED)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}/Plugins)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}/Plugins)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}/Plugins)
#添加头文件目录
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../Interface)

#配置插件名称
qt_add_plugin(FocusDevice
    CLASS_NAME FocusDevice
)
#添加资源文件
qt_add_resources(FocusDevice jsonresources
    PREFIX "/file"
    FILES config.json
)

#添加文件
target_sources(FocusDevice PRIVATE
    focusplugin.h focusplugin.cpp
)

#链接库
target_link_libraries(FocusDevice PUBLIC
    Qt6::SerialPort
)
