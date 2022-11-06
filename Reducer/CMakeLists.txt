add_target()

target_link_libraries(Reducer GeometryLib)
target_link_libraries(Reducer MapLib)

set(FLAG1S __4_NEIGHBOR;__8_NEIGHBOR)

foreach(FLAG1 IN LISTS FLAG1S)
    add_target(${FLAG1})
    target_link_libraries(Reducer_${FLAG1} GeometryLib)
    target_link_libraries(Reducer_${FLAG1} MapLib)
endforeach()
