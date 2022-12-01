// Created by HotariTobu

#include <cassert>
#include <limits>
#include <set>
#include <vector>

#include "../include/searcher.h"

extern double searcher_threshold;

bool CanPass(const std::vector<std::pair<double, Vector3d>> attributes, int width, std::vector<std::vector<int>> index_vector) {
    int points_count = attributes.size();
    int height = points_count / width;
    
    std::map<Point2d, ReducerAttribute> data;

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            Point2d point = {(double)x, (double)y};
            auto&& [z, vector] = attributes[x + y * width];

            ReducerAttribute attribute;
            attribute.z = z;
            attribute.normal_vector = vector;

            data.insert({point, attribute});
        }
    }

    Rectangle rectangle;
    rectangle.min_x = 0;
    rectangle.min_y = 0;
    rectangle.max_x = width - 1;
    rectangle.max_y = height - 1;

    ZMap z_map(data, rectangle);

    auto indices_list = SearchPointGroups(z_map);

    std::set<std::set<int>> result;
    for (auto&& indices : indices_list) {
        std::set<int> index_set(indices.begin(), indices.end());
        result.insert(index_set);
    }

    std::set<std::set<int>> answer;
    for (auto&& indices : index_vector) {
        std::set<int> index_set;
        for (int index : indices) {
            int offset_x = index % width + 1;
            int offset_y = index / width + 1;

            int new_index = z_map.GetIndex(offset_x, offset_y);
            index_set.insert(new_index);
        }
        answer.insert(index_set);
    }

    return result == answer;
}

int main() {
    constexpr double nan = std::numeric_limits<double>::quiet_NaN();

    searcher_threshold = 0.5;

#ifdef __4_NEIGHBOR
// Uniform 4-neighbor code is hear...

    assert(CanPass({
        {  0, {0.1, 0.0, 0.9}}, {  1, {0.0, 1.0, 0.0}}, {  2, {0.0, 0.9, 0.1}}, {  3, {0.1, 1.0, 0.0}},
        {  4, {0.0, 0.0, 1.0}}, {  5, {0.0, 0.0, 1.0}}, {  6, {0.1, 0.0, 1.0}}, {  7, {0.0, 1.0, 0.0}},
        {  8, {0.0, 0.1, 0.9}}, {  9, {0.0, 0.1, 1.0}}, { 10, {0.0, 1.0, 0.0}}, { 11, {0.0, 1.0, 0.1}},
        { 12, {0.0, 0.0, 1.0}}, { 13, {0.1, 0.9, 0.0}}, { 14, {0.0, 0.1, 0.9}}, { 15, {0.1, 0.0, 1.0}},
    }, 4, {
        {
            0, 4, 8, 12, 5, 9, 6,
        },
        {
            1, 2, 10, 3 ,7 ,11,
        },
        {
            13,
        },
        {
            14, 15,
        },
    }));

#elif __8_NEIGHBOR
// Uniform 8-neighbor code is hear...

    assert(CanPass({
        {  0, {0.1, 0.0, 0.9}}, {  1, {0.0, 1.0, 0.0}}, {  2, {0.0, 0.9, 0.1}}, {  3, {0.1, 1.0, 0.0}},
        {  4, {0.0, 0.0, 1.0}}, {  5, {0.0, 0.0, 1.0}}, {  6, {0.1, 0.0, 1.0}}, {  7, {0.0, 1.0, 0.0}},
        {  8, {0.0, 0.1, 0.9}}, {  9, {0.0, 0.1, 1.0}}, { 10, {0.0, 1.0, 0.0}}, { 11, {0.0, 1.0, 0.1}},
        { 12, {0.0, 0.0, 1.0}}, { 13, {0.1, 0.9, 0.0}}, { 14, {0.0, 0.1, 0.9}}, { 15, {0.1, 0.0, 1.0}},
    }, 4, {
        {
            0, 4, 8, 12, 5, 9, 6, 14, 15,
        },
        {
            1, 13, 2, 10, 3 ,7 ,11,
        },
    }));

#endif

}