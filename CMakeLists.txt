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

set(MCGA_cli_tests ON)
add_subdirectory(cli)

set(MCGA_matchers_tests ON)
add_subdirectory(matchers)

set(MCGA_proc_tests ON)
add_subdirectory(proc)

set(MCGA_test_tests ON)
add_subdirectory(test)

set(MCGA_threading_tests ON)
add_subdirectory(threading)
