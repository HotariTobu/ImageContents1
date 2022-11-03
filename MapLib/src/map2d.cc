// Created by 

#include "../include/map2d.h"

template<class T>
bool operator==(const Map2d<T>& map1, const Map2d<T>& map2) {
    return
        map1.x == map2.x &&
        map1.y == map2.y &&
        map1.width == map2.width &&
        map1.height == map2.height &&
        map1.data == map2.data;
}

template<class T>
bool operator!=(const Map2d<T>& map1, const Map2d<T>& map2) {
    return !(map1 == map2);
}
