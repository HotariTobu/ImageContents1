// Created by 

#ifndef __OPTION_READER_H__
#define __OPTION_READER_H__

#include <map>
#include <string>

/*
Read an option file.
[params]
- path: path to the option file
[return]
Return the option map that is read.
*/
std::map<std::string, std::string> ReadOption(const std::string path);

#endif // __OPTION_READER_H__