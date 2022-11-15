set(FLAG1S __4_NEIGHBOR;__8_NEIGHBOR)
set(FLAG2S __MIN;__MAX;__MEAN;__MEDIAN)

foreach(FLAG1 IN LISTS FLAG1S)
    foreach(FLAG2 IN LISTS FLAG2S)
        add_target(${FLAG1} ${FLAG2})
        target_link_libraries(Filler_${FLAG1}_${FLAG2} MapLib)
        target_link_libraries(Filler_${FLAG1}_${FLAG2} OptionLib)
    endforeach() 
endforeach()

set(DEPEND_ON_MAPLIB calculator)

foreach(FLAG1 IN LISTS FLAG1S)
endforeach()

foreach(FLAG1 IN LISTS FLAG1S)
    foreach(FLAG2 IN LISTS FLAG2S)
        foreach(TEST_FILENAME IN LISTS DEPEND_ON_MAPLIB)
            target_link_libraries(TEST_${TEST_FILENAME}_${FLAG1}_${FLAG2} MapLib)
        endforeach()
    endforeach() 
endforeach()
