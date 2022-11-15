// Created by 

#ifndef __SIMULATOR_H__
#define __SIMULATOR_H__

#include "neighbor.h"

// double simulator_threshold;

/*
Simulate ease of stay.
Deal out center value to surroundings.
If a neighbor value is bigger than the center value and the difference between the center and the neighbor is bigger than `simulator_threshold`, ignore the neighbor.

In uniform mode, the center value is divided by a count of points that can receive ease of stay value.

In flexible mode, first, calculate unsigned differences for each point that can receive ease of stay value. Then, sum them and subtract the sum by each difference. In addition, sum them and divide the differences by the sum. Finally, multiply the center ease of stay value.

[params]
- value: ease of stay in center
- neighbor: surrounding heights
[return]
additional ease of stay of neighbors.
If value is 0, ease of stay is not changed.
*/
Neighbor Simulate(double value, Neighbor neighbor);

#endif // __SIMULATOR_H__
