cmake_minimum_required(VERSION 3.12.1)
project(MCGA)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

include_directories(cli/include)
include_directories(threading/include)
include_directories(test/kktest/core/include)
include_directories(test/kktest/extensions/death/include)
include_directories(test/kktest/extensions/matchers/include)

add_subdirectory(threading)
add_subdirectory(cli)
add_subdirectory(test)
