// Created by HotariTobu

#ifndef __DUMPER_H__
#define __DUMPER_H__

#include <filesystem>
#include <map>
#include <string>

#include "point2d.h"
#include "rectangle.h"
#include "../include/reducer_attribute.h"

class Dumper {
private:
    std::filesystem::path _directory_path;
    Rectangle _rectangle;

public:
    Dumper(const std::filesystem::path& file_path, const Rectangle& rectangle);
    
    void Dump(const std::string& filename, const std::map<Point2d, ReducerAttribute>& data);
};

#endif // __DUMPER_H__