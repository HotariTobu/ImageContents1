// Created by HotariTobu

#ifndef __REDUCER_ATTRIBUTE_H__
#define __REDUCER_ATTRIBUTE_H__

#include "attribute.h"
#include "vector3d.h"

struct ReducerAttribute : public Attribute {
    Vector3d normal_vector;
};


#endif // __REDUCER_ATTRIBUTE_H__