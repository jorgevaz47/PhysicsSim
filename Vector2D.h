#pragma once
#define VECTOR2D_H
#include <iostream>

class Vector2D
{
public:
    // Construtor for Vector2D
    Vector2D(float newX = 0.0, float newY = 0.0);
    // Getters and Setters for components of Vector2D
    float GetX() const { return x; };
    float GetY() const { return y; };
    void SetX(float newX);
    void SetY(float newY);
    // Overloading addition, minus, assignment, and output operator to correctly apply these operations
    Vector2D operator+(Vector2D const &newVector2D);
    Vector2D operator-(Vector2D const &newVector2D);
    void operator=(const Vector2D &vector);
    friend std::ostream &operator<<(std::ostream &output, Vector2D const &vector);

private:
    float x;
    float y;
};