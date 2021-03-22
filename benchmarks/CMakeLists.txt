cmake_minimum_required(VERSION 3.15-3.18)

add_executable(benchmark skiplist_benchmark_main.cc $<TARGET_OBJECTS:skiplistlib> "${PROJECT_DIR}")