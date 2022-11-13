// Created by 

#include "../include/vector3d.h"

#include "equals.h"
#include "near.h"

void Vector3d::Normalize() {

}

double Vector3d::Length() const {

}

double Vector3d::Inner(const Vector3d vector) const {

}

Vector3d Vector3d::Cross(const Vector3d vector) const {
    
}

bool operator==(const Vector3d vector1, const Vector3d vector2) {
    return
        Equals(vector1.x, vector2.x) &&
        Equals(vector1.y, vector2.y) &&
        Equals(vector1.z, vector2.z);
}

bool operator!=(const Vector3d vector1, const Vector3d vector2) {
    return !(vector1 == vector2);
}

bool operator<(const Vector3d vector1, const Vector3d vector2) {
    double vector1_values[3] = {vector1.x, vector1.y, vector1.z};
    double vector2_values[3] = {vector2.x, vector2.y, vector2.z};

    for (int i = 0; i < 3; i++) {
        double difference = vector1_values[i] - vector2_values[i];
        if (difference < 0) {
            return true;
        }
        else if (difference > 0) {
            return false;
        }
    }
    
    return false;
}

Vector3d operator+(const Vector3d vector1, const Vector3d vector2) {

}

Vector3d operator-(const Vector3d vector1, const Vector3d vector2) {

}

Vector3d operator*(const Vector3d vector, double value) {

}

Vector3d operator/(const Vector3d vector, double value) {

}

bool Near(Vector3d vector1, Vector3d vector2) {
    return
        Near(vector1.x, vector2.x) &&
        Near(vector1.y, vector2.y) &&
        Near(vector1.z, vector2.z);
}
