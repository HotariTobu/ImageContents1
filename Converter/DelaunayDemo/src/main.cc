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

void WriteSVG(const std::string& path, std::list<std::pair<Point3d*, Point3d*>> edges) {

}

int main() {
    Random random(-100, 100);

    Point3d b0 = {0, 0, random()};
    Point3d b1 = {100, 0, random()};
    Point3d b2 = {0, 100, random()};

    auto [r, d] = MakeRoot(&b0, &b1, &b2);
    std::list<Point3d> points;
    std::list<std::pair<Point3d*, Point3d*>> edges;

    for (int i = 0; i < 100; i++) {
        Point3d p; 
        do {
            p = {random(), random(), random()};
        } while (!r->Contains(&p));
        
        points.push_back(p);
        Point3d* point = &points.back();

        auto deepest = r->FindDeepest(point).lock();

        r->Divide(point);

        int i1 = -1;
        for (int j = 0; j < 3; j++) {
            if (deepest->children[j] == nullptr) {
                i1 = j;
                break;
            }
        }

        if (i1 != -1) {
            int i0 = (i1 + 2) % 3;
            int j1 = deepest->GetNeighborPointIndex(i1);

            auto neighbor = deepest->neighbors[i1].lock();

            edges.push_back(std::make_pair(point, deepest->points[i0]));
            edges.push_back(std::make_pair(point, neighbor->points[j1]));
        }
        else {
            for (int j = 0; j < 3; j++) {
                edges.push_back(std::make_pair(point, deepest->points[1]));
            }
        }

        WriteSVG
    }
}