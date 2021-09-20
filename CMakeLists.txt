cmake_minimum_required(VERSION 3.18)
project(MCGA)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)

include_directories(third_party/evpp)
include_directories(third_party/mock_glog)
add_library(glog INTERFACE)
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

set(MCGA_threading_examples ON)
set(MCGA_threading_benchmarks ON)
set(MCGA_threading_benchmark_against_evpp ON)
set(MCGA_threading_tests ON)
add_subdirectory(threading)

enable_testing()
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure)
add_dependencies(check mcga_cli_test mcga_matchers_test mcga_proc_test mcga_threading_test)
get_property(mcga_test_check_deps TARGET mcga_test_check PROPERTY MANUALLY_ADDED_DEPENDENCIES)
add_dependencies(check ${mcga_test_check_deps})
add_test(NAME build_all COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target all)
add_test(NAME mcga::cli COMMAND mcga_cli_test --executor=boxed)
add_test(NAME smooth::mcga::cli COMMAND mcga_cli_test --executor=smooth)
add_test(NAME mcga::matchers COMMAND mcga_matchers_test --executor=boxed)
add_test(NAME smooth::mcga::matchers COMMAND mcga_matchers_test --executor=smooth)
add_test(NAME mcga::proc COMMAND mcga_proc_test --executor=boxed)
add_test(NAME smooth::mcga::proc COMMAND mcga_proc_test --executor=smooth)
add_test(NAME mcga::threading COMMAND mcga_threading_test --executor=boxed)
add_test(NAME smooth::mcga::threading COMMAND mcga_threading_test --executor=smooth)
