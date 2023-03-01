#pragma once
#define RIGIDBODY_2D_H
#include "Particle.h"
#include "Shape.h"

class RigidBody2D: public Particle
{
public:
    RigidBody2D() : Particle() {};
    float CalculateInertia();
private:
    Shape colliderShape;
};