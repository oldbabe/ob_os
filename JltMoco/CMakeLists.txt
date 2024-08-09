cmake_minimum_required(VERSION 3.14)

project(JltMoco LANGUAGES CXX)

find_package(Qt6 COMPONENTS Qml REQUIRED)
find_package(Qt6 COMPONENTS Widgets REQUIRED)
find_package(Qt6 COMPONENTS Network REQUIRED)
find_package(Qt6 COMPONENTS SerialPort REQUIRED)
find_package(Qt6 COMPONENTS Multimedia REQUIRED)

file(GLOB_RECURSE srcs CONFIGURE_DEPENDS src/*.cpp include/*.h)
add_library(JltMoco SHARED ${srcs})
target_include_directories(JltMoco PUBLIC include)
target_compile_definitions(JltMoco PRIVATE DEVICECONTROLLER_LIBRARY)

target_include_directories(JltMoco PRIVATE ${SDKDir}/opencv/include)
if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    set(OpenCvDll ${SDKDir}/opencv/x64/vc16/bin/opencv_world490d.dll)
    set(OpenCvLib ${SDKDir}/opencv/x64/vc16/lib/opencv_world490d.lib)
else ()
    set(OpenCvDll ${SDKDir}/opencv/x64/vc16/bin/opencv_world490.dll)
    set(OpenCvLib ${SDKDir}/opencv/x64/vc16/lib/opencv_world490.lib)
endif ()

#链接库
target_link_libraries(JltMoco PRIVATE
    Qt6::Qml
    Qt6::Widgets
    Qt6::Network
    Qt6::SerialPort
    Qt6::Multimedia
    ${OpenCvLib}
)



