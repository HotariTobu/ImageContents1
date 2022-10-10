#include "../include/stringExtension.hpp"

std::vector<std::string> split(std::string string, std::string separator) {
    std::vector<std::string> result;

    rsize_t offset = 0;

    size_t separatorLength = separator.length();
    while (true) {
        auto pos = string.find(separator, offset);
        if (pos == std::string::npos) {
            break;
        }

        result.push_back(string.substr(offset, pos - offset));
        offset = pos + separatorLength;
    }

    result.push_back(string.substr(offset));

    return result;
}