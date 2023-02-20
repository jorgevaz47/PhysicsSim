#include "Vector2D.h"
#include "Vector2D.cpp"
#include "Particle.h"
#include "Particle.cpp"
#include "iostream"
#include <iomanip>
#include <random>
#include <chrono>

using namespace std;

const int NUM_PARTICLES = 1;
float GRAVITY = -9.81;

Particle particles[NUM_PARTICLES];
static mt19937 generator(static_cast<long unsigned int>(chrono::high_resolution_clock::now().time_since_epoch().count()));
uniform_int_distribution<int> height(50, 100);
uniform_int_distribution<int> velocity(0, 25);
uniform_int_distribution<int> mass(1, 15);

void initializeParticles(){

    for(int i = 0; i < NUM_PARTICLES; i++){
        int y_pos = height(generator);
        int x_vel = velocity(generator);
        int y_vel = velocity(generator);
        int part_mass = mass(generator);
        particles[i] = Particle(Vector2D(0, y_pos), Vector2D(x_vel, y_vel), part_mass);
    }

}

Vector2D calculateForce(Particle particle, Vector2D acceleration){
    return Vector2D(particle.GetMass() * acceleration.GetX(), particle.GetMass() * acceleration.GetY());
}

int main(){

    initializeParticles();

    int y_pos = height(generator);
    int x_vel = velocity(generator);
    int y_vel = velocity(generator);
    int part_mass = mass(generator);

    Vector2D velocity = Vector2D(x_vel, y_vel);
    Vector2D position = Vector2D(0, y_pos);
    Particle test_Part = Particle(position, velocity, part_mass);

    cout << "Initial Particle: " << test_Part << endl;

    Vector2D gAccVec = Vector2D(0, GRAVITY);
    Vector2D gForce = calculateForce(test_Part, gAccVec);

    cout << gForce << endl;

    Vector2D newVel = Vector2D(test_Part.GetVelocity().GetX() + (gForce.GetX() / test_Part.GetMass()) * 1.0, test_Part.GetVelocity().GetY() + (gForce.GetY() / test_Part.GetMass()) * 1.0);
    Vector2D newPos = Vector2D(test_Part.GetPosition().GetX() + test_Part.GetVelocity().GetX() * 1.0, test_Part.GetPosition().GetY() + test_Part.GetVelocity().GetY() * 1.0);
   
    cout << "New Pos Vec: " << newPos << "\tNew Vel Vec: " << newVel << endl;

    test_Part.SetPosition(newPos);
    test_Part.SetVelocity(newVel);

    cout << "Final Particle: " << test_Part << endl;

}