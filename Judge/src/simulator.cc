// Created by yu-getu

#include "../include/simulator.h"

#include <math.h>
#include <vector>

int point_number = 0;
int distribute_point_4 = 0;
double sum_difference_4 = 0;
double sum_difference_8 = 0;
double sum_distribute_difference_4 = 0;
double sum_distribute_difference_8 = 0; 
std::vector<int> distribute_point ;
std::vector<std::vector<double>> distribute_difference;
double simulator_threshold;

Neighbor Simulate(double value, Neighbor neighbor) {
    if (value != 0){
        for(int i; i < 3 ; i++){
            for(int j; j < 3 ; j++){
                point_number += 1;
                if(point_number != 5){
                    if(neighbor.data[i][j] < value || fabs(value - neighbor.data[i][j]) < simulator_threshold){
                        distribute_point.push_back(point_number); //分配する点番号を記憶
                        sum_difference_8 += fabs(value - neighbor.data[i][j]);
                        if (point_number % 2 == 0){
                            distribute_point_4 += 1;
                            sum_difference_4 += fabs(value - neighbor.data[i][j]);
                        }
                        
                    }
                }
            }
        }

        for (int i = 0; i < distribute_point.size(); i++){
            point_number = 0;
            for (int j = 0; j < 3; j++){
                for (int k = 0; k < 3; k++){
                    point_number += 1;
                    if(point_number == distribute_point[k]){
                        distribute_difference[j][k] = fabs(value - neighbor.data[j][k]) - sum_difference_8;
                        sum_distribute_difference_8 += distribute_difference[j][k];
                        if (point_number % 2 == 0){
                            distribute_difference[j][k] = fabs(value - neighbor.data[j][k]) - sum_difference_4;
                            sum_distribute_difference_4 += distribute_difference[j][k];
                        }
                    }
                }
            }
        }   

#ifdef __UNIFORM
// Uniform code is hear...
        for (int i = 0; i < distribute_point.size(); i++){
            point_number = 0;
            for(int j = 0; j < 3 ; j++){
                for(int k = 0; k < 3 ; k++){
                    point_number += 1;
#ifdef __8_NEIGHBOR
// Uniform 8-neighbor code is hear...
                    if(distribute_point[i] == point_number){
                        neighbor.data[j][k] += value/double(distribute_point.size()); 

#elif __4_NEIGHBOR
// Uniform 4-neighbor code is hear...
                        if (point_number % 2 == 0){
                            neighbor.data[j][k] += value/double(distribute_point_4); 
                        }
                    }
                }
            }
        }

#endif

#elif __FLEXIBLE
// Flexible code is hear...
        for (int i = 0; i < distribute_point.size(); i++){
            point_number = 0;
            for(int j = 0; j < 3 ; j++){
                for(int k = 0; k < 3 ; k++){
                    point_number += 1;
#ifdef __8_NEIGHBOR
// Flexible 8-neighbor code is hear...
                    if(distribute_point[i] == point_number){
                        neighbor.data[j][k] += (value * neighbor.data[j][k])/sum_distribute_difference_8; 

#elif __4_NEIGHBOR
// Flexible 4-neighbor code is hear...
                        if (point_number % 2 == 0){
                            neighbor.data[j][k] += (value * neighbor.data[j][k])/sum_distribute_difference_4; 
                        }
                    }
                }
            }
        }

#endif

    neighbor.data[1][1] = 0;
    return neighbor;
    }else{
        return neighbor;
    }

#endif

}
