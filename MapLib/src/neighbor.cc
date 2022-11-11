// Created by 

#include "../include/neighbor.h"

template<class T>
bool operator==(const Neighbor neighbor1, const Neighbor neighbor2) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (neighbor1.data[i][j] != neighbor2.data[i][j]) {
                return false;
            }
        }
    }

    return true;
}

template<class T>
bool operator!=(const Neighbor neighbor1, const Neighbor neighbor2) {
    return !(neighbor1 == neighbor2);
}
