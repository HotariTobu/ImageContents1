// Created by 

#ifndef __OPTION_READER_AND_WRITER_H__
#define __OPTION_READER_AND_WRITER_H__

#include <map>
#include <string>

/*
First, read an option file.
Overwrite option with default option if a key-value pair doesn't exist in option.
Finally, write the option file.
[params]
- path: path to the option file
- option: option map to be written
[return]
Return the option map that is read and overwritten.
*/
std::map<std::string, std::string> ReadAndWriteOption(const std::string path, const std::map<std::string, std::string>& default_option);

#endif // __OPTION_READER_AND_WRITER_H__