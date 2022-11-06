set(FLAG1S __UNIFORM;__FLEXIBLE)
set(FLAG2S __4_NEIGHBOR;__8_NEIGHBOR)

foreach(FLAG1 IN LISTS FLAG1S)
    foreach(FLAG2 IN LISTS FLAG2S)
        add_target(${FLAG1} ${FLAG2})
        target_link_libraries(Judge_${FLAG1}_${FLAG2} MapLib)
    endforeach() 
endforeach()
