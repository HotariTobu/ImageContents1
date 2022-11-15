// Created by 

#ifndef __OPTION_WRITER_H__
#define __OPTION_WRITER_H__

#include <map>
#include <string>

/*
Write option file.
[params]
- path: path to the option file
- option: option map to be written
*/
void WriteOption(const std::string path, const std::map<std::string, std::string>& option);

#endif // __OPTION_WRITER_H__