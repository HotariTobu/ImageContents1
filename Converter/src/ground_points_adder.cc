// Created by HotariTobu

#include "../include/ground_points_adder.h"

#include <algorithm>
#include <cmath>

#include "point3d.h"

double ground_point_threshold;

struct IndexSetWithOrigin {
    int index_set_index;
    Point2d origin;
};

struct IndexSetWithAngle {
    int index_set_index;
    double angle;
};

struct IndexSetWithEdge {
    int index_set_index;
    int point_index;
    Vector3d edge;
};

Point3d Merge(Point2d point, double z) {
    return {point.x, point.y, z};
}

std::vector<IndexSetWithEdge> GetEdges(const std::vector<Point2d>& points, const std::vector<double>& z_values, const std::vector<IndexSet>& indices, const std::vector<IndexSetWithOrigin>& point_label, int index) {
    Point2d base_point_2d = points[index];
    int edges_count = point_label.size();

    std::vector<IndexSetWithAngle> labels(edges_count);

    for (int i = 0; i < edges_count; ++i) {
        IndexSetWithOrigin index_set_with_origin = point_label[i];
        Vector2d vector = index_set_with_origin.origin - base_point_2d;

        int index_set_index = index_set_with_origin.index_set_index;
        double angle = std::atan2(vector.y, vector.x);

        labels[i] = {index_set_index, angle};
    }

    std::sort(labels.begin(), labels.end(), [](IndexSetWithAngle l1, IndexSetWithAngle l2) { return l1.angle < l2.angle; });

    Point3d base_point_3d = Merge(base_point_2d, z_values[index]);
    std::vector<IndexSetWithEdge> edge_labels(edges_count);

    for (int i = 0; i < edges_count; ++i) {
        int index_set_index = labels[i].index_set_index;
        IndexSet index_set = indices[index_set_index];

        int j = 0;
        while (index_set[j] != index) {
            ++j;
        }

        int another_index = index_set[(j + 1) % 3];

        Point3d another_point_3d = Merge(points[another_index], z_values[another_index]);        
        Vector3d edge = another_point_3d - base_point_3d;

        edge_labels[i] = {index_set_index, j, edge};
    }

    return edge_labels;
}

bool IsCycled(const std::vector<IndexSet>& indices, const std::vector<IndexSetWithEdge> edge_labels) {
    int edges_count = edge_labels.size();

    for (int i0 = 0; i0 < edges_count; ++i0) {
        int i1 = (i0 + 1) % edges_count;
        
        IndexSetWithEdge edge_0 = edge_labels[i0];
        IndexSetWithEdge edge_1 = edge_labels[i1];

        IndexSet index_set_0 = indices[edge_0.index_set_index];
        IndexSet index_set_1 = indices[edge_1.index_set_index];

        int point_index_0 = edge_0.point_index;
        int point_index_1 = edge_1.point_index;

        if (index_set_0[(point_index_0 + 2) % 3] != index_set_1[(point_index_1 + 1) % 3]) {
            return false;
        }
    }

    return true;
}

std::vector<double> GetTilts(const std::vector<IndexSetWithEdge>& edge_labels) {
    int edges_count = edge_labels.size();
    std::vector<double> tilts(edges_count);

    for (int i0 = 0; i0 < edges_count; ++i0) {
        int i1 = (i0 + 1) % edges_count;
        
        Vector3d vector = edge_labels[i0].edge.Cross(edge_labels[i1].edge);
        vector.Normalize();

        tilts[i0] = vector.Inner({0, 0, 1});
    }

    return tilts;
}

void AddGroundPoints(std::vector<Point2d>& points, std::vector<double>& z_values, std::vector<IndexSet>& indices) {
    int points_count = points.size();
    int index_set_count = indices.size();

    std::vector<IndexSetWithOrigin> point_labels[points_count];

    for (int i = 0; i < index_set_count; ++i) {
        IndexSet index_set = indices[i];

        Point2d origin = {0, 0};
        for (int i = 0; i < 3; ++i) {
            origin += points[index_set[i]];
        }
        origin /= 3;

        IndexSetWithOrigin index_set_with_origin = {i, origin};

        for (int i = 0; i < 3; ++i) {
            point_labels[index_set[i]].push_back(index_set_with_origin);
        }
    }

    for (int i = 0; i < points_count; ++i) {
        auto point_label = point_labels[i];

        auto edge_labels = GetEdges(points, z_values, indices, point_label, i);
        if (!IsCycled(indices, edge_labels)) {
            continue;
        }

        auto tilts = GetTilts(edge_labels);

        std::vector<int> candidates;

        int edges_count = edge_labels.size();
        for (int j = 0; j < edges_count; ++j) {
            if (tilts[j] < ground_point_threshold) {
                candidates.push_back(j);
            }
        }

        int candidates_count = candidates.size();
        if (candidates_count == 0) {
            continue;
        }
        
        auto min_ite = std::min_element(edge_labels.begin(), edge_labels.end(), [](const IndexSetWithEdge& l1, const IndexSetWithEdge& l2) {
            return l1.edge.z < l2.edge.z;
        });
        int ground_point_index = points.size();
        points.push_back(points[i]);
        z_values.push_back(z_values[i] + min_ite->edge.z);

        for (int j = 0; j < candidates_count; ++j) {
            int candidate = candidates[j];

            int i0 = edge_labels[candidate].point_index;
            int i1 = (i0 + 1) % 3;
            int i2 = (i0 + 2) % 3;

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