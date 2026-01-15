include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

# For Windows compatibility
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

add_executable(unit_tests test_aabb.cpp)

target_link_libraries(unit_tests PRIVATE
        gtest_main
        collision_lib
)

# This enables the "Test Explorer" in IDEs like CLion
include(GoogleTest)
gtest_discover_tests(unit_tests)