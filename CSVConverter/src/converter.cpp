#include "../include/converter.hpp"
#include "../include/stringExtension.hpp"
#include "../include/color.hpp"

void convert(std::ifstream& ifs, std::ofstream& ofs) {
    std::string line;

    std::getline(ifs, line);
    std::vector<std::string> values = split(line, ",");

    int minX = std::stoi(values[0]);
    int maxX = std::stoi(values[1]);
    int minY = std::stoi(values[2]);
    int maxY = std::stoi(values[3]);

    int width = maxX - minX + 1;
    int height = maxY - minY + 1;

    std::vector<std::vector<double>> data(width, std::vector<double>(height));

    constexpr double nan = std::numeric_limits<double>::quiet_NaN();
    double minZ = std::numeric_limits<double>::max();
    double maxZ = std::numeric_limits<double>::min();

    for (int y = height - 1; y >= 0; y--) {
        std::getline(ifs, line);
        values = split(line, ",");

        for (int x = 0; x < width; x++) {
            // double value = nan;
            double value = -100;

            if (values[x] != "NaN") {
                value = std::stod(values[x]);

                if (minZ > value) {
                    minZ = value;
                }
                else if (maxZ < value) {
                    maxZ = value;
                }
            }
            
            data[x][y] = value;
        }
    }

    double depth = maxZ - minZ;

    ofs << R"(#VRML V2.0 utf8

Shape {
    geometry IndexedFaceSet {
        colorPerVertex TRUE
        color Color {
            color [
)";

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            double z = data[x][y];
            double h = (z - minZ) / depth;
            Color color(h, 1, 1);

            ofs << color.r << ' ' << color.g << ' ' << color.b << ',' << std::endl;
        }
    }

    ofs << R"(            ]
        }
        coord Coordinate {
            point [
)";

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            ofs << x << ' ' << y << ' ' << data[x][y] << ',' << std::endl;
        }
    }

    ofs << R"(            ]
        }
        coordIndex [
)";

    for (int y = 1; y < height; y++) {
        for (int x = 1; x < width; x++) {
            int index = x + y * width;
            ofs << index << ',';
            index--;
            ofs << index << ',';
            index -= width;
            ofs << index << ',';
            index++;
            ofs << index << ',';
            ofs << "-1" << std::endl;
        }
    }

    ofs << R"(        ]
    }
})";
}