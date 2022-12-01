// Created by HotariTobu

#include "../include/bottom_point_set_remover.h"

#include <vector>

std::list<std::pair<IndexSet, int>> RemoveBottomPointSet(std::list<IndexedPoint2dSet>& leaf_point_set_list) {
    std::list<std::pair<IndexSet, int>> bottom_index_set_list;

    for (auto ite = leaf_point_set_list.cbegin(); ite != leaf_point_set_list.cend();) {
        auto&& point_set = *ite;

        std::vector<int> minus_index_indices;
        for (int i = 0; i < 3; ++i) {
            if (point_set[i].index < 0) {
                minus_index_indices.push_back(i);
            }
        }
        int minus_indices_count = minus_index_indices.size();
        
        if (minus_indices_count > 0) {
            if (minus_indices_count == 1) {
                bottom_index_set_list.push_back({
                    {
                        point_set[0].index,
                        point_set[1].index,
                        point_set[2].index,
                    },
                    minus_index_indices[0]
                });
            }

            ite = leaf_point_set_list.erase(ite);
        }
        else {
            ++ite;
        }
    }

    return bottom_index_set_list;
}