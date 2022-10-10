#include "../include/datetime.hpp"

std::string getNowDateTimeString() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    
    tm now_lt;
    localtime_s(&now_lt, &now_time);
    
    char result[16];
    sprintf_s(result, sizeof(result), "%04d%02d%02d%02d%02d%02d", now_lt.tm_year + 1900, now_lt.tm_mon + 1, now_lt.tm_mday, now_lt.tm_hour, now_lt.tm_min, now_lt.tm_sec);
    return result;
}