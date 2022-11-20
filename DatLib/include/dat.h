// Created by HotariTobu

#ifndef __DAT_H__
#define __DAT_H__

#include <string>
#include <utility>
#include <vector>

std::vector<std::tuple<int, int, double, int>> ReadDAT(const std::string& path);
std::vector<std::tuple<int, int, double, int>> WriteDAT(const std::string& path);

#endif // __DAT_H__