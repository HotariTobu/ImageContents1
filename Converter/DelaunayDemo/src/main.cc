// Created by HotariTobu

#include <filesystem>
#include <fstream>
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

void WriteSVG(const std::string& path, std::list<std::pair<Point2d*, Point2d*>> edges) {
    std::ofstream ofs(path);

    ofs << R"(<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 100 100"><path d=")";

    for (auto edge : edges) {
        Point2d point1 = *edge.first;
        Point2d point2 = *edge.second;

        ofs << 'M' << point1.x << ',' << point1.y;
        ofs << 'L' << point2.x << ',' << point2.y;
    }

    ofs << R"(" stroke="gray" width="0.1"/></svg>)";

    ofs.close();
}

int main() {
    Random random(-100, 100);

    const char* directory_name = "DelaunayDemoImages";
    if (!std::filesystem::exists(directory_name)) {
        std::filesystem::create_directory(directory_name);
    }

    Point2d b0 = {0, 0};
    Point2d b1 = {100, 0};
    Point2d b2 = {0, 100};

    auto [r, d] = MakeRoot(&b0, &b1, &b2);
    std::list<Point2d> points;
    std::list<std::pair<Point2d*, Point2d*>> edges = {
        {&b0, &b1},
        {&b1, &b2},
        {&b2, &b0},
    };

    for (int i = 0; i < 10; i++) {
        Point2d p; 
        do {
            p = {random(), random()};
        } while (!r->Contains(&p));
        
        points.push_back(p);
        Point2d* point = &points.back();

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
                edges.push_back(std::make_pair(point, deepest->points[j]));
            }
        }

        char filename[64];
        sprintf(filename, "%s/%04d.svg", directory_name, i);

        WriteSVG(filename, edges);
    }
}