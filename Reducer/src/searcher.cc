// Created by guinpen98

#include "../include/searcher.h"

#include <cmath>
#include <queue>

double searcher_threshold;

constexpr int kgroup_nan = -1;
constexpr int kgroup_null = -2;

bool IsSafe(const int x, const int y, const int width, const int height)
{
    return (x >= 1 && x <= width) && (y >= 1 && y <= height);
}

double CalculateSimilarity(const Vector3d& vec1, const Vector3d& vec2){
    return vec1.Inner(vec2);
}

void FloodFill(const ZMap<ReducerAttribute>& z_map, std::vector<std::vector<int>>& group_map, const int x, const int y){
    std::queue<std::pair<int, int>> q;
    q.push({x, y});
    std::vector<std::pair<int, int>> points{{0, -1}, {-1, 0}, {0, 1}, {1, 0}};

    while(!q.empty()){
        int node_x = q.front().first;
        int node_y = q.front().second;
        q.pop();

        for(int i = 0; i < 4; i++){
            if (!IsSafe(node_x + points[i].second, node_y + points[i].first, z_map.width, z_map.height)){
                continue;
            }
            if(group_map[node_y + points[i].first][node_x + points[i].second] != kgroup_nan){
                continue;
            }
            Vector3d v1 = Vector3d{double(node_x), double(node_y), z_map.z_values[z_map.GetIndex(node_x, node_y)]->z};
            if(CalculateSimilarity(, Vector3d{double(node_x + points[i].second), double(node_y + points[i].first), z_map.z_values[z_map.GetIndex(node_x + points[i].second, node_y + points[i].first)]->z}) < searcher_threshold){
                continue;            
            }
            group_map[node_y +  points[i].first][node_x +  points[i].second] = group_map[node_y][node_x];
            q.push({node_x +  points[i].second, node_y +  points[i].first});
        }
    }
}

std::list<std::list<int>> SearchPointGroups(const ZMap<ReducerAttribute>& z_map) {
    int group_count = 0;
    std::vector<std::vector<int>> group_map(z_map.height + 2, std::vector<int>(z_map.width + 2, kgroup_nan));

    /*for(auto& nan_point_indice : z_map.nan_point_indices){
        Point2d nan_point = z_map.GetPoint(nan_point_indice);
        group_map[nan_point.y][nan_point.x] = kgroup_null;
    }*/

    for(int y = 1; y <= z_map.height; ++y){
        for(int x = 1; x <= z_map.width; ++x){
            int index = z_map.GetIndex(x, y);
            if(z_map.z_values[index] == nullptr){
                group_map[y][x] = kgroup_null;
            }
        }
    }
    for(int y = 1; y <= z_map.height; ++y){
        for(int x = 1; x <= z_map.width; ++x){
            if(group_map[y][x] != kgroup_nan){
                continue;
            }
            group_map[y][x] = group_count;
            FloodFill(z_map, group_map, x, y);
            group_count++;
        }
    }

    std::list<std::list<int>> pointGroups(group_count);
    for(int y = 1; y <= z_map.height; y++){
        for(int x = 1; x <= z_map.width; x++){
            if(group_map[y][x] < 0){
                continue;
            }
            int list_indice = group_map[y][x];
            auto itr = pointGroups.begin();
            for(int i = 0; i < list_indice; ++i){
                ++itr;
            }
            itr->push_back(z_map.GetIndex(x, y));
        }
    }

    return pointGroups;
}