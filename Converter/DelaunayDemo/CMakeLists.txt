add_target()

target_link_libraries(DelaunayDemo GeometryLib)
target_link_libraries(DelaunayDemo RandomLib)

file(GLOB TRIANGLE_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/../src/triangle*.cc)
foreach(FILE_PATH IN LISTS TRIANGLE_SOURCE_FILES)
    target_sources(DelaunayDemo PRIVATE ${FILE_PATH})
endforeach()

target_sources(DelaunayDemo PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../src/circle.cc)
target_sources(DelaunayDemo PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../src/indexed_point.cc)
target_sources(DelaunayDemo PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../src/root_maker.cc)
