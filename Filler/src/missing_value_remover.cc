// Created by HotariTobu

#include "../include/missing_value_remover.h"

#define MISSING_VALUE_THRESHOLD -9999

void RemoveMissingValue(std::map<Point2d, double>& data) {
    auto ite = data.cbegin();
    while (ite != data.cend()) {
        if (ite->second < MISSING_VALUE_THRESHOLD) {
            ite = data.erase(ite);
        }
        else {
            ++ite;
        }
    }
}