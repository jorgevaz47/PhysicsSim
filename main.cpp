#include "Vector2D.h"
#include "Particle.h"
#include "RigidBody2D.h"
#include "Square.h"
#include <iostream>
#include <iomanip>
#include <random>
#include <chrono>

using namespace std;

const int NUM_PARTICLES = 2;
float GRAVITY = -9.81;

Particle particles[NUM_PARTICLES];
static mt19937 generator(static_cast<long unsigned int>(chrono::high_resolution_clock::now().time_since_epoch().count()));
uniform_int_distribution<int> height(50, 100);
uniform_int_distribution<int> velocity(0, 25);
uniform_int_distribution<int> mass(1, 15);

void initializeParticles()
{

    for (int i = 0; i < NUM_PARTICLES; i++)
    {
        int y_pos = height(generator);
        int x_vel = velocity(generator);
        int y_vel = velocity(generator);
        int part_mass = mass(generator);
        particles[i] = Particle(Vector2D(0, y_pos), Vector2D(x_vel, y_vel), part_mass);
    }
}

Vector2D calculateForce(Particle particle, Vector2D acceleration)
{
    return Vector2D(particle.GetMass() * acceleration.GetX(), particle.GetMass() * acceleration.GetY());
}

int main()
{

    int tFinal = 10;
    int tInitial;
    int tChange = 1;

    Vector2D gAccVec = Vector2D(0, GRAVITY);
    Vector2D gForce;

    initializeParticles();

    int i = 0;

    for (Particle p : particles)
    {

        tInitial = 0;

        // Displaying initial conditions of particle
        cout << i << " " << p << endl;

        // Calculate the force due to gravity of the particle (this is just for thoroughness)
        // Only needs to be calculated once since the mass of the particle is not changing
        gForce = calculateForce(p, gAccVec);

        while (tInitial <= tFinal)
        {

            // Calculating the new velocity and new position vector of the particle
            Vector2D newVel = Vector2D(p.GetVelocity().GetX() + (gForce.GetX() / p.GetMass()) * 1.0, p.GetVelocity().GetY() + (gForce.GetY() / p.GetMass()) * 1.0);
            Vector2D newPos = Vector2D(p.GetPosition().GetX() + p.GetVelocity().GetX() * 1.0, p.GetPosition().GetY() + p.GetVelocity().GetY() * 1.0);

            // Applying changes
            p.SetVelocity(newVel);
            p.SetPosition(newPos);

            // Displaying velocity and position update
            cout << i << " " << p << endl;

            // Updating the time by a deltaT of 1 sec
            tInitial += tChange;
        }

        i++;
    }

    RigidBody2D test = RigidBody2D();

}