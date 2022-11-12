# cmake_minimum_required(VERSION <specify CMake version here>)
cmake_minimum_required(VERSION 3.3)
project(monitor)

set(CMAKE_CXX_STANDARD 20)

include_directories(./include)

if(CMAKE_HOST_UNIX)
    message("current platform is Unix/Linux, use ansi color char")
    add_library(color STATIC
            src/color/color.cpp)
    set(SYSTEM "WIN32")
elseif(CMAKE_HOST_WIN32)
    message("current platform is Windows, use color 0X")
    add_library(color STATIC
            src/color/color_in_windows.cpp)
    set(SYSTEM "UNIX")
else()
    message("Unknow platform! Use ansi color char")
    add_library(color STATIC
            src/color/color.cpp)
    set(SYSTEM "ELSE")
endif()

add_executable(monitor src/test.cpp)

target_link_libraries(monitor color)
