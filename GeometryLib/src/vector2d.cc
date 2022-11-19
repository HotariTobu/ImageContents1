// Created by baconcategg

#include "../include/vector2d.h"

#include <cmath>

#include "equals.h"
#include "near.h"
#include "../include/point2d.h"

void Vector2d::Normalize() {
    double length = Length();
    x = x / length;
    y = y / length;
}

double Vector2d::Length() const {
    return sqrt((x * x) + (y * y));
}

double Vector2d::Inner(const Vector2d vector) const {
    return (x * vector.x) + (y * vector.y);
}

double Vector2d::Cross(const Vector2d vector) const {
    return (x * vector.y) - (y * vector.x);
}

Point2d Vector2d::ToPoint() const {
    return Point2d{x, y};
}

Vector2d& Vector2d::operator+=(const Vector2d vector) {
    x += vector.x;
    y += vector.y;
    return *this;
}

Vector2d& Vector2d::operator-=(const Vector2d vector) {
    x -= vector.x;
    y -= vector.y;
    return *this;
}

Vector2d& Vector2d::operator*=(const Vector2d vector) {
    x *= vector.x;
    y *= vector.y;
    return *this;
}

Vector2d& Vector2d::operator*=(const double value) {
    x *= value;
    y *= value;
    return *this;
}

Vector2d& Vector2d::operator/=(const Vector2d vector) {
    x /= vector.x;
    y /= vector.y;
    return *this;
}

Vector2d& Vector2d::operator/=(const double value) {
    x /= value;
    y /= value;
    return *this;
}


bool operator==(const Vector2d vector1, const Vector2d vector2) {
    return
        Equals(vector1.x, vector2.x) &&
        Equals(vector1.y, vector2.y);
}

bool operator!=(const Vector2d vector1, const Vector2d vector2) {
    return !(vector1 == vector2);
}

bool operator<(const Vector2d vector1, const Vector2d vector2) {
    double vector1_values[2] = {vector1.x, vector1.y};
    double vector2_values[2] = {vector2.x, vector2.y};

    for (int i = 0; i < 2; i++) {
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

Vector2d operator+(const Vector2d vector1, const Vector2d vector2) {
    return {
        vector1.x + vector2.x ,
        vector1.y + vector2.y
    };
}

Vector2d operator-(const Vector2d vector1, const Vector2d vector2) {
    return {
        vector1.x - vector2.x ,
        vector1.y - vector2.y
    };
}

Vector2d operator*(const Vector2d vector, double value) {
    return {
        vector.x * value ,
        vector.y * value
    };
}

Vector2d operator/(const Vector2d vector, double value) {
    return {
        vector.x / value ,
        vector.y / value
    };
}

bool Near(Vector2d vector1, Vector2d vector2) {
    return
        Near(vector1.x, vector2.x) &&
        Near(vector1.y, vector2.y);
}