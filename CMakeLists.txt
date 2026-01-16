cmake_minimum_required(VERSION 3.15)

project(collision-bench
        VERSION 0.1.0
        LANGUAGES CXX
       )

# 17 or newer for better performance features
set(CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) #set to OFF for portability


# adding dependencies
find_package(Eigen3 3.3 REQUIRED NO_MODULE)


# create a library
add_library(collision_lib INTERFACE)
target_include_directories(collision_lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(collision_lib INTERFACE Eigen3::Eigen)

# create an application for benchmarking
add_executable(collision_bench src/main.cpp)
target_include_directories(collision_bench PUBLIC
       $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
       ${EIGEN3_INCLUDE_DIRS}
)
target_link_libraries(collision_bench PUBLIC Eigen3::Eigen)



# compiler warnings
if(MSVC)
       target_compile_options(collision_bench PRIVATE /W4)
else()
       target_compile_options(collision_bench PRIVATE -Wall -Wextra -Wpedantic -Wshadow)
endif()

# enable newer SIMD instruction sets.
target_compile_options(collision_bench PRIVATE -march=native)

# optimization for performance
set_target_properties(collision_bench PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE # Enables LTO (Link Time Optimization)
)

enable_testing()
add_subdirectory(tests)

add_subdirectory(bench)