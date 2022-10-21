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
If value is "Nan", assign nan of double.
*/
Map2d ReadCSV(std::string path);

#endif // __CSV_READER_H__