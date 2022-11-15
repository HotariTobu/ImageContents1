// Created by 

#ifndef __OPTION_READER_AND_WRITER_H__
#define __OPTION_READER_AND_WRITER_H__

#include <map>
#include <string>

std::map<std::string, std::string> ReadAndWriteOption(const std::string path, const std::map<std::string, std::string>& default_option);

#endif // __OPTION_READER_AND_WRITER_H__