get_filename_component(TARGET_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)


file(GLOB SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc)

add_library(${TARGET_NAME} SHARED ${SOURCE_FILES})

target_compile_features(${TARGET_NAME} PUBLIC cxx_std_17)
target_include_directories(${TARGET_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)


file(GLOB TEST_FILES ${CMAKE_CURRENT_SOURCE_DIR}/test/*.test)

foreach(FILE_PATH IN LISTS TEST_FILES)
    get_filename_component(FILENAME_WE ${FILE_PATH} NAME_WE)
    set(TEST_NAME TEST_${FILENAME_WE})

    add_executable(${TEST_NAME}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/${FILENAME_WE}.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/test/${FILENAME_WE}.test
    )

    target_compile_features(${TARGET_NAME} PUBLIC cxx_std_17)

    add_test(NAME ${TEST_NAME}_TEST COMMAND $<TARGET_FILE:${TEST_NAME}>)
endforeach()


message("lib: " ${TARGET_NAME})
message("\tsrc:")
foreach(FILE_PATH IN LISTS SOURCE_FILES)
    get_filename_component(FILENAME ${FILE_PATH} NAME)
    message("\t\t" ${FILENAME})
endforeach()