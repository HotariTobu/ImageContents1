// Created by HotariTobu

#include "../include/main_helper.h"

#include <cctype>
#include <filesystem>
#include <iostream>

#include "../include/option_reader.h"
#include "../include/option_writer.h"

namespace fs = std::filesystem;

std::string ToLower(const std::string string) {
    std::string result;
    for (char c : string) {
        result.push_back(std::tolower(c));
    }
    return result;
}

void HelpMain(const std::string option_file_path, const std::map<std::string, std::string> default_option, std::function<void(std::map<std::string, std::string>&)> init, std::function<void(const std::string, const std::string)> process_file) {
    auto option = ReadOption(option_file_path);

    for (auto pair : default_option) {
        option.insert(pair);
    }

    std::string source_directory_path = option.at("source_directory_path");
    std::string destination_directory_path = option.at("destination_directory_path");

    if (!fs::exists(source_directory_path)) {
        std::cout << "Not exist: " << source_directory_path << std::endl;
        return;
    }

    fs::create_directories(destination_directory_path);

    init(option);

    for (const auto& file : fs::directory_iterator(source_directory_path)) {
        fs::path source_file_path = file.path();

        if (ToLower(source_file_path.extension().string()) != ".csv") {
            continue;
        }

        fs::path basename = source_file_path.stem();
        fs::path destination_base_path = fs::path(destination_directory_path) / basename;

        process_file(source_file_path.string(), destination_base_path.string());
    }

    WriteOption(option_file_path, option);
}