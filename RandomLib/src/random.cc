// Created by HotariTobu

#include "../include/random.h"

Random::Random(double min, double max) {
    std::random_device random_device;
    random_engine = std::default_random_engine(random_device());
    random_distribution = std::uniform_real_distribution<double>(min, max);
}

double Random::operator()() {
    return random_distribution(random_engine);
}