add_library(lib STATIC
    color.cpp
    converter.cpp
    datetime.cpp
    stringExtension.cpp
)

target_compile_features(lib PUBLIC cxx_std_17)
target_include_directories(lib INTERFACE ${PROJECT_SOURCE_DIR}/include)