cmake_minimum_required(VERSION 3.14)

project(DeviceApp LANGUAGES CXX)

find_package(Qt6 COMPONENTS Quick REQUIRED)
find_package(Qt6 COMPONENTS Widgets REQUIRED)
find_package(Qt6 COMPONENTS Multimedia REQUIRED)

#配置源文件
set(resource_files
    main.cpp
    editorqml.h editorqml.cpp
)
#配置资源文件
qt_add_resources(resource_files bigResource.qrc)
#添加文件
add_executable(DeviceApp WIN32 ${resource_files} "icon.rc")

target_link_libraries(DeviceApp PRIVATE
    Qt6::Quick
    Qt6::Widgets
    Qt6::Multimedia
    JltMoco
)
