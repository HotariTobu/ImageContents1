// Created by yu-getu

#include "../include/csv_writer.h"

#include <cmath>
#include <iostream>
#include <fstream>

void WriteCSV(std::string path, const Map2d<double> &map)
{
    std::ofstream ofs(path);
    if (ofs){
        ofs << map.x << "," << (map.width+map.x-1) << "," << map.y << "," << (map.height+map.y-1) << "\n";
        for (int i = 1; i < map.height+1; i++){
            for (int j = 1; j < map.width+1; j++){
                if (!std::isnan(map.data[i][j])){
                    ofs << map.data[i][j];
                }else{
                    ofs << "NaN";
                }
                if(j != map.width){
                    ofs << ",";
                }
            }
            ofs << std::endl;
        }
    }
}
