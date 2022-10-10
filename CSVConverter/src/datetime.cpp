#include "../include/datetime.hpp"

std::string getNowDateTimeString() {
    std::time_t t = std::time(nullptr);
    std::tm tm = *std::localtime(&t);
    std::stringstream result;
    result << std::put_time(&tm, "%Y%m%d%H%M%S");
    return result.str();
}