add_target()

target_link_libraries(Converter GeometryLib)
target_link_libraries(Converter DatLib)
# target_link_libraries(Converter MapLib)
target_link_libraries(Converter MainLib)
target_link_libraries(Converter PointTypeLib)

target_link_libraries(TEST_big_triangle_maker GeometryLib)
target_link_libraries(TEST_ground_points_adder GeometryLib)
target_link_libraries(TEST_randomizer GeometryLib)
target_link_libraries(TEST_triangle_circle GeometryLib)
target_link_libraries(TEST_triangle_contains GeometryLib)
target_link_libraries(TEST_triangle_list_leaf_point_set GeometryLib)
target_link_libraries(TEST_triangle GeometryLib)
target_link_libraries(TEST_wrl_writer GeometryLib)

target_link_libraries(TEST_big_triangle_maker RandomLib)

target_link_libraries(TEST_ground_points_adder PointTypeLib)

target_link_libraries(TEST_maps_combiner MapLib)
target_link_libraries(TEST_maps_combiner PointTypeLib)

target_link_libraries(TEST_wrl_writer DatLib)
target_link_libraries(TEST_wrl_writer PointTypeLib)

file(GLOB TRIANGLE_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/triangle*.cc)
foreach(FILE_PATH IN ITEMS ${TRIANGLE_SOURCE_FILES} ${CMAKE_CURRENT_SOURCE_DIR}/src/circle.cc ${CMAKE_CURRENT_SOURCE_DIR}/src/indexed_point.cc)
    target_sources(TEST_big_triangle_maker PRIVATE ${FILE_PATH})
    target_sources(TEST_ground_points_adder PRIVATE ${FILE_PATH})
    target_sources(TEST_triangle_circle PRIVATE ${FILE_PATH})
    target_sources(TEST_triangle_contains PRIVATE ${FILE_PATH})
    target_sources(TEST_triangle_list_leaf_point_set PRIVATE ${FILE_PATH})
    target_sources(TEST_triangle PRIVATE ${FILE_PATH})
endforeach()

target_sources(TEST_ground_points_adder PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/wrl_writer.cc)

target_sources(TEST_triangle_list_leaf_point_set PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/root_maker.cc)

target_sources(TEST_triangle PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/root_maker.cc)

add_subdirectory(DelaunayDemo)