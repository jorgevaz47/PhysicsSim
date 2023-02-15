#pragma once
#define VECTOR2D_H
#include <iostream>

class Vector2D{
    public:
        Vector2D(float newX = 0.0, float newY = 0.0);
        Vector2D operator + (Vector2D const &newVector2D);
        Vector2D operator - (Vector2D const &newVector2D);
        friend std::ostream& operator << (std::ostream &output, Vector2D const &vector);
        void SetX(float newX);
        void SetY(float newY);
        float GetX() const {return x;};
        float GetY() const {return y;};
    private:
        float x;
        float y;
};