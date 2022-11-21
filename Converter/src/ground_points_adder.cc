// Created by HotariTobu

#include "../include/ground_points_adder.h"

#include "algorithm"
#include <cmath>
#include <map>
#include <vector>

#include "point3d.h"

double ground_point_threshold;

struct PointSetWithOrigin {
    const IndexedPointSet* point_set;
    Point2d origin;
};

struct PointSetWithEdge {
    const IndexedPointSet* point_set;
    int point_index;
    Vector3d edge;
    bool is_reconnect;
};

std::vector<PointSetWithEdge> GetEdgesLabel(const std::list<PointSetWithOrigin>& point_label, Point2d base_point, double base_z, const std::map<Point2d, Attribute>& data) {
    int edges_count = point_label.size();

    std::map<double, PointSetWithEdge> edges_label;
    for (auto&& with_origin : point_label) {
        Vector2d vector = with_origin.origin - base_point;
        double angle = std::atan2(vector.y, vector.x);

        const IndexedPointSet* point_set = with_origin.point_set;
                
        int j = 0;
        while (*(*point_set)[j] != base_point) {
            ++j;
        }

        Point2d another_point = *(*point_set)[(j + 1) % 3];
        Vector2d edge = another_point - base_point;

        PointSetWithEdge with_edge;
        with_edge.point_set = point_set;
        with_edge.point_index = j;
        with_edge.edge = {
            edge.x,
            edge.y,
            data.at(another_point).z - base_z
        };

        edges_label.insert({angle, with_edge});
    }

    std::vector<PointSetWithEdge> sorted_edges_label;
    for (auto [_, with_edge] : edges_label) {
        sorted_edges_label.push_back(with_edge);
    }

    return sorted_edges_label;
}


bool IsCycled(const std::vector<PointSetWithEdge>& edges_label) {
    int edges_count = edges_label.size();

    for (int i0 = 0; i0 < edges_count; ++i0) {
        int i1 = (i0 + 1) % edges_count;
        
        PointSetWithEdge with_edge_0 = edges_label[i0];
        PointSetWithEdge with_edge_1 = edges_label[i1];

        const IndexedPointSet* point_set_0 = with_edge_0.point_set;
        const IndexedPointSet* point_set_1 = with_edge_1.point_set;

        int point_index_0_in_set = with_edge_0.point_index;
        int point_index_1_in_set = with_edge_1.point_index;

        if (point_set_0[(point_index_0_in_set + 2) % 3] != point_set_1[(point_index_1_in_set + 1) % 3]) {
            return false;
        }
    }

    return true;
}

int SetFlags(std::vector<PointSetWithEdge>& edges_label) {
    int edges_count = edges_label.size();
    int candidates_count = 0;

    for (int i0 = 0; i0 < edges_count; ++i0) {
        int i1 = (i0 + 1) % edges_count;
        
        Vector3d vector = edges_label[i0].edge.Cross(edges_label[i1].edge);
        vector.Normalize();

        double tilt = vector.Inner({0, 0, 1});
        bool is_reconnect = tilt < ground_point_threshold;
        edges_label[i0].is_reconnect = is_reconnect;

        if (is_reconnect) {
            ++candidates_count;
        }
    }

    return candidates_count;
}

std::list<Point3d> AddGroundPoints(const std::map<Point2d, Attribute>& data, const std::list<IndexedPointSet>& point_set_list) {
    int points_count = data.size();

    std::list<PointSetWithOrigin> points_label[points_count];

    for (auto&& point_set : point_set_list) {
        Point2d origin = {0, 0};
        for (int i = 0; i < 3; ++i) {
            origin += *point_set[i];
        }
        origin /= 3;

        PointSetWithOrigin point_set_with_origin = {&point_set, origin};

        for (int i = 0; i < 3; ++i) {
            int point_index = point_set[i].index;
            if (point_index < 0) {
                continue;
            }

            points_label[point_index].push_back(point_set_with_origin);
        }
    }

    std::list<Point3d> additional_points;

    auto points_label_ite = points_label.begin();
    int additional_points_count = 0;
    for (auto [base_point, attribute] : data) {
        auto point_label = *points_label_ite;
        double base_z = data.at(base_point).z;

        auto edges_label = GetEdgesLabel(point_label, base_point, base_z, data);
        if (!IsCycled(edges_label)) {
            ++points_label_ite;
            continue;
        }

        int candidates_count = SetFlags(edges_label);
        if (candidates_count == 0) {
            ++points_label_ite;
            continue;
        }
        
        auto min_ite = std::min_element(edges_label.begin(), edges_label.end(), [](const PointSetWithEdge& l1, const PointSetWithEdge& l2) {
            return l1.edge.z < l2.edge.z;
        });

        int ground_point_index = points_count + points.size();
        Point2d ground_point = {
            base_point.x,
            base_point.y,
            base_z + min_ite->edge.z
        };

        additional_points.push_back(ground_point);

        for (auto&& edge_label : edge_labels) {
            int i0 = edge_label.point_index;
            int i1 = (i0 + 1) % 3;
            int i2 = (i0 + 2) % 3;


        }

        IndexedPoint ground_point_set = {ground_point_index, &additional_points.back()}
        point_set_list.push_back(inde)

        ++points_label_ite;
    }

    for (int i = 0; i < points_count; ++i) {

        for (int j = 0; j < candidates_count; ++j) {
            int candidate = candidates[j];

            int index_set_index = edge_labels[candidate].index_set_index;
            IndexSet index_set = indices[index_set_index];

            if (candidates[(j + candidates_count - 1) % candidates_count] != (candidate + edges_count - 1) % edges_count) {
                IndexSet prev_index_set = {ground_point_index, index_set[i0], index_set[i1]};
                indices.push_back(prev_index_set);
            }

            if (candidates[(j + 1) % candidates_count] != (candidate + 1) % edges_count) {
                IndexSet next_index_set = {ground_point_index, index_set[i2], index_set[i0]};
                indices.push_back(next_index_set);
            }

            indices[index_set_index][i0] = ground_point_index;
        }
    }
}