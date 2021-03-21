cmake_minimum_required(VERSION 3.0.0)
project(skiplist VERSION 0.1.0)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

include_directories(
    src
)

set (SOURCE_FILES
    src/skiplist.cc
)

add_library(skiplistlib OBJECT ${SOURCE_FILES})
add_subdirectory(tests)


