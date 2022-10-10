cmake_minimum_required(VERSION 3.2)
project(CSVConverter CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

add_subdirectory(src)

add_executable(CSVConverter src/main.cpp)
target_link_libraries(CSVConverter lib)
