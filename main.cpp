#include "Vector2D.h"
#include "Particle.h"
#include "RigidBody2D.h"
#include "Square.h"
#include <iostream>
#include <iomanip>
#include <random>
#include <chrono>
#include <SDL2/SDL.h>

using namespace std;

// Initializing Constants
const int NUM_PARTICLES = 1; // Number of particles to simulate
const int WIDTH = 800, HEIGHT = 600; // Parameters for SDL window
const float GRAVITY = 9.81; // Acceleration due to gravity (m/s^2)
const float TIME = 0.5;

// Allocating an array with size NUM_PARTICLES of Particle objects
Particle particles[NUM_PARTICLES];

// Necessary objects to make randomized parameters for particles
static mt19937 generator(static_cast<long unsigned int>(chrono::high_resolution_clock::now().time_since_epoch().count()));
uniform_int_distribution<int> length(50, 500);
uniform_int_distribution<int> height(50, 100);
uniform_int_distribution<int> velocity(0, 25);
uniform_int_distribution<int> mass(1, 15);

// Prototype functions
void initializeParticles();
Vector2D calculateForce(Particle particle, Vector2D acceleration);
void updateParticle(Particle particleArray[], int arraySize);
bool outOfBounds(Vector2D pos, char axis);

// This function works by creating particle objects with random parameters
// It then places them into the array particles
void initializeParticles()
{
    for (int i = 0; i < NUM_PARTICLES; i++)
    {   
        int x_pos = length(generator);
        int y_pos = height(generator);
        int x_vel = velocity(generator);
        int y_vel = velocity(generator);
        int part_mass = mass(generator);
        particles[i] = Particle(Vector2D(x_pos, y_pos), Vector2D(x_vel, y_vel), part_mass);
    }
}

// Calculutes the force on a particle given an accleration due to a force
// In this case the acceleration is due to gravity
// Returns a Vector2D representing the force vector
// Follows Newton's second law of motion (F=ma)
Vector2D calculateForce(Particle particle, Vector2D acceleration)
{
    return Vector2D(particle.GetMass() * acceleration.GetX(), particle.GetMass() * acceleration.GetY());
}

// TODO: Create function so that it encapsulates the updating of particle's position and velocity
//       Also use another function to detect for boundaries
void updateParticle(Particle particleArray[], int arraySize)
{
    for(int i = 0; i < arraySize; i++){
        Particle& p = particleArray[i];

        // Calculate the force on the particle due to gravity
        Vector2D gForce = Vector2D(calculateForce(p, Vector2D(0, GRAVITY)));

        // Calculates the new velocity and then the new position of the particle
        Vector2D newVel = Vector2D(p.GetVelocity().GetX() + (gForce.GetX() / p.GetMass()) * TIME, p.GetVelocity().GetY() + (gForce.GetY() / p.GetMass()) * TIME);

        cout << "newVel" << newVel << endl;

        // TEST OPPOSING FORCE
        Vector2D airResistance = Vector2D(0, p.GetPosition().GetY() / p.GetVelocity().GetY() / 10000);
        if(newVel.GetY() > 0){
            cout << "Slowing down ball" << endl;
            newVel.SetY(newVel.GetY() - airResistance.GetY());
        }
        

        Vector2D newPos = Vector2D(p.GetPosition().GetX() + p.GetVelocity().GetX() * TIME, p.GetPosition().GetY() + p.GetVelocity().GetY() * TIME);

        // Out-of-bounds checker
        if(outOfBounds(newPos, 'X')){
            newVel.SetX(-newVel.GetX());
            newPos.SetX(p.GetPosition().GetX() + newVel.GetX() * TIME);
        }
        if(outOfBounds(newPos, 'Y')){
            newVel.SetY(-newVel.GetY() + 25);
            if(p.GetPosition().GetY() + newVel.GetY() * TIME > 550){
                cout << "Reached bottom of ground" << endl;
                newPos.SetY(550);
            } else{
                newPos.SetY(p.GetPosition().GetY() + newVel.GetY() * TIME);
            }
        }

        p.SetVelocity(newVel);
        p.SetPosition(newPos);

    }
}

bool outOfBounds(Vector2D pos, char axis){
    if(axis == 'X'){
        if(pos.GetX() < 50 || pos.GetX() > 750){
            return true;
        }
    }
    if(axis == 'Y'){
        if(pos.GetY() < 50 || pos.GetY() > 550){
            return true;
        }
    }
    return false;
    
}

int main(int argc, char *argv[])
{
    // Creating the acceleration vector due to gravity
    Vector2D gAccVec = Vector2D(0, GRAVITY);
    Vector2D gForce;

    // Calling method to setup all particles
    initializeParticles();

    // Initializing the SDL library
    SDL_Init(SDL_INIT_EVERYTHING);

    // Generates a pointer to an SDL_Window with the width and height set 
    SDL_Window *window = SDL_CreateWindow("Test run", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);

    // Generates a poitner to an SDL_Renderer that is used to display graphics
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    // This checks to see if the window failed to create
    if (NULL == window)
    {
        cout << "Could not create window: " << SDL_GetError() << endl;
        return 1;
    }

    // Creating a variable to hold SDL_Event's
    SDL_Event event;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Set draw color to black
    SDL_RenderClear(renderer); // Set the entire window to black

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawLine(renderer, 0, 550, 800, 550);

    // This will run while the window is open
    while (true)
    {

        // This checks for events from the SDL library
        if (SDL_PollEvent(&event))
        {   
            // If a quit event is detect, exit while loop
            if (SDL_QUIT == event.type)
            {
                break;
            }

            // Checks for a pressed key
            if (SDL_KEYDOWN == event.type)
            {   
                // Checks if pressed key is the spacebar
                if (SDLK_SPACE == event.key.keysym.sym)
                {   
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                    for(Particle p : particles){
                        SDL_RenderDrawPoint(renderer, p.GetPosition().GetX(), p.GetPosition().GetY());
                    }
                    updateParticle(particles, NUM_PARTICLES);
                }
            }
        }
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}