// Created by HotariTobu

#include "../include/dumper.h"

#include "dat.h"

Dumper::Dumper(const std::filesystem::path& file_path, const Rectangle& rectangle) {
    _directory_path = file_path.parent_path() / file_path.stem();
    std::filesystem::create_directories(_directory_path);
    
    _rectangle = rectangle;
}

void Dumper::Dump(const std::string& filename, const std::map<Point2d, ReducerAttribute>& data) {
    std::map<Point2d, ReducerAttribute> dump_data(data.begin(), data.end());

    Color outline_color(0, 0, 0);
    Color inside_color(0, 0, 1);

    for (auto&& [_, attribute] : dump_data) {
        if (attribute.is_removed) {
            attribute.color = inside_color;
        }
        else {
            attribute.color = outline_color;
        }
    }

    auto file_path = _directory_path / filename;
    WriteDAT(file_path.string(), dump_data);
}