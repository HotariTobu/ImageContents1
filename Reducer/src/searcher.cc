// Created by guinpen98

#include "../include/searcher.h"

#include <queue>

double searcher_threshold;

constexpr int kgroup_nan = -1;

bool IsSafe(const int x, const int y, const int width, const int height)
{
    return (x >= 1 && x <= width) && (y >= 1 && y <= height);
}

double CalculateSimilarity(const Vector3d& vec1, const Vector3d& vec2){
    return 1 + vec1.Inner(vec2);
}

void FloodFill(const Map2d<std::pair<double, Vector3d>>& map, std::vector<std::vector<int>>& group_map, const int x, const int y){
    std::queue<std::pair<int, int>> q;
    q.push({x, y});

    int row[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
    int col[] = { -1, 0, 1, -1, 1, -1, 0, 1 };

    while(!q.empty()){
        int node_x = q.front().first;
        int node_y = q.front().second;
        q.pop();

        for(int i = 0; i < 8; i++){
            if (!IsSafe(node_x + row[i], node_y + col[i], map.width, map.height)){
                continue;
            }
            if(group_map[node_y + col[i]][node_x + row[i]] != kgroup_nan){
                continue;
            }
            if(CalculateSimilarity(map.data[node_y][node_x].second, map.data[node_y + col[i]][node_x + row[i]].second) < searcher_threshold){
                continue;            
            }
            group_map[node_y + col[i]][node_x + row[i]] = group_map[node_y][node_x];
            q.push({node_x + row[i], node_y + col[i]});
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
            pointGroups[group_map[y][x]].push_back(std::make_pair(Point3d{(double)x, (double)y, map.data[y][x].first}, map.data[y][x].second));
        }
    }

    return pointGroups;
}