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
const int NUM_PARTICLES = 5; // Number of particles to simulate
const int WIDTH = 800, HEIGHT = 600; // Parameters for SDL window
const float GRAVITY = 9.81; // Acceleration due to gravity (m/s^2)

// Allocating an array with size NUM_PARTICLES of Particle objects
Particle particles[NUM_PARTICLES];

// Necessary objects to make randomized parameters for particles
static mt19937 generator(static_cast<long unsigned int>(chrono::high_resolution_clock::now().time_since_epoch().count()));
uniform_int_distribution<int> length(50, 500);
uniform_int_distribution<int> height(50, 100);
uniform_int_distribution<int> velocity(0, 25);
uniform_int_distribution<int> mass(1, 15);

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
void updateParticle()
{
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
                    for (Particle &p : particles)
                    {

                        // Calculate the force on the particle due to gravity
                        gForce = calculateForce(p, gAccVec);

                        // Calculates the new velocity and then the new position of the particle
                        Vector2D newVel = Vector2D(p.GetVelocity().GetX() + (gForce.GetX() / p.GetMass()) * 0.1, p.GetVelocity().GetY() + (gForce.GetY() / p.GetMass()) * 0.1);
                        Vector2D newPos = Vector2D(p.GetPosition().GetX() + p.GetVelocity().GetX() * 0.1, p.GetPosition().GetY() + p.GetVelocity().GetY() * 0.1);

                        // FOR DEBUGGING PURPOSES UNCOMMENT THIS
                        // cout << "New Pos: " << newPos << endl;

                        // Draw a white line between the old position to the new position of the particle
                        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                        SDL_RenderDrawLine(renderer, p.GetPosition().GetX(), p.GetPosition().GetY(), newPos.GetX(), newPos.GetY());

                        // Draw a red point on the old position
                        // This really can't be distinguished because of how close each point is drawn
                        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                        SDL_RenderDrawPoint(renderer, p.GetPosition().GetX(), p.GetPosition().GetY());

                        // Update the particles velocity and position
                        p.SetVelocity(newVel);
                        p.SetPosition(newPos);

                        // Boundary checks
                        // If any are out-of-bounds, flip the respective velocity
                        if(newPos.GetX() < 50 || newPos.GetX() > 750){
                            p.SetPosition(Vector2D(newPos.GetX(), p.GetPosition().GetY()));
                            p.SetVelocity(Vector2D(-p.GetVelocity().GetX(), p.GetVelocity().GetY()));
                        }
                        if(newPos.GetY() < 50 || newPos.GetY() > 550){
                            p.SetPosition(Vector2D(p.GetPosition().GetX(), newPos.GetY()));
                            p.SetVelocity(Vector2D(p.GetVelocity().GetX(), -p.GetVelocity().GetY()));
                        }
                    }
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