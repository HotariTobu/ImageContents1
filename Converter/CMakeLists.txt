add_target()

target_link_libraries(Converter GeometryLib)
target_link_libraries(Converter MapLib)
target_link_libraries(Converter MainLib)

set(DEPEND_ON_GEOMEYRYLIB big_triangle_maker;ground_points_adder;randomizer;triangle;wrl_writer)
set(DEPEND_ON_MAPLIB ground_points_adder;maps_combiner;wrl_writer)
set(DEPEND_ON_RANDOMLIB big_triangle_maker;ground_points_adder;maps_combiner;triangle_circle;triangle_contains;triangle;wrl_writer)

foreach(TEST_FILENAME IN LISTS DEPEND_ON_GEOMEYRYLIB)
    target_link_libraries(TEST_${TEST_FILENAME} GeometryLib)
endforeach()

foreach(TEST_FILENAME IN LISTS DEPEND_ON_MAPLIB)
    target_link_libraries(TEST_${TEST_FILENAME} MapLib)
endforeach()

foreach(TEST_FILENAME IN LISTS DEPEND_ON_RANDOMLIB)
    target_link_libraries(TEST_${TEST_FILENAME} RandomLib)
endforeach()

target_sources(TEST_big_triangle_maker PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/triangle.cc)
target_sources(TEST_big_triangle_maker PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/triangle_contains.cc)

target_sources(TEST_ground_points_adder PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/triangle.cc)
target_sources(TEST_ground_points_adder PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/wrl_writer.cc)

target_sources(TEST_triangle_circle PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/circle.cc)
target_sources(TEST_triangle_circle PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/triangle.cc)
target_sources(TEST_triangle_circle PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/triangle_circle.cc)

target_sources(TEST_triangle_contains PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/triangle.cc)
target_sources(TEST_triangle_contains PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/triangle_contains.cc)

target_sources(TEST_triangle PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/circle.cc)
target_sources(TEST_triangle PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/triangle.cc)
target_sources(TEST_triangle PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/triangle_all_leaves_getter.cc)
target_sources(TEST_triangle PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/triangle_circle.cc)
target_sources(TEST_triangle PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/triangle_contains.cc)
target_sources(TEST_triangle PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/triangle_divide.cc)
target_sources(TEST_triangle PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/triangle_find_deepest.cc)
target_sources(TEST_triangle PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/triangle_flip.cc)
target_sources(TEST_triangle PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/triangle_get_neighbor_point_index.cc)