cmake_minimum_required(VERSION 3.14)

project(Editor LANGUAGES CXX)

find_package(Qt6 COMPONENTS Quick REQUIRED)
find_package(Qt6 COMPONENTS Widgets REQUIRED)
#find_package(Qt6 COMPONENTS Multimedia REQUIRED)

#配置源文件
set(resource_files
    main.cpp
    editorqml.h editorqml.cpp
)
#配置资源文件
qt_add_resources(resource_files bigResource.qrc)
#添加文件
add_executable(Editor WIN32 ${resource_files} "icon.rc")

set(INC_DIR
    "${CMAKE_CURRENT_SOURCE_DIR}/../../LiveLinkFreeD"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../DeviceController"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../UserServer"
)

include_directories(${INC_DIR})
target_link_libraries(Editor PRIVATE
    Qt6::Quick
    Qt6::Widgets

    "${JAPP_LIB}/LiveLinkFreeD.lib"
    "${JAPP_LIB}/DeviceController.lib"
    "${JAPP_LIB}/UserServer.lib"
)
