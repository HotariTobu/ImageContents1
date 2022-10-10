#include <filesystem>
#include <iostream>
#include <string>

namespace fs = std::filesystem;

#include "../include/converter.hpp"
#include "../include/datetime.hpp"

int main(int argc, const char *argv[]) {
    if (argc < 2) {
        std::cout << "Usage: \"path/to/source/csv/file/1\" \"path/to/source/csv/file/2\" ..." << std::endl;
        std::cin.get();
        return 0;
    }

    fs::path datetime = getNowDateTimeString();
    fs::create_directory(datetime);

    for (int i = 1; i < argc; i++) {
        try
        {
            fs::path srcPath = argv[i];

            std::string filename = srcPath.stem().string();
            fs::path dstPath = datetime / (filename + ".wrl");
            
            std::cout << "Converting: " << srcPath << " > " << dstPath << std::endl;

            std::ifstream ifs(srcPath);
            if (ifs.fail()) {
                std::cerr << "Source file error: " << std::strerror(errno) << std::endl;
                continue;
            }

            std::ofstream ofs(dstPath);
            if (ofs.fail()) {
                std::cerr << "Destination file error: " << std::strerror(errno) << std::endl;
                continue;
            }

            convert(ifs, ofs);

            ifs.close();
            ofs.close();
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << std::endl;
        }
    }
}