add_target()

target_link_libraries(Converter GeometryLib)
target_link_libraries(Converter MapLib)

set(DEPEND_ON_GEOMEYRYLIB big_triangle_maker;ground_points_adder;randomizer;triangle;wrl_writer)
set(DEPEND_ON_MAPLIB maps_combiner;wrl_writer)

foreach(TEST_FILENAME IN LISTS DEPEND_ON_GEOMEYRYLIB)
    target_link_libraries(TEST_${TEST_FILENAME} GeometryLib)
endforeach()

foreach(TEST_FILENAME IN LISTS DEPEND_ON_MAPLIB)
    target_link_libraries(TEST_${TEST_FILENAME} MapLib)
endforeach()

target_sources(TEST_big_triangle_maker PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/triangle.cc)
target_sources(TEST_big_triangle_maker PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/triangle_circle.cc)

target_sources(TEST_triangle PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/triangle.cc)
target_sources(TEST_triangle PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/triangle_circle.cc)
target_sources(TEST_triangle PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/triangle_contains.cc)
target_sources(TEST_triangle PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/triangle_divide.cc)
target_sources(TEST_triangle PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/triangle_find_deepest.cc)
target_sources(TEST_triangle PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/triangle_flip.cc)