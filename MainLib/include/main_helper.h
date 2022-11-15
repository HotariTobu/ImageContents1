// Created by 

#ifndef __MAIN_HELPER_H__
#define __MAIN_HELPER_H__

#include <functional>
#include <map>
#include <string>

void HelpMain(const std::string option_file_path, const std::map<std::string, std::string> default_option, std::function<void(std::map<std::string, std::string>&)> init, std::function<void(const std::string, const std::string)> process_file);

#endif // __MAIN_HELPER_H__