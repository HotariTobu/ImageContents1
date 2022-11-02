add_library(MapLib STATIC
    color.cpp
    converter.cpp
    datetime.cpp
    stringExtension.cpp
)

target_compile_features(MapLib PUBLIC cxx_std_17)
target_include_directories(MapLib INTERFACE ${PROJECT_SOURCE_DIR}/include)