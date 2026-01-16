FetchContent_Declare(
        benchmark
        GIT_REPOSITORY https://github.com/google/benchmark.git
        GIT_TAG        v1.8.3
)
FetchContent_MakeAvailable(benchmark)

add_executable(aabb_bench bench_aabb.cpp)
target_link_libraries(aabb_bench PRIVATE
        benchmark::benchmark_main
        collision_lib
)

# optimization for performance
set_target_properties(aabb_bench PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE # Enables LTO (Link Time Optimization)
)
