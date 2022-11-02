cmake_minimum_required(VERSION 3.0.0)
project(ImageContent1 VERSION 0.1.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

include(CTest)
enable_testing()

add_subdirectory(MapLib)

add_subdirectory(Filler)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
