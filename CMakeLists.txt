cmake_minimum_required(VERSION 3.14)

project(JltApp VERSION 1.9.2.3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/Debug)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Debug)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Debug)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Debug)

    file(
    COPY
        ${CMAKE_CURRENT_SOURCE_DIR}/SDK/opencv/x64/vc16/bin/opencv_world490d.dll
    DESTINATION
        ${EXECUTABLE_OUTPUT_PATH}
    )

elseif (${CMAKE_BUILD_TYPE} STREQUAL "Release")
    set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/Release)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Release)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Release)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Release)

    file(
    COPY
        ${CMAKE_CURRENT_SOURCE_DIR}/SDK/opencv/x64/vc16/bin/opencv_world490.dll
    DESTINATION
        ${EXECUTABLE_OUTPUT_PATH}
    )
else ()
# 其他配置
endif ()

set(SDKDir ${CMAKE_CURRENT_SOURCE_DIR}/SDK)
set(PluginInterfaceDir ${CMAKE_CURRENT_SOURCE_DIR}/JltMoco/include/Interface)

add_subdirectory(Editor)
add_subdirectory(JltMoco)
add_subdirectory(Plugins)


