// Created by baconcategg

#include "../include/calculator.h"

#include <algorithm>
#include <cmath>
#include <limits>
#include <vector>

double Calculate(Neighbor neighbor) {
#ifdef __4_NEIGHBOR
// 4-neighbor code is hear...
#ifdef __MIN
    // Min code is hear...
    double min = std::numeric_limits<double>::max();
    for (int i = 0; i < 4; ++i) {
        int x = (-1 + i) % 2;
        int y = (-2 + i) % 2;
        double z;
        if (neighbor.At(x, y, &z)){
            if (z < min) {
                min = z;
            }
        }
    }
    return min;
#elif __MAX
    // Max code is hear...
    double max = std::numeric_limits<double>::min();
    for (int i = 0; i < 4; ++i) {
        int x = (-1 + i) % 2;
        int y = (-2 + i) % 2;
        double z;
        if (neighbor.At(x, y, &z)){
            if (max < z) {
                max = z;
            }
        }
    }
    return max;
#elif __MEAN
    // Mean code is hear...
    double sum = 0;
    int data_number = 0;
    for (int i = 0; i < 4; ++i) {
        int x = (-1 + i) % 2;
        int y = (-2 + i) % 2;
        double z;
        if (neighbor.At(x, y, &z)){
            sum += z;
            data_number++;
        }
    }
    double mean = sum / data_number;
    return mean;
#elif __MEDIAN
    // Median code is hear...
    std::vector<double> v;
    for (int i = 0; i < 4; ++i) {
        int x = (-1 + i) % 2;
        int y = (-2 + i) % 2;
        double z;
        if (neighbor.At(x, y, &z)){
            v.push_back(z);
        }
    }
    double median;
    std::sort(v.begin(), v.end());
    if (v.size() % 2 == 1){
        median = v[v.size() / 2];
    }else{
        median = (v[((v.size()) / 2) - 1] + v[v.size() / 2]) / 2;
    }
    return median;
#endif
#elif __8_NEIGHBOR
// 8-neighbor code is hear...
#ifdef __MIN
    // Min code is hear...
    double min = std::numeric_limits<double>::max();
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            double z;
            if (neighbor.At(i, j, &z)){
                if (z < min) {
                    min = z;
                }
            }
        }
    }
    return min;
#elif __MAX
    // Max code is hear...
    double max = std::numeric_limits<double>::min();
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            double z;
            if (neighbor.At(i, j, &z)){
                if (max < z) {
                    max = z;
                }
            }
        }
    }
    return max;
#elif __MEAN
    // Mean code is hear...
    double sum = 0;
    int data_number = 0;
    for (int i = -1; i <= 1; i++){
        for (int j = -1; j <= 1; j++){
            double z;
            if (neighbor.At(i, j, &z)){
                sum += z;
                data_number++;
            }
        }
    }
    double mean = sum / data_number;
    return mean;
#elif __MEDIAN
    // Median code is hear...
    std::vector<double> v;
    for (int i = -1; i <= 1; i++){
        for (int j =-1; j <= 1; j++){
            double z;
            if (neighbor.At(i, j, &z)){
                v.push_back(z);
            }
        }
    }
    double median;
    std::sort(v.begin(), v.end());
    if (v.size() % 2 == 1){
        median = v[v.size() / 2];
    }else{
        median = (v[((v.size()) / 2) - 1] + v[v.size() / 2]) / 2;
    }
    return median;
#endif
#endif
}
