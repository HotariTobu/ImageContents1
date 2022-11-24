// Created by guinpen98

#include "../include/simulator.h"

#include <vector>
#include <cmath>

double simulator_threshold;

std::array<std::array<double, 3>, 3> Simulate(double value, Neighbor<Attribute> neighbor) {
    std::array<std::array<double, 3>, 3> simulated_neighbor;
    simulated_neighbor[1][1] = 0;

#ifdef __4_NEIGHBOR
// Uniform 4-neighbor code is hear...
    std::vector<std::pair<int, int>> points{{1, 2}, {2, 1}, {1, 0}, {0, 1}};
    const int edge_num = 4;
    simulated_neighbor[0][0] = 0;
    simulated_neighbor[2][0] = 0;
    simulated_neighbor[0][2] = 0;
    simulated_neighbor[2][2] = 0;

#elif __8_NEIGHBOR
// Uniform 8-neighbor code is hear...
    std::vector<std::pair<int, int>> points{{0, 1}, {0, 2}, {1, 2}, {2, 2}, {2, 1}, {2, 0}, {1, 0}, {0, 0}};
    const int edge_num = 8;
    
#endif

    Attribute center_z;
    if (!neighbor.At(0, 0, &center_z)) {
        return simulated_neighbor;
    }

#ifdef __UNIFORM
// Uniform code is hear...
    int cnt = 0;
    for (int i = 0; i < edge_num; ++i){
        Attribute z;
        if (!neighbor.At(points[i].first - 1, points[i].second - 1, &z)) {
            continue;
        }

        if (z.z - center_z.z > simulator_threshold){
            simulated_neighbor[points[i].second][points[i].first] = 0;
        }else {
            simulated_neighbor[points[i].second][points[i].first] = value;
            cnt++;
        }
    }

    for (int i = 0; i < edge_num; ++i){
        simulated_neighbor[points[i].second][points[i].first] /= cnt;
    }

#elif __FLEXIBLE
// Flexible code is hear...
    double sum_difference = 0;
    for (int i = 0; i < edge_num; ++i){
        Attribute z;
        if (!neighbor.At(points[i].first - 1, points[i].second - 1, &z)) {
            continue;
        }

        double difference = z.z - center_z.z;
        if (difference > simulator_threshold){
            simulated_neighbor[points[i].second][points[i].first] = std::nan("");
        }else {
            double unsigned_difference = std::fabs(difference);
            simulated_neighbor[points[i].second][points[i].first] = unsigned_difference;
            sum_difference += unsigned_difference;
        }
    }
    double sum_easy_of_stay = 0;
    for (int i = 0; i < edge_num; ++i){
        if (std::isnan(simulated_neighbor[points[i].second][points[i].first])){
            continue;
        }
        double easy_of_stay = sum_difference - simulated_neighbor[points[i].second][points[i].first];;
        simulated_neighbor[points[i].second][points[i].first] = easy_of_stay;
        sum_easy_of_stay += easy_of_stay;
    }
    for (int i = 0; i < edge_num; ++i){
        if (std::isnan(simulated_neighbor[points[i].second][points[i].first])){
            simulated_neighbor[points[i].second][points[i].first] = 0;
        }
        simulated_neighbor[points[i].second][points[i].first] /= sum_easy_of_stay;
        simulated_neighbor[points[i].second][points[i].first] *= value;
    }

#endif
    return simulated_neighbor;
}