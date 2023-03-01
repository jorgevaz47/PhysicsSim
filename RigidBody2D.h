#pragma once
#define RIGIDBODY_2D_H
#include "Particle.h"

class RigidBody2D: public Particle
{
public:
    float GetLength() const { return length; };
    float GetWidth() const { return width; };
    void SetLength(float newLength);
    void SetWidth(float newWidth);
private:
    float length;
    float width;
};