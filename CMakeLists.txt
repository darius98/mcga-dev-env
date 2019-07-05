cmake_minimum_required(VERSION 3.12.1)
project(MCGA)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

include_directories(third_party/evpp)

include_directories(cli/include)
include_directories(matchers/include)
include_directories(proc/include)
include_directories(test/include)
include_directories(threading/include)

add_subdirectory(cli)
add_subdirectory(hpc)
add_subdirectory(matchers)
add_subdirectory(proc)
add_subdirectory(test)
add_subdirectory(threading)
