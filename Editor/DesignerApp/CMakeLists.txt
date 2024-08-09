project(DesignerApp LANGUAGES CXX)

find_package(Qt6 COMPONENTS Quick REQUIRED)
find_package(Qt6 COMPONENTS Widgets REQUIRED)
find_package(Qt6 COMPONENTS Sql REQUIRED)
find_package(Qt6 COMPONENTS Multimedia REQUIRED)

set(resource_files
    main.cpp
    jltscriptconnector.cpp jltscriptconnector.h
    jltscriptdrop.cpp jltscriptdrop.h
    jltscriptnode.cpp jltscriptnode.h
    jltscriptscene.cpp jltscriptscene.h
    jltscriptshape.cpp jltscriptshape.h

)
qt_add_resources(resource_files jltResource.qrc)
#添加文件
add_executable(DesignerApp WIN32 ${resource_files} "icon.rc")

target_link_libraries(DesignerApp PRIVATE
    Qt6::Quick
    Qt6::Widgets
    Qt6::Sql
    Qt6::Multimedia
    JltMoco
)

# 拷贝 ModelFile文件夹下的内容  到 exe目录
execute_process(COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/ModelFile ${EXECUTABLE_OUTPUT_PATH}/ModelFile)
