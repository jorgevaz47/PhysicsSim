#pragma once
#define PARTICLE_H
#include "Vector2D.h"

class Particle{
    public:
        // Constructor for Particle
        Particle(Vector2D newPosition = Vector2D(), Vector2D newVelocity = Vector2D(), float newMass = 1.0);
        // Getters and Setters for components of Particle
        Vector2D GetPosition() const {return position;};
        Vector2D GetVelocity() const {return velocity;};
        float GetMass() const {return mass;};
        void SetPosition(Vector2D newPosition);
        void SetVelocity(Vector2D newVelocity);
        void SetMass(float newMass);
        // Overloading output operator to correctly apply this operation
        friend std::ostream& operator << (std::ostream &output, Particle const &particle);
    private:
        Vector2D position;
        Vector2D velocity;
        float mass;
};