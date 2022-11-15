// Created by 

#include "../include/option_reader_and_writer.h"

#include "../include/option_reader.h"
#include "../include/option_writer.h"

std::map<std::string, std::string> ReadAndWriteOption(const std::string path, const std::map<std::string, std::string>& default_option) {
    auto option = ReadOption(path);

    for (auto pair : default_option) {
        option.insert(pair);
    }

    return option;
}