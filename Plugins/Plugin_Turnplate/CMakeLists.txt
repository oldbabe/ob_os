cmake_minimum_required(VERSION 3.14)

project(TurnplateDevice LANGUAGES CXX)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}/Plugins)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}/Plugins)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}/Plugins)

find_package(Qt6 COMPONENTS SerialPort REQUIRED)

#配置插件名称
qt_add_plugin(TurnplateDevice
    CLASS_NAME TurnplateDevice
)

#添加资源文件
qt_add_resources(TurnplateDevice resources
    PREFIX "/"
    FILES config.json
)
#添加文件
target_sources(TurnplateDevice PRIVATE
    turnplateplugin.cpp turnplateplugin.h
)

#链接库
target_link_libraries(TurnplateDevice PUBLIC
    Qt6::SerialPort
)
