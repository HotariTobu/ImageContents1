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

void HelpMain(int argc, const char* argv[], const std::string& option_file_path, const std::map<std::string, std::string>& default_option, std::function<void(std::map<std::string, std::string>&)> init, std::function<void(const std::string, const std::string)> process_file, const std::string& white_extension) {
    auto option = ReadOption(option_file_path);

    for (auto pair : default_option) {
        option.insert(pair);
    }

    std::string source_directory_path = option.at("source_directory_path");
    std::string destination_directory_path = option.at("destination_directory_path");

    if (!fs::exists(source_directory_path)) {
        std::cout << "Not exist: " << source_directory_path << std::endl;
        std::filesystem::create_directories(source_directory_path);
        std::cout << "Created: " << source_directory_path << std::endl;
        return;
    }

    fs::create_directories(destination_directory_path);

    init(option);

    std::list<fs::path> file_paths;
    for (int i = 0; i < argc; i++) {
        file_paths.push_back(fs::path(argv[i]));
    }
    
    for (auto&& file : fs::directory_iterator(source_directory_path)) {
        file_paths.push_back(file.path());
    }

    for (auto&& source_file_path : file_paths) {
        if (ToLower(source_file_path.extension().string()) != white_extension) {
            continue;
        }

        fs::path basename = source_file_path.stem();
        fs::path destination_base_path = fs::path(destination_directory_path) / basename;

        process_file(source_file_path.string(), destination_base_path.string());
    }

    WriteOption(option_file_path, option);
}