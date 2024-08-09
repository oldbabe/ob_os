project(CameraDevice LANGUAGES CXX)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}/Plugins)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}/Plugins)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}/Plugins)

find_package(Qt6 COMPONENTS Gui REQUIRED)

#配置插件名称
qt_add_plugin(CameraDevice
    CLASS_NAME CameraDevice
)

#添加资源文件
qt_add_resources(CameraDevice resources
    PREFIX "/"
    FILES config.json
)

target_include_directories(CameraDevice PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/CRSDK)

#添加文件
target_sources(CameraDevice PRIVATE
    cameradefined.h
    cameraplugin.h cameraplugin.cpp
    cameradevice.h cameradevice.cpp
    workerthread.h workerthread.cpp
    propertyvaluetable.h propertyvaluetable.cpp
)


#链接库
target_link_libraries(CameraDevice PUBLIC
    Qt6::Gui
    ${OpenCvLib}
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/Cr_Core.lib
)

file(
COPY
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/Cr_Core.dll
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/monitor_protocol.dll
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/monitor_protocol_pf.dll
DESTINATION
    ${EXECUTABLE_OUTPUT_PATH}
)

file(
COPY
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/CrAdapter/Cr_PTP_IP.dll
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/CrAdapter/Cr_PTP_USB.dll
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/CrAdapter/libusb-1.0.dll
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/CrAdapter/libssh2.dll
DESTINATION
    ${EXECUTABLE_OUTPUT_PATH}/CrAdapter
)
