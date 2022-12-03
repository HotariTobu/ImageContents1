cmake_minimum_required(VERSION 3.13)
project(ImageContent1 VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/${BUILD_TYPE_LOWER})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/${BUILD_TYPE_LOWER})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/${BUILD_TYPE_LOWER})

include(CTest)
enable_testing()

include(Helper.cmake)

add_subdirectory(OperatorLib)
add_subdirectory(GeometryLib)
add_subdirectory(DatLib)
add_subdirectory(MapLib)

add_subdirectory(RandomLib)
add_subdirectory(AttributeLib)
add_subdirectory(MainLib)

add_subdirectory(Converter)
add_subdirectory(Filler)
add_subdirectory(Judge)
add_subdirectory(Reducer)
add_subdirectory(Splitter)

add_subdirectory(options)
add_subdirectory(scripts)

file(MAKE_DIRECTORY ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/source_data)