/* Name: Jorge Vazuqez
 * Date: 5/18/2023
 * Description: RigidBody2D header file
 * UNUSED IN PROJECT
*/

#pragma once
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