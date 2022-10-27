// Created by D0000000000N

#include "../include/csv_reader.h"

#include <fstream>
#include <sstream>
#include <iostream>

std::vector<std::string> split(std::string &input, char delimiter)
{
    std::istringstream stream(input);
    std::string field;
    std::vector<std::string> result;
    while (getline(stream, field, delimiter))
        result.push_back(field);
    return result;
}

Map2d<double> ReadCSV(std::string path)
{
    Map2d<double> map;
    int x_max;
    int y_max;
    std::ifstream ifs(path);

    if (ifs)
    {
        std::string line;

        // 一行目がラベルの場合
        // getline(ifs, line);
        // std::vector<std::string> strvec = split(line, ',');

        while (getline(ifs, line))
        {
            std::vector<int> datvec;
            std::vector<std::string> strvec = split(line, ',');
            for (auto &&s : strvec)
                datvec.push_back(std::stoi(s)); // セルの文字列を数値に変換
            data.push_back(datvec);
        }
        
        /*
        map.x;
        x_max;
        map.y;
        y_max;
        map.width = x_max - map.x;
        map.height = y_max - map.y;

        std::vector<double> v;
        map.data.insert(map.data.begin(), v);
        */
    }