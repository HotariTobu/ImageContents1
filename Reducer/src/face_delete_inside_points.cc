// Created by guinpen98

#include "../include/face.h"

#include <cmath>
#include <map>
#include <vector>

bool IsDent(Point2d p0, Point2d p1, Point2d p2) {
    Vector2d&& v1 = p1 - p0;
    Vector2d&& v2 = p2 - p0;
    double&& cross_product = v1.Cross(v2);
    return cross_product <= 0;
}

std::list<Point2d> Face::DeleteInsidePoints() {
    int points_count = _points.size();
    if (points_count <= 3) {
        return {};
    }

    Point2d origin_2d = {
        _origin.x,
        _origin.y
    };

    std::map<std::pair<double, double>, const std::pair<Point2d, double *>*> sorted_points;

    for (auto&& point : _points) {
        Vector2d vector = point.first - origin_2d;
        double angle = std::atan2(vector.y, vector.x);
        double length = vector.Length();
        sorted_points.insert({{angle, length}, &point});
    }

    std::vector<std::pair<int, const std::pair<Point2d, double *>*>> iterator(points_count);

    auto ite = sorted_points.cbegin();
    for (int i = 0; i < points_count; ++i, ++ite) {
        iterator[i] = {i + 1, ite->second};
    }
    iterator[points_count - 1].first = 0;

    sorted_points.clear();

    int bottom_index = 0;
    for (int i = 1; i < points_count; ++i) {
        if (iterator[bottom_index].second->first.y > iterator[i].second->first.y) {
            bottom_index = i;
        }
    }

    std::list<Point2d> deleted_points;
    
    auto current = &iterator[bottom_index];
    int deleted_count = 0;
    while (true) {
        auto next = &iterator[current->first];
        auto next_next = &iterator[next->first];

        if (current == next_next) { 
            break;
        }

        if (IsDent(current->second->first, next->second->first, next_next->second->first)) {
            deleted_points.push_back(next->second->first);

            current->first = next->first;
            ++deleted_count;

            next = next_next;
        }

        current = next;

        if (current->first == bottom_index) {
            if (deleted_count == 0) {
                break;
            }

            deleted_count = 0;
        }
    }

    std::list<std::pair<Point2d, double *>> new_points;

    bottom_index = current->first;
    do {
        new_points.push_back(*current->second);
        current = &iterator[current->first];
    } while (current->first != bottom_index);

    _points = new_points;
    return deleted_points;
}


