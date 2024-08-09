cmake_minimum_required(VERSION 3.14)

project(JakaRobot LANGUAGES CXX)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}/Plugins)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}/Plugins)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}/Plugins)

find_package(Qt6 COMPONENTS Network REQUIRED)

#配置插件名称
qt_add_plugin(JakaRobot SHARED
    CLASS_NAME JakaRobot
)

#添加资源文件
qt_add_resources(JakaRobot jsonresources
    PREFIX "/Json"
    FILES JakaRobot.json
)

# 添加JAKA库头文件搜索路径
target_include_directories(JakaRobot PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/inc)

#链接库
target_link_libraries(JakaRobot PRIVATE
    Qt6::Network
    ${CMAKE_CURRENT_SOURCE_DIR}/lib64/jakaAPI.lib
)

#添加文件
target_sources(JakaRobot PRIVATE
    jakaplugin.h jakaplugin.cpp
    jrobot.h jrobot.cpp
    jtrack.h jtrack.cpp
    jroboterrortext.h jroboterrortext.cpp
)

file(
COPY
    ${CMAKE_CURRENT_SOURCE_DIR}/lib64/jakaAPI.dll
DESTINATION
    ${EXECUTABLE_OUTPUT_PATH}
)

