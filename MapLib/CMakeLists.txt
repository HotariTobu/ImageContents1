get_filename_component(TARGET_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
file(GLOB SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc)

add_library(${TARGET_NAME} SHARED ${SOURCE_FILES})

target_compile_features(${TARGET_NAME} PUBLIC cxx_std_17)
target_include_directories(${TARGET_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

message("lib: " ${TARGET_NAME})
message("\tsrc: ")
foreach(FILE_PATH IN LISTS SOURCE_FILES)
    get_filename_component(FILENAME ${FILE_PATH} NAME)
    message("\t\t" ${FILENAME})
endforeach()