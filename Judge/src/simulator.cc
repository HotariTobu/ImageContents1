// Created by 

#include "../include/simulator.h"

#include <math.h>
#include <vector>

int point_number;
std::vector<std::vector<int>> point_distoribution;
double simulator_threshold;

Neighbor Simulate(double value, Neighbor neighbor) {

for(int i; i < 3 ; i++){
    for(int j; j < 3 ; j++){
        point_number = 0;
        if(neighbor.data[i][j] < value || fabs(value - neighbor.data[i][j]) < simulator_threshold){
            point_number += 1; 
        }      
    }
}

#ifdef __UNIFORM
// Uniform code is hear...


#elif __FLEXIBLE
// Flexible code is hear...

#endif
}
