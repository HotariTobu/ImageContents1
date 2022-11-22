// Created by HotariTobu

#include <cassert>
#include <ctime>
#include <vector>

#include "../include/randomizer.h"

bool CanPass() {
    constexpr int count = 20;

    std::vector<int> values;

    for (int i = 0; i < count; i++) {
        values.push_back(rand());
    }
    
    std::vector<int> clone = values;

    Randomize(clone);

    return values != clone;
}

int main() {
    srand(std::time(NULL));

    for (int i = 0; i < 5; ++i) {
        assert(CanPass());
    }
}