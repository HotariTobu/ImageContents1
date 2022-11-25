// Created by HotariTobu

#ifndef __MAIN_HELPER_H__
#define __MAIN_HELPER_H__

#include <functional>
#include <map>
#include <string>

void HelpMain(int argc, const char* argv[], const std::string& option_file_path, const std::map<std::string, std::string>& default_option, std::function<void(std::map<std::string, std::string>&)> init, std::function<void(const std::string, const std::string)> process_file, const std::string& white_extension = ".dat");

#endif // __MAIN_HELPER_H__