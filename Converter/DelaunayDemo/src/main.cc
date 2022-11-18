// Created by HotariTobu

#include <list>
#include <random>

#include "../../include/triangle.h"

class Random {
private:
    std::default_random_engine random_engine;
    std::uniform_real_distribution<double> random_distribution;

public:
    Random(double min, double max) {
        std::random_device random_device;
        random_engine = std::default_random_engine(random_device());
        random_distribution = std::uniform_real_distribution<double>(min, max);
    }

    double operator()() {
        return random_distribution(random_engine);
    }
};

int main() {
    Random random(-100, 100);

    Point3d b0 = {0, 0, random()};
    Point3d b1 = {100, 0, random()};
    Point3d b2 = {0, 100, random()};

    auto [r, d] = MakeRoot(&b0, &b1, &b2);
    std::list<Point3d> points;

    for (int i = 0; i < 100; i++) {
        Point3d p; 
        do {
            p = {random(), random(), random()};
        } while (!r->Contains(&p));
        
        points.push_back(p);
        r->Divide(&points.back());
    }
}