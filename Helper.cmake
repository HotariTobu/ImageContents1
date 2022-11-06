include(GenerateExportHeader)

function(concat)
    
endfunction()


function(add_target)
    if (LIB IN_LIST ARGN)
        set(IS_LIB TRUE)
        list(REMOVE_ITEM ARGN LIB)
    else()
        set(IS_LIB FALSE)
    endif()


    set(TARGET_FLAGS ${ARGN})
    get_filename_component(TARGET_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
    string(JOIN "_" TARGET_NAME ${TARGET_NAME} ${TARGET_FLAGS})


    file(GLOB SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc)
    
    if(${IS_LIB})
        message("lib: ${TARGET_NAME}")

        add_library(${TARGET_NAME} SHARED ${SOURCE_FILES})
        generate_export_header(${TARGET_NAME})

        set(TARGET_INCLUDE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/include)
        target_include_directories(${TARGET_NAME} INTERFACE ${TARGET_INCLUDE_PATH})
        file(COPY ${CMAKE_CURRENT_BINARY_DIR}/${TARGET_NAME}_export.h DESTINATION ${TARGET_INCLUDE_PATH})
    else()
        message("exe: ${TARGET_NAME}")

        add_executable(${TARGET_NAME} ${SOURCE_FILES})
    endif()

    if(TARGET_FLAGS)
        target_compile_definitions(${TARGET_NAME} PUBLIC ${TARGET_FLAGS})
    endif()

    message("\tsrc:")
    foreach(FILE_PATH IN LISTS SOURCE_FILES)
        get_filename_component(FILENAME ${FILE_PATH} NAME)
        message("\t\t${FILENAME}")
    endforeach()
    

    file(GLOB TEST_FILES ${CMAKE_CURRENT_SOURCE_DIR}/test/test_*.cc)
    
    message("\ttest:")
    foreach(TEST_FILE_PATH IN LISTS TEST_FILES)
        get_filename_component(FILENAME_WE ${TEST_FILE_PATH} NAME_WE)
        string(REPLACE "test_" "" FILENAME_WE ${FILENAME_WE})
        string(JOIN "_" TEST_TARGET_NAME TEST_${FILENAME_WE} ${TARGET_FLAGS})

        add_executable(${TEST_TARGET_NAME} ${TEST_FILE_PATH})

        if(${IS_LIB})
            target_link_libraries(${TEST_TARGET_NAME} ${TARGET_NAME})
        else()
            set(SOURCE_FILE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src/${FILENAME_WE}.cc)

            if(EXISTS ${SOURCE_FILE_PATH})
                target_sources(${TEST_TARGET_NAME} PRIVATE ${SOURCE_FILE_PATH})
            endif()
        endif()

        set(TEST_NAME ${TEST_TARGET_NAME}_TEST)
        add_test(NAME ${TEST_NAME} COMMAND $<TARGET_FILE:${TEST_TARGET_NAME}>)

        message("\t\t${TEST_TARGET_NAME} -> ${TEST_NAME}")
    endforeach()
endfunction()