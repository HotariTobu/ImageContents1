// Created by 

#include "../include/option_reader.h"

#include <fstream>

std::string Trim(std::string string, const char* trim_character_list = " \t\v\r\n") {
    std::string::size_type left = string.find_first_not_of(trim_character_list);
    if (left != std::string::npos) {
        string = string.substr(left);
    }

    std::string::size_type right = string.find_last_not_of(trim_character_list);
    if (right != std::string::npos) {
        string = string.substr(0, right + 1);
    }
    
    return string;
}

std::map<std::string, std::string> ReadOption(const std::string path) {
    std::map<std::string, std::string> option;

    std::ifstream ifs(path);
    if (ifs.fail()) {
        return option;
    }

    std::string line;
    while (getline(ifs, line)) {
        std::string::size_type separator_index = line.find('=');
        if (separator_index == std::string::npos) {
            continue;
        }

        std::string key = line.substr(0, separator_index);
        std::string value = line.substr(separator_index);

        if (value.size() > 0) {
            value[0] = ' ';
        }

        option.insert_or_assign(Trim(key), Trim(value));
    }

    ifs.close();

    return option;
}
