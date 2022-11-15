// Created by guinpen98

#include "../include/searcher.h"

#include <cmath>
#include <queue>

double searcher_threshold;

constexpr int kgroup_nan = -1;

double CalculateSimilarity(const Vector3d& vec1, const Vector3d& vec2){
    return vec1.Inner(vec2);
}

void FloodFill(const Map2d<std::pair<double, Vector3d>>& map, std::vector<std::vector<int>>& group_map, const int x, const int y){
    std::queue<std::pair<int, int>> q;
    q.push({x, y});
    std::vector<std::pair<int, int>> points{{0, -1}, {-1, 0}, {0, 1}, {1, 0}};

    while(!q.empty()){
        int node_x = q.front().first;
        int node_y = q.front().second;
        q.pop();

        for(int i = 0; i < 4; i++){
            if (std::isnan(map.data[node_y + points[i].first][node_x + points[i].second].first)){
                continue;
            }
            if(group_map[node_y + points[i].first][node_x + points[i].second] != kgroup_nan){
                continue;
            }
            if(CalculateSimilarity(map.data[node_y][node_x].second, map.data[node_y + points[i].first][node_x + points[i].second].second) < searcher_threshold){
                continue;            
            }
            group_map[node_y +  points[i].first][node_x +  points[i].second] = group_map[node_y][node_x];
            q.push({node_x +  points[i].second, node_y +  points[i].first});
        }
    }
}

std::vector<PointVectorSet> SearchPointGroups(const Map2d<std::pair<double, Vector3d>>& map) {
    int group_count = 0;
    std::vector<std::vector<int>> group_map(map.height + 2, std::vector<int>(map.width + 2, kgroup_nan));

    for(int y = 1; y <= map.height; y++){
        for(int x = 1; x <= map.width; x++){
            if(group_map[y][x] != kgroup_nan){
                continue;
            }
            group_map[y][x] = group_count;
            FloodFill(map, group_map, x, y);
            group_count++;
        }
    }

    std::vector<PointVectorSet> pointGroups(group_count);
    for(int y = 1; y <= map.height; y++){
        for(int x = 1; x <= map.width; x++){
            pointGroups[group_map[y][x]].push_back(std::make_pair(Point3d{(double)(x - 1), (double)(y - 1), map.data[y][x].first}, map.data[y][x].second));
        }
    }

    return pointGroups;
}