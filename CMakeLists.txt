cmake_minimum_required(VERSION 3.18)
project(MCGA)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

set(SANITIZER_COMPILE_OPTIONS -fsanitize=address,undefined -fno-sanitize-recover=undefined)
set(SANITIZER_LINK_OPTIONS -fsanitize=address,undefined)

set(CLANG_WARNINGS
        -Wall
        -Wextra # reasonable and standard
        -Wshadow # warn the user if a variable declaration shadows one from a parent context
        -Wnon-virtual-dtor # warn the user if a class with virtual functions has a non-virtual destructor. This helps
        # catch hard to track down memory errors
        -Wold-style-cast # warn for c-style casts
        -Wcast-align # warn for potential performance problem casts
        -Wunused # warn on anything being unused
        -Woverloaded-virtual # warn if you overload (not override) a virtual function
        -Wpedantic # warn if non-standard C++ is used
        -Wconversion # warn on type conversions that may lose data
        -Wsign-conversion # warn on sign conversions
        -Wnull-dereference # warn if a null dereference is detected
        -Wdouble-promotion # warn if float is implicit promoted to double
        -Wformat=2 # warn on security issues around functions that format output (ie printf)
        -Wimplicit-fallthrough # warn on statements that fallthrough without an explicit annotation
        )
set(GCC_WARNINGS
        ${CLANG_WARNINGS}
        -Wmisleading-indentation # warn if indentation implies blocks where blocks do not exist
        -Wduplicated-cond # warn if if / else chain has duplicated conditions
        -Wduplicated-branches # warn if if / else branches have duplicated code
        -Wlogical-op # warn about logical operations being used where bitwise were probably wanted
        -Wuseless-cast # warn if you perform a cast to the same type
        )

if(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
    add_compile_options(${PROJECT_WARNINGS} -Werror)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options(${PROJECT_WARNINGS} -Werror)
else()
    message(AUTHOR_WARNING "No compiler warnings set for '${CMAKE_CXX_COMPILER_ID}' compiler.")
endif()

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
