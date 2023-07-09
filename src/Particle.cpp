/* Name: Jorge Vazuqez
 * Date: 5/18/2023
 * Description: Particle implementation file
 * 
*/

#include "../include/Particle.h"
#include "iostream"

// Constructor for the particle object
Particle::Particle(Vector2D newPosition, Vector2D newVelocity, float newMass)
{
    position = newPosition;
    velocity = newVelocity;
    mass = newMass;
}

// Setters for the particle's fields
void Particle::SetPosition(Vector2D newPosition)
{
    position = newPosition;
}

void Particle::SetVelocity(Vector2D newVelocity)
{
    velocity = newVelocity;
}

void Particle::SetMass(float newMass)
{
    mass = newMass;
}

// Overloading the << operator to customize it for the particle object
std::ostream &operator<<(std::ostream &output, Particle const &particle)
{
    output << "Particle is at " << particle.GetPosition() << " with a velocity of " << particle.GetVelocity() << " and a mass of " << particle.GetMass();
    return output;
}