file(GLOB SCRIPT_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*)

list(REMOVE_ITEM SCRIPT_FILES ${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt)

message("scripts:")
foreach(FILE_PATH IN LISTS SCRIPT_FILES)
    get_filename_component(FILENAME ${FILE_PATH} NAME)
    message("\t${FILENAME}")

    configure_file(${FILE_PATH} ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/${FILENAME} COPYONLY)
endforeach()