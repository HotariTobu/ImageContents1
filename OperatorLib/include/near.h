// Created by 

#ifndef __NEAR_H__
#define __NEAR_H__

/*
Determine if the 2 values are close.
[params]
- a: first value
- b: second value
[return]
Return true if the unsigned difference of `a` and `b` is lesser than a threshold, false other else.
*/
bool Near(double a, double b);

#endif // __NEAR_H__