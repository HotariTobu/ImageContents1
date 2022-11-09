// Created by baconcategg

#include "../include/calculator.h"

#include <cmath>
#include <limits>

double Calculate(Neighbor neighbor) {
#ifdef __MIN
    // Min code is hear...
    double min = std::numeric_limits<double>::max();
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (!std::isnan(neighbor.data[i][j])){
                if (neighbor.data[i][j] < min) {
                    min = neighbor.data[i][j];
                }
            }
        }
    }
    return min;
#elif __MAX
    // Max code is hear...
    double max = std::numeric_limits<double>::min();
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (!std::isnan(neighbor.data[i][j])){
                if (max < neighbor.data[i][j]) {
                    max = neighbor.data[i][j];
                }
            }
        }
    }
    return max;
#elif __MEAN
    // Mean code is hear...
    double sum = 0;
    int data_number = 0;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (!std::isnan(neighbor.data[i][j])){
                sum += neighbor.data[i][j];
                data_number++;
            }
        }
    }
    double mean = sum / data_number;
    return mean;
#elif __MEDIAN
    // Median code is hear...
    std::vector<double> v;
    for (int i = 0; i < 3; i++){
        for (int j =0; j < 3; j++){
            if (!std::isnan(neighbor.data[i][j])){
                v.push_back(neighbor.data[i][j]);
            }
        }
    }
    double median;
    std::sort(v.begin(), v.end());
    if (v.size() % 2 == 1){
        median = v[(v.size() / 2) + 1];
    }else{
        median = (v[v.size() / 2] + v[(v.size() / 2) + 1]) / 2;
    }
    return median;
#endif
}
