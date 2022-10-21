// Created by 

#ifndef __SIMULATOR_H__
#define __SIMULATOR_H__

#include "neighbor.h"

/*
Simulate ease of stay.
Deal out center value to surroundings.
[params]
- value: ease of stay in center
- neighbor: surrounding heights
[return]
additional ease of stay of neighbors.
If value is 0, ease of stay is not changed.
*/
Neighbor Simulate(double value, Neighbor neighbor);

#endif // __SIMULATOR_H__