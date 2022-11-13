set(FLAG1S __4_NEIGHBOR;__8_NEIGHBOR)

foreach(FLAG1 IN LISTS FLAG1S)
    add_target(${FLAG1})
    target_link_libraries(Reducer_${FLAG1} GeometryLib)
    target_link_libraries(Reducer_${FLAG1} MapLib)
endforeach()

set(DEPEND_ON_GEOMEYRYLIB face_constructor;face_delete_inside_points;face_project_points;normal_vector_getter;searcher)
set(DEPEND_ON_MAPLIB normal_vector_getter;searcher)

foreach(FLAG1 IN LISTS FLAG1S)
    foreach(TEST_FILENAME IN LISTS DEPEND_ON_GEOMEYRYLIB)
        target_link_libraries(TEST_${TEST_FILENAME}_${FLAG1} GeometryLib)
    endforeach()

    foreach(TEST_FILENAME IN LISTS DEPEND_ON_MAPLIB)
        target_link_libraries(TEST_${TEST_FILENAME}_${FLAG1} MapLib)
    endforeach()
endforeach()

set(USE_FACE_GETTER face_constructor;face_delete_inside_points;face_project_points)
set(USE_FACE_CONSTRUCTOR face_delete_inside_points;face_project_points)

foreach(FLAG1 IN LISTS FLAG1S)
    foreach(TEST_FILENAME IN LISTS USE_FACE_GETTER)
        target_sources(TEST_${TEST_FILENAME}_${FLAG1} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/face_getter.cc)
    endforeach()

    foreach(TEST_FILENAME IN LISTS USE_FACE_CONSTRUCTOR)
        target_sources(TEST_${TEST_FILENAME}_${FLAG1} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/face_constructor.cc)
    endforeach()
endforeach()