// Created by 

#include "../include/option_writer.h"

#include <fstream>

void WriteOption(const std::string path, const std::map<std::string, std::string>& option) {
    std::ofstream ofs(path);

    for (auto [key, value] : option) {
        ofs << key << " : " << value << std::endl;
    }

    ofs.close();
}