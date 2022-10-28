// Created by 

#ifndef __WRL_WRITER_H__
#define __WRL_WRITER_H__

#include <string>
#include <utils>
#include <vector>

#include "alias.h"

void WriteWRL(std::string path, const PointSet& points, const std::vector<std::tuple<int, int, int>> indexSet);

#endif // __WRL_WRITER_H__