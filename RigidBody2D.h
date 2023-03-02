#pragma once
#define RIGIDBODY_2D_H
#include "Particle.h"
#include "Square.h"

class RigidBody2D: public Particle
{
public:
    RigidBody2D(Square newSquare = Square()) : Particle() {};
    float CalculateInertia();
private:
    Square shapeSquare;
    float angle;
    float angularVelocity;
};