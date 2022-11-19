// Created by HotariTobu

#ifndef __RANDOM_H__
#define __RANDOM_H__

#include <random>

class Random {
private:
    std::default_random_engine random_engine;
    std::uniform_real_distribution<double> random_distribution;

public:
    Random(double min, double max);

    double operator()();
};

#endif // __RANDOM_H__