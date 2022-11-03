// Created by 

#include "../include/vector3d.h"

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
        vector1.x == vector2.x &&
        vector1.y == vector2.y &&
        vector1.z == vector2.z;
}

bool operator!=(const Vector3d vector1, const Vector3d vector2) {
    return !(vector1 == vector2);
}

Vector3d operator+(const Vector3d vector1, const Vector3d vector2) {

}

Vector3d operator-(const Vector3d vector1, const Vector3d vector2) {

}

Vector3d operator*(const Vector3d vector, double value) {

}

Vector3d operator/(const Vector3d vector, double value) {

}
