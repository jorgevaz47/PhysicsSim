#include "Particle.h"
#include "iostream"

Particle::Particle(Vector2D newPosition, Vector2D newVelocity, float newMass){
    position = newPosition;
    velocity = newVelocity;
    mass = newMass;
}

void Particle::SetPosition(Vector2D newPosition){
    position = newPosition;
}

void Particle::SetVelocity(Vector2D newVelocity){
    velocity = newVelocity;
}

void Particle::SetMass(float newMass){
    mass = newMass;
}

std::ostream &operator<<(std::ostream &output, Particle const &particle){
    output << "Particle is at " << particle.GetPosition() << " with a velocity of " << particle.GetVelocity() << " and a mass of " << particle.GetMass();
}