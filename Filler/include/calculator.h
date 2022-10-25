// Created by 

#ifndef __CALCULATOR_H__
#define __CALCULATOR_H__

#include "neighbor.h"

/*
Calculate center missing value from neighbors.
Ignore nan in neighbors.
[params]
- neighbors: surrounding height values
[return]
Calculated center value.
*/
double Calculate(Neighbor neighbor);

#endif // __CALCULATOR_H__