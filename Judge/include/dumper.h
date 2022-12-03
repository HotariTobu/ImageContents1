// Created by HotariTobu

#ifndef __DUMPER_H__
#define __DUMPER_H__

#include <string>

#include "attribute.h"
#include "z_map.h"

class Dumper {
private:
    std::string _directory_path;
    std::map<Point2d, Attribute>* _data;
    ZMap<Attribute>* _z_map;

    double _max_ease_of_stay_value;
    int _count;

public:
    Dumper(const std::string& file_path, std::map<Point2d, Attribute>* data, ZMap<Attribute>* z_map);
    
    void Dump(const std::unique_ptr<double[]>& ease_of_stay_data);
};

#endif // __DUMPER_H__