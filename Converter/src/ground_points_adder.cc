// Created by 

#include "../include/ground_points_adder.h"

#include <algorithm>
#include <cmath>
#include <vector>

double ground_point_threshold;

struct IndexSetWithOrigin {
    int index_set_index;
    Point3d origin;
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

std::vector<IndexSetWithEdge> GetEdges(const PointSet& points, const std::vector<IndexSet>& indices, const std::vector<IndexSetWithOrigin>& point_label, int index) {
    Point3d base_point = points[index];
    int edges_count = point_label.size();

    std::vector<IndexSetWithAngle> labels(edges_count);

    for (int i = 0; i < edges_count; ++i) {
        IndexSetWithOrigin index_set_with_origin = point_label[i];
        Vector3d vector = index_set_with_origin.origin - base_point;

        int index_set_index = index_set_with_origin.index_set_index;
        double angle = std::atan2(vector.y, vector.x);

        labels[i] = {index_set_index, angle};
    }

    std::sort(labels.begin(), labels.end(), [](IndexSetWithAngle l1, IndexSetWithAngle l2) { return l1.angle < l2.angle; });

    std::vector<IndexSetWithEdge> edge_labels(edges_count);

    for (int i = 0; i < edges_count; ++i) {
        int index_set_index = labels[i].index_set_index;
        IndexSet index_set = indices[index_set_index];

        int j = 0;
        while (index_set[j] != index) {
            ++j;
        }

        Point3d another_point = points[index_set[(j + 1) % 3]];
        Vector3d edge = another_point - base_point;

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

Point3d GetGroundPoint(Point3d base_point, const std::vector<IndexSetWithEdge>& edge_labels) {
    int edges_count = edge_labels.size();
    double min_z = edge_labels[0].edge.z;

    for (int i = 1; i < edges_count; ++i) {
        double z = edge_labels[i].edge.z;
        if (min_z > z) {
            min_z = z;
        }
    }

    base_point.z += min_z;
    return base_point;
}

void AddGroundPoints(PointSet& points, std::vector<IndexSet>& indices) {
    int points_count = points.size();
    int index_set_count = indices.size();

    std::vector<IndexSetWithOrigin> point_labels[points_count];
    Point3d origins[index_set_count];

    for (int i = 0; i < index_set_count; ++i) {
        IndexSet index_set = indices[i];

        Point3d origin = {0, 0, 0};
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

        auto edge_labels = GetEdges(points, indices, point_label, i);
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
        
        Point3d ground_point = GetGroundPoint(points[i], edge_labels);
        int ground_point_index = points.size();
        points.push_back(ground_point);

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