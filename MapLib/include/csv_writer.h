// Created by 

#ifndef __CSV_WRITER_H__
#define __CSV_WRITER_H__

#include <string>

#include "../include/map2d.h"

/*
Write data to .csv file.
If value is nan of double, write "NaN".
Outside values with 1 width are nan and actual heights surrounded by them so the size of `Map2d::data` is (`Map2d::height` + 2) * (`Map2d::width` + 2).
[params]
- path: path to output .csv file
- map: height values to output
*/
void WriteCSV(std::string path, const Map2d<double>& map);

#endif // __CSV_WRITER_H__