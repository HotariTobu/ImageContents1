get_filename_component(TARGET_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
file(GLOB SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc)

add_executable(${TARGET_NAME} ${SOURCE_FILES})
target_link_libraries(${TARGET_NAME} MapLib)

message("exe: " ${TARGET_NAME})
message("\tsrc: ")
foreach(FILE_PATH IN LISTS SOURCE_FILES)
    get_filename_component(FILENAME ${FILE_PATH} NAME)
    message("\t\t" ${FILENAME})
endforeach()