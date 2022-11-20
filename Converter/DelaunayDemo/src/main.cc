// Created by HotariTobu

#include <array>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <list>
#include <map>
#include <random>
#include <set>
#include <stack>
#include <string>
#include <thread>

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

std::list<Point2d*> GetUniquePoints(const std::weak_ptr<Triangle>& root_triangle) {
    std::set<Point2d*> points;
    
    auto leaves = root_triangle.lock()->GetAllLeaves();

    for (auto&& leaf : leaves) {
        auto accessible_leaf = leaf.lock();

        for (int j = 0; j < 3; ++j) {
            Point2d* p0 = accessible_leaf->points[j];
            Point2d* p1 = accessible_leaf->points[(j + 1) % 3];

            points.insert(p0);
            points.insert(p1);
        }
    }

    return std::list(points.begin(), points.end());
}

std::set<std::pair<Point2d*, Point2d*>> GetUniqueLeavesEdges(const std::weak_ptr<Triangle>& root_triangle) {
    std::set<std::pair<Point2d*, Point2d*>> edges;
    
    auto leaves = root_triangle.lock()->GetAllLeaves();

    for (auto&& leaf : leaves) {
        auto accessible_leaf = leaf.lock();

        for (int j = 0; j < 3; ++j) {
            Point2d* p0 = accessible_leaf->points[j];
            Point2d* p1 = accessible_leaf->points[(j + 1) % 3];

            if (*p0 < *p1) {
                edges.insert({p0, p1});
            }
            else {
                edges.insert({p1, p0});
            }
        }
    }

    return edges;
}

template<typename T>
int GetIndex(const T& container, typename T::value_type element) {
    int index = 0;
    for (auto iterator = std::begin(container); *iterator != element; ++iterator, ++index);
    return index;
}

void WriteSVG(const std::string& path, const std::set<std::pair<Point2d*, Point2d*>>& edges) {
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

void DrawGraphInHTML(const std::string& path, const std::list<Point2d>& points, const std::set<std::pair<Point2d*, Point2d*>>& edges, const std::weak_ptr<Triangle>& root_triangle) {
    struct Utility {
        static std::string GetLabel(const std::list<Point2d>& points, const std::weak_ptr<Triangle>& triangle) {
            std::set<int> indices;
            for (Point2d* point : triangle.lock()->points) {
                indices.insert(GetIndex(points, *point));
            }

            std::string label;
            for (int index : indices) {
                label += "-p";
                label += std::to_string(index);
            }

            return label.substr(1);
        }
    };

    std::ofstream ofs(path);

    ofs << R"(<script src="https://cdnjs.cloudflare.com/ajax/libs/mermaid/9.2.2/mermaid.min.js" integrity="sha512-IX+bU+wShHqfqaMHLMrtwi4nK6W/Z+QdZoL4kPNtRxI2wCLyHPMAdl3a43Fv1Foqv4AP+aiW6hg1dcrTt3xc+Q==" crossorigin="anonymous" referrerpolicy="no-referrer"></script>
<script>
    mermaid.initialize({ startOnLoad: true });
</script>
<svg viewBox="-5 -75 110 80">
    <path d=")";

    for (auto edge : edges) {
        Point2d point1 = *edge.first;
        Point2d point2 = *edge.second;

        ofs << 'M' << point1.x << ',' << -point1.y;
        ofs << 'L' << point2.x << ',' << -point2.y;
    }

    ofs << R"(" stroke="gray" stroke-width="0.1"/>
)";

    int i = 0;
    for (auto &&point : points) {
        ofs << R"(    <text )";
        ofs << R"(x=")" << point.x << R"(" )";
        ofs << R"(y=")" << -point.y << R"(" )";
        ofs << R"(font-size="2">)";
        ofs << 'p' << i;
        ofs << R"(</text>)" << std::endl;

        i++;
    }
    
    ofs << R"(</svg>
<div class="mermaid">
    flowchart TD
)";

    std::set<std::pair<std::string, std::string>> children_relations;
    std::map<std::pair<std::string, std::string>, int> neighbors_relations;

    std::stack<std::weak_ptr<Triangle>> triangle_stack;
    triangle_stack.push(root_triangle);

    while (!triangle_stack.empty()) {
        auto triangle = triangle_stack.top().lock();
        triangle_stack.pop();

        std::string label = Utility::GetLabel(points, triangle);

        for (auto&& child : triangle->children) {
            if (child != nullptr) {
                children_relations.insert({label, Utility::GetLabel(points, child)});
                triangle_stack.push(child);
            }
        }

        for (auto&& neighbor : triangle->neighbors) {
            if (neighbor.lock() == nullptr) {
                continue;
            }

            std::string neighbor_label = Utility::GetLabel(points, neighbor);
            std::pair<std::string, std::string> pair_label;

            if (label < neighbor_label) {
                pair_label = {label, neighbor_label};
            }
            else {
                pair_label = {neighbor_label, label};
            }

            neighbors_relations.insert({pair_label, 0});
            neighbors_relations.at(pair_label)++;
        }
    }

    for (auto [parent_label, child_label] : children_relations) {
        ofs << "    " << parent_label;
        ofs << " --> " << child_label;
        ofs << std::endl;
    }
/*
    for (auto [pair_label, count] : neighbors_relations) {
        ofs << "    " << pair_label.first;
        ofs << " -.";
        ofs << count;
        ofs << ".- " << pair_label.second;
        ofs << std::endl;
    }
*/
    ofs << R"(</div>)";

    ofs.close();
}

int main() {
    Random random(0, 100);

    const char* directory_name = "DelaunayDemoImages";
    if (std::filesystem::exists(directory_name)) {
        std::filesystem::remove_all(directory_name);
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::filesystem::create_directory(directory_name);


    std::list<Point2d> points {
        {0, 0},
        {100, 0},
        {50, 70},
    };
    
    auto [root_triangle, dummy_triangle] = MakeRoot(&*points.begin(), &*++points.begin(), &*++++points.begin());

    std::set<std::pair<Point2d*, Point2d*>> edges;
    std::set<std::pair<Point2d*, Point2d*>> flipped_edges = GetUniqueLeavesEdges(root_triangle);

    for (int i = 0; i < 100; i++) {
        Point2d p; 
        do {
            p = {random(), random()};
        } while (!root_triangle->Contains(&p));
        
        points.push_back(p);
        Point2d* point = &points.back();


        auto deepest = root_triangle->FindDeepest(point).lock();
        
        root_triangle->Divide(point);

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

        sprintf(filename, "%s/flipping-%04d.svg", directory_name, i);
        WriteSVG(filename, edges);


        flipped_edges = GetUniqueLeavesEdges(root_triangle);

        sprintf(filename, "%s/flipped-%04d.svg", directory_name, i);
        WriteSVG(filename, flipped_edges);

        sprintf(filename, "%s/with-graph-%04d.html", directory_name, i);
        DrawGraphInHTML(filename, points, flipped_edges, root_triangle);
    }
}