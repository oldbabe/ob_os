project(UpdateApp LANGUAGES CXX)

find_package(Qt6 COMPONENTS Core REQUIRED)
find_package(Qt6 COMPONENTS Quick REQUIRED)
find_package(Qt6 COMPONENTS Widgets REQUIRED)

set(resource_files
    main.cpp
    updatemanager.h updatemanager.cpp
)

#添加资源文件
qt_add_resources(resource_files jltResource.qrc)
#添加文件
add_executable(UpdateApp WIN32 ${resource_files} "icon.rc" )

target_link_libraries(UpdateApp PRIVATE
    Qt6::Core
    Qt6::Quick
    Qt6::Widgets
)

include_directories(${Qt6Gui_PRIVATE_INCLUDE_DIRS})
target_compile_definitions(UpdateApp PRIVATE UpdateAppDir)
