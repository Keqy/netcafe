cmake_minimum_required(VERSION 3.16)

project(netcafe)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(LIB src/filedata.cpp src/types.cpp src/clientmanager.cpp src/table.cpp)
set(SOURCE src/main.cpp)
add_library(netcafeutils STATIC ${LIB})

add_executable(netcafe ${SOURCE})

target_link_libraries(netcafe PRIVATE netcafeutils)
