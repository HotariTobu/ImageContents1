// Created by HotariTobu

#include <filesystem>
#include <fstream>
#include <list>
#include <random>
#include <set>

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

void WriteSVG(const std::string& path, std::set<std::pair<Point2d*, Point2d*>> edges) {
    std::ofstream ofs(path);

    ofs << R"(<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 -70 100 70"><path d=")";

    for (auto edge : edges) {
        Point2d point1 = *edge.first;
        Point2d point2 = *edge.second;

        ofs << 'M' << point1.x << ',' << -point1.y;
        ofs << 'L' << point2.x << ',' << -point2.y;
    }

    ofs << R"(" stroke="gray" stroke-width="0.1"/></svg>)";

    ofs.close();
}

int main() {
    Random random(0, 100);

    const char* directory_name = "DelaunayDemoImages";
    if (!std::filesystem::exists(directory_name)) {
        std::filesystem::create_directory(directory_name);
    }

    Point2d b0 = {0, 0};
    Point2d b1 = {100, 0};
    Point2d b2 = {50, 70};

    auto [r, d] = MakeRoot(&b0, &b1, &b2);
    std::list<Point2d> points;
    
    std::set<std::pair<Point2d*, Point2d*>> edges;
    std::set<std::pair<Point2d*, Point2d*>> flipped_edges = {
        {&b0, &b1},
        {&b0, &b2},
        {&b1, &b2},
    };

    for (int i = 0; i < 100; i++) {
        Point2d p; 
        do {
            p = {random(), random()};
        } while (!r->Contains(&p));
        
        points.push_back(p);
        Point2d* point = &points.back();


        auto deepest = r->FindDeepest(point).lock();

        r->Divide(point);

        std::set<std::pair<Point2d*, Point2d*>> additional_edges;

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

            additional_edges.insert({point, deepest->points[i0]});
            additional_edges.insert({point, neighbor->points[j1]});
        }
        else {
            for (int j = 0; j < 3; j++) {
                additional_edges.insert({point, deepest->points[j]});
            }
        }


        edges = flipped_edges;
        edges.merge(additional_edges);

        char filename[64];

        sprintf(filename, "%s/n%04d.svg", directory_name, i);
        WriteSVG(filename, edges);


        flipped_edges.clear();

        auto leaves = r->GetAllLeaves();

        for (auto&& leaf : leaves) {
            auto accessible_leaf = leaf.lock();

            for (int j = 0; j < 3; ++j) {
                Point2d* p0 = accessible_leaf->points[j];
                Point2d* p1 = accessible_leaf->points[(j + 1) % 3];

                if (*p0 < *p1) {
                    flipped_edges.insert({p0, p1});
                }
                else {
                    flipped_edges.insert({p1, p0});
                }
            }
        }

        sprintf(filename, "%s/l%04d.svg", directory_name, i);
        WriteSVG(filename, flipped_edges);
    }
}