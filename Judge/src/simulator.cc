// Created by guinpen98

#include "../include/simulator.h"

#include <vector>
#include <cmath>

double simulator_threshold;

Neighbor Simulate(double value, Neighbor neighbor) {
    Neighbor simulated_neighbor;
    simulated_neighbor.data[1][1] = 0;

#ifdef __4_NEIGHBOR
// Uniform 4-neighbor code is hear...
    std::vector<std::pair<int, int>> points{{1, 2}, {2, 1}, {1, 0}, {0, 1}};
    const int edge_num = 4;
    simulated_neighbor.data[0][0] = 0;
    simulated_neighbor.data[2][0] = 0;
    simulated_neighbor.data[0][2] = 0;
    simulated_neighbor.data[2][2] = 0;

#elif __8_NEIGHBOR
// Uniform 8-neighbor code is hear...
    std::vector<std::pair<int, int>> points{{0, 1}, {0, 2}, {1, 2}, {2, 2}, {2, 1}, {2, 0}, {1, 0}, {0, 0}};
    const int edge_num = 8;
    
#endif

#ifdef __UNIFORM
// Uniform code is hear...
    int cnt = 0;
    for (int i = 0; i < edge_num; ++i){
        if (neighbor.data[points[i].second][points[i].first] - neighbor.data[1][1] > simulator_threshold){
            simulated_neighbor.data[points[i].second][points[i].first] = 0;
        }else {
            simulated_neighbor.data[points[i].second][points[i].first] = value;
            cnt++;
        }
    }

    for (int i = 0; i < edge_num; ++i){
        simulated_neighbor.data[points[i].second][points[i].first] /= cnt;
    }

#elif __FLEXIBLE
// Flexible code is hear...
    double sum_difference = 0;
    for (int i = 0; i < edge_num; ++i){
        double difference = std::fabs(neighbor.data[points[i].second][points[i].first] - neighbor.data[1][1]);
        if (difference > simulator_threshold){
            simulated_neighbor.data[points[i].second][points[i].first] = std::nan("");
        }else {
            simulated_neighbor.data[points[i].second][points[i].first] = difference;
            sum_difference += difference;
        }
    }
    double sum_easy_of_stay = 0;
    for (int i = 0; i < edge_num; ++i){
        if (std::isnan(simulated_neighbor.data[points[i].second][points[i].first])){
            continue;
        }
        double easy_of_stay = sum_difference - simulated_neighbor.data[points[i].second][points[i].first];;
        simulated_neighbor.data[points[i].second][points[i].first] = easy_of_stay;
        sum_easy_of_stay += easy_of_stay;
    }
    for (int i = 0; i < edge_num; ++i){
        if (std::isnan(simulated_neighbor.data[points[i].second][points[i].first])){
            simulated_neighbor.data[points[i].second][points[i].first] = 0;
        }
        simulated_neighbor.data[points[i].second][points[i].first] /= sum_easy_of_stay;
        simulated_neighbor.data[points[i].second][points[i].first] *= value;
    }

#endif
    return simulated_neighbor;
}