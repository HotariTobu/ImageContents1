// Created by HotariTobu

#ifndef __VECTOR2D_H__
#define __VECTOR2D_H__

struct Point2d;

// Represent 2D vector.
struct Vector2d {
    double x;
    double y;

    // Make the length 1.
    void Normalize();


    // Return the length.
    double Length() const;

    // Calculate inner product with `vector`.
    double Inner(const Vector2d vector) const;

    // Calculate cross product with `vector`.
    double Cross(const Vector2d vector) const;
    

    // Return the vector as a point.
    Point2d ToPoint() const;

    Vector2d& operator+=(const Vector2d vector);
    Vector2d& operator-=(const Vector2d vector);
    Vector2d& operator*=(const Vector2d vector);
    Vector2d& operator/=(const Vector2d vector);
    
    Vector2d& operator*=(const double value);
    Vector2d& operator/=(const double value);
};

bool operator==(const Vector2d vector1, const Vector2d vector2);
bool operator!=(const Vector2d vector1, const Vector2d vector2);

bool operator<(const Vector2d vector1, const Vector2d vector2);

Vector2d operator+(const Vector2d vector1, const Vector2d vector2);
Vector2d operator-(const Vector2d vector1, const Vector2d vector2);
Vector2d operator*(const Vector2d vector, double value);
Vector2d operator/(const Vector2d vector, double value);

bool Near(Vector2d vector1, Vector2d vector2);

#endif // __VECTOR2D_H__