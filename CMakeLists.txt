# cmake_minimum_required(VERSION <specify CMake version here>)
cmake_minimum_required(VERSION 3.15)
project(monitor)

set(CMAKE_CXX_STANDARD 20)

include_directories(./include)

add_executable(monitor
        src/ProgramMonitor.cpp
        include/ProgramMonitor.h include/MonitorGroup.h src/MonitorGroup.cpp include/tools/SimpleLogger.h include/tools/Timetools.h include/tools/color.h)
