// Created by 

#ifndef __CSV_WRITER_H__
#define __CSV_WRITER_H__

#include <string>

#include "../include/height_map.h"

/*
Write data to .csv file.
If value is nan of double, write "Nan".
[params]
- path: path to output .csv file
- map: height values to output
*/
void WriteCSV(std::string path, Map2d map);

#endif // __CSV_WRITER_H__