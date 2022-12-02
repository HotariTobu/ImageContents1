// Created by HotariTobu

#include "../include/ground_points_adder.h"

#include "algorithm"
#include <cmath>
#include <map>
#include <vector>

#include "point3d.h"

double ground_point_threshold;

struct PointSetWithOrigin {
    IndexedPoint2dSet* point_set = nullptr;
    Point2d origin;
};

struct PointSetWithEdge {
    IndexedPoint2dSet* point_set = nullptr;
    int point_index_index;
    Vector3d edge;
    bool is_reconnected;
};

std::vector<PointSetWithEdge> GetEdgesLabel(const std::list<PointSetWithOrigin>& point_label, const Point2d* base_point, double base_z, const std::map<Point2d, Attribute>& data) {
    int edges_count = point_label.size();

    std::map<double, PointSetWithEdge> edges_label;
    for (auto&& with_origin : point_label) {
        Vector2d vector = with_origin.origin - *base_point;
        double angle = std::atan2(vector.y, vector.x);

        auto point_set = with_origin.point_set;
                
        int j = 0;
        while ((*point_set)[j].point != base_point) {
            ++j;
        }

        auto another_point = (*point_set)[(j + 1) % 3];
        if (another_point.index < 0) {
            continue;
        }
        
        auto another_point_3d = *(another_point.point);
        Vector2d edge = another_point_3d - *base_point;

        PointSetWithEdge with_edge;
        with_edge.point_set = point_set;
        with_edge.point_index_index = j;
        with_edge.edge = {
            edge.x,
            edge.y,
            data.at(another_point_3d).z - base_z
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
        
        auto&& with_edge_0 = edges_label[i0];
        auto&& with_edge_1 = edges_label[i1];

        auto* point_set_0 = with_edge_0.point_set;
        auto* point_set_1 = with_edge_1.point_set;

        if ((*point_set_0)[(with_edge_0.point_index_index + 2) % 3] != (*point_set_1)[(with_edge_1.point_index_index + 1) % 3]) {
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
        bool is_reconnected = tilt < ground_point_threshold;
        edges_label[i0].is_reconnected = is_reconnected;

        if (is_reconnected) {
            ++candidates_count;
        }
    }

    return candidates_count;
}

std::pair<std::list<std::pair<Point2d, double>>, std::list<IndexSet>> AddGroundPoints(const std::map<Point2d, Attribute>& data, std::list<IndexedPoint2dSet>& point_set_list) {
    int points_count = data.size();

    std::vector<std::list<PointSetWithOrigin>> points_label(points_count);

    for (auto&& point_set : point_set_list) {
        Point2d origin = {0, 0};
        for (int i = 0; i < 3; ++i) {
            origin += *(point_set[i]);
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

    std::list<std::pair<Point2d, double>> additional_points;
    std::list<IndexSet> additional_index_set_list;

    int i = 0;
    int ground_point_index = points_count;
    for (auto&& [base_point, _] : data) {
        auto point_label = points_label[i];
        double base_z = data.at(base_point).z;

        auto edges_label = GetEdgesLabel(point_label, &base_point, base_z, data);
        if (!IsCycled(edges_label)) {
            ++i;
            continue;
        }

        int candidates_count = SetFlags(edges_label);
        if (candidates_count == 0) {
            ++i;
            continue;
        }
        
        auto min_ite = std::min_element(edges_label.begin(), edges_label.end(), [](const PointSetWithEdge& l1, const PointSetWithEdge& l2) {
            return l1.edge.z < l2.edge.z;
        });

        additional_points.push_back({
            {
                base_point.x,
                base_point.y,
            },
            base_z + min_ite->edge.z
        });

        int edges_count = edges_label.size();

        for (int j = 0; j < edges_count; ++j) {
            auto edge_label_0 = edges_label[j];
            auto edge_label_1 = edges_label[(j + 1) % edges_count];

            auto* current_point_set = edge_label_0.point_set;
            int point_index_index_0 = edge_label_0.point_index_index;

            if (edge_label_0.is_reconnected ^ edge_label_1.is_reconnected) {
                IndexSet additional_index_set;
                int point_index_index_2 = (point_index_index_0 + 2) % 3;

                if (edge_label_0.is_reconnected) {
                    additional_index_set = {
                        ground_point_index,
                        (*current_point_set)[point_index_index_2].index,
                        (*current_point_set)[point_index_index_0].index
                    };
                }
                else {
                    additional_index_set = {
                        ground_point_index,
                        (*current_point_set)[point_index_index_0].index,
                        (*current_point_set)[point_index_index_2].index
                    };
                }

                additional_index_set_list.push_back(additional_index_set);
            }

            if (edge_label_0.is_reconnected) {
                (*current_point_set)[point_index_index_0].index = ground_point_index;
            }
        }

        ++i;
        ++ground_point_index;
    }

    return {additional_points, additional_index_set_list};
}