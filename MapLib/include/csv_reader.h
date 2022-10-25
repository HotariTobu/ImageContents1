// Created by 

#ifndef __CSV_READER_H__
#define __CSV_READER_H__

#include <string>

#include "../include/map2d.h"

/*
Read data from .csv file.
[params]
- path: path to input .csv file
[return]
Height values from .csv file.
If value is "NaN", assign nan of double.
Outside values with 1 width are nan and actual heights surrounded by them so the size of `Map2d::data` is (`Map2d::height` + 2) * (`Map2d::width` + 2).
*/
Map2d<double> ReadCSV(std::string path);

#endif // __CSV_READER_H__