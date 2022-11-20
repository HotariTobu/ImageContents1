// Created by HotariTobu

#ifndef __DAT_H__
#define __DAT_H__

#include <string>
#include <map>

#include "point2d.h"

template<typename T>
std::map<Point2d, T> ReadDAT(const std::string& path);

template<typename T>
void WriteDAT(const std::string& path, const std::map<Point2d, T>& data);

typename std::map<Point2d, double> ReadDAT(const std::string& path);
typename void WriteDAT(const std::string& path, const std::map<Point2d, double>& data);

#endif // __DAT_H__