set(FLAG1S __4_NEIGHBOR;__8_NEIGHBOR)

foreach(FLAG1 IN LISTS FLAG1S)
    add_target(${FLAG1})
    target_link_libraries(Reducer_${FLAG1} GeometryLib)
    target_link_libraries(Reducer_${FLAG1} DatLib)
    # target_link_libraries(Reducer_${FLAG1} MapLib)
    target_link_libraries(Reducer_${FLAG1} MainLib)
    target_link_libraries(Reducer_${FLAG1} PointTypeLib)
    
    target_link_libraries(TEST_face_constructor_${FLAG1} GeometryLib)
    target_link_libraries(TEST_face_delete_inside_points_${FLAG1} GeometryLib)
    target_link_libraries(TEST_face_project_points_${FLAG1} GeometryLib)
    target_link_libraries(TEST_normal_vector_getter_${FLAG1} GeometryLib)
    target_link_libraries(TEST_searcher_${FLAG1} GeometryLib)
    
    target_link_libraries(TEST_normal_vector_getter_${FLAG1} DatLib)
    target_link_libraries(TEST_normal_vector_getter_${FLAG1} PointTypeLib)

    target_link_libraries(TEST_searcher_${FLAG1} DatLib)
    target_link_libraries(TEST_searcher_${FLAG1} MainLib)
    target_link_libraries(TEST_searcher_${FLAG1} PointTypeLib)

    target_sources(TEST_face_constructor_${FLAG1} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/face_getter.cc)
    target_sources(TEST_face_delete_inside_points_${FLAG1} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/face_getter.cc)
    target_sources(TEST_face_project_points_${FLAG1} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/face_getter.cc)
    
    target_sources(TEST_face_delete_inside_points_${FLAG1} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/face_constructor.cc)
    target_sources(TEST_face_project_points_${FLAG1} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/face_constructor.cc)
endforeach()
