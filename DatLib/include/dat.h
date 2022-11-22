// Created by HotariTobu

#ifndef __DAT_H__
#define __DAT_H__

#include <string>
#include <map>
#include <utility>

#include "point2d.h"
#include "rectangle.h"

template<typename T>
std::pair<std::map<Point2d, T>, Rectangle> ReadDAT(const std::string& path);

template<typename T>
void WriteDAT(const std::string& path, const std::map<Point2d, T>& data);

#include "../src/dat.in"

#endif // __DAT_H__