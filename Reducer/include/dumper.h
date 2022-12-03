// Created by HotariTobu

#ifndef __DUMPER_H__
#define __DUMPER_H__

#include <string>

#include "z_map.h"
#include "../include/reducer_attribute.h"

class Dumper {
private:
    std::string _directory_path;
    std::map<Point2d, ReducerAttribute>* _data;
    ZMap<ReducerAttribute>* _z_map;

public:
    Dumper(const std::string& file_path, std::map<Point2d, ReducerAttribute>* data, ZMap<ReducerAttribute>* z_map);
    
    void Dump(std::list<std::list<int>> indices_list);
};

#endif // __DUMPER_H__