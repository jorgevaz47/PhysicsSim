/* Name: Jorge Vazuqez
 * Date: 5/18/2023
 * Description: Physics Simulator Project
 * 
*/

#include "../PhysicsSim/include/Vector2D.h"
#include "../PhysicsSim/include/Particle.h"
#include "../PhysicsSim/include/RigidBody2D.h"
#include "../PhysicsSim/include/Square.h"
#include "../PhysicsSim/include/Stack.h"
#include <iostream>
#include <iomanip>
#include <random>
#include <chrono>
#include <SDL2/SDL.h>

using namespace std;

// Initializing Constants
const int NUM_PARTICLES = 4;         // Number of particles to simulate
const int WINDOW_SIZE[2] = {800, 600}; // Parameters for SDL window {WIDTH, HEIGHT}
const float GRAVITY = 9.81;          // Acceleration due to gravity (m/s^2)
const float TIME = 0.1;              // Time step

// Allocating an array with size NUM_PARTICLES of Particle objects
Particle particles[NUM_PARTICLES];

// Necessary objects to make randomized parameters for particles
static mt19937 generator(static_cast<long unsigned int>(chrono::high_resolution_clock::now().time_since_epoch().count()));
uniform_int_distribution<int> length(50, 500);
uniform_int_distribution<int> height(50, 100);
uniform_int_distribution<int> velocity(0, 25);
uniform_int_distribution<int> mass(1, 50);

// Prototype functions
void initializeParticles();
Vector2D calculateForce(Particle particle, Vector2D acceleration);
void updateParticle(Particle &p);
void updateParticles(Particle particleArray[], int arraySize);
bool outOfBounds(Vector2D pos, char axis);
void drawBackground(SDL_Renderer *renderer);
void drawParticle(SDL_Renderer *renderer, Particle p);
bool inNet(Vector2D pos);

int main(int argc, char *argv[])
{

    Stack stack;

    // Calling method to setup all particles
    initializeParticles();

    for(Particle p : particles){
        stack.push(p);
    }

    // Initializing the SDL library
    SDL_Init(SDL_INIT_EVERYTHING);

    // Generates a pointer to an SDL_Window with the width and height set
    SDL_Window *window = SDL_CreateWindow("Test run", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_SIZE[0], WINDOW_SIZE[1], SDL_WINDOW_ALLOW_HIGHDPI);

    // Generates a poitner to an SDL_Renderer that is used to display graphics
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    // This checks to see if the window failed to create
    if (NULL == window)
    {
        cout << "Could not create window: " << SDL_GetError() << endl;
        return 1;
    }

    // Method to draw background
    drawBackground(renderer);

    // First particle to shoot
    Particle particle = stack.top();
    // cout << particle << endl;
    stack.pop();

    // Left-Click flag and timer
    bool leftClickable = true;
    int iteration = 0;
    
    // Creating a variable to hold SDL_Event's
    SDL_Event event;

    // This will run while the window is open
    while (true && !stack.isEmpty())
    {

        // This checks for events from the SDL library
         if (SDL_PollEvent(&event))
        {
            // If a quit event is detect, exit while loop
            if (SDL_QUIT == event.type)
            {
                break;
            }
            // Drawing an arrow when the user has clicked the left mouse button from the initial position of the particle
            if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT && leftClickable)
            {   
                cout << particle << endl;
                int mouseX = event.button.x;
                int mouseY = event.button.y;

                // cout << mouseX << ", " << mouseY << endl;

                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderDrawLine(renderer, particle.GetPosition().GetX(), particle.GetPosition().GetY(), mouseX, mouseY);
                particle.SetVelocity(Vector2D((mouseX - particle.GetPosition().GetX()) * 25 / 100, -(particle.GetPosition().GetY() - mouseY) * 25 / 100));
                // cout << particle << endl;
                leftClickable = !leftClickable;
            }
        }
        // Once user has left clicked, animate the ball
        if(!leftClickable){
            iteration++;
            drawParticle(renderer, particle);
            updateParticle(particle);
        }
        SDL_RenderPresent(renderer);

        // After 300 iterations of the update, reset and go onto the next particle
        if(iteration > 300){
            leftClickable = !leftClickable;
            iteration = 0;
            particle = stack.top();
            stack.pop();
            drawBackground(renderer);
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}

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
        // particles[i] = Particle(Vector2D(x_pos, y_pos), Vector2D(x_vel, y_vel), part_mass);
        particles[i] = Particle(Vector2D(100, 450), Vector2D(0, 0), part_mass);
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

void updateParticle(Particle &p)
{

    // Calculate the force on the particle due to gravity
    Vector2D gForce = Vector2D(calculateForce(p, Vector2D(0, GRAVITY)));

    // Calculates the new velocity and then the new position of the particle
    Vector2D newVel = Vector2D(p.GetVelocity().GetX() + (gForce.GetX() / p.GetMass()) * TIME, p.GetVelocity().GetY() + (gForce.GetY() / p.GetMass()) * TIME);

    // cout << "newVel" << newVel << endl;

    // TEST OPPOSING FORCE
    Vector2D airResistance = Vector2D(0, p.GetPosition().GetY() / p.GetVelocity().GetY() / 10000);
    if (newVel.GetY() > 0)
    {
        // cout << "Slowing down ball" << endl;
        newVel.SetY(newVel.GetY() - airResistance.GetY());
    }

    Vector2D newPos = Vector2D(p.GetPosition().GetX() + p.GetVelocity().GetX() * TIME, p.GetPosition().GetY() + p.GetVelocity().GetY() * TIME);

    // Out-of-bounds checker
    if (outOfBounds(newPos, 'X'))
    {
        // cout << "---OUT OF BOUNDS IN THE X COORDINATE---" << endl;
        newVel.SetX(-newVel.GetX());
        newPos.SetX(p.GetPosition().GetX() + newVel.GetX() * TIME);
    }
    if (outOfBounds(newPos, 'Y'))
    {
        // cout << "---OUT OF BOUNDS IN THE Y COORDINATE---" << endl;
        // Recalculate the X-Position and X-Velocity of the particle
        newPos.SetY(550);
        float time = abs((newPos.GetY() - p.GetPosition().GetY()) / (newVel.GetY()));
        // newVel.SetX(p.GetVelocity().GetX() + (gForce.GetX() / p.GetMass()) * time);
        newPos.SetX(p.GetPosition().GetX() + newVel.GetX() * time);
        newVel.SetY(-newVel.GetY() + 25);
    }

    if(inNet(p.GetPosition())){
        return;
    }

    p.SetVelocity(newVel);
    p.SetPosition(newPos);
}

// Updates each particle's velocity and position and does a bounary check to ensure that each particle is within the bounds
void updateParticles(Particle particleArray[], int arraySize)
{
    for (int i = 0; i < arraySize; i++)
    {
        Particle &p = particleArray[i];

        // Calculate the force on the particle due to gravity
        Vector2D gForce = Vector2D(calculateForce(p, Vector2D(0, GRAVITY)));

        // Calculates the new velocity and then the new position of the particle
        Vector2D newVel = Vector2D(p.GetVelocity().GetX() + (gForce.GetX() / p.GetMass()) * TIME, p.GetVelocity().GetY() + (gForce.GetY() / p.GetMass()) * TIME);

        // cout << "newVel" << newVel << endl;

        // TEST OPPOSING FORCE
        Vector2D airResistance = Vector2D(0, p.GetPosition().GetY() / p.GetVelocity().GetY() / 10000);
        if (newVel.GetY() > 0)
        {
            // cout << "Slowing down ball" << endl;
            newVel.SetY(newVel.GetY() - airResistance.GetY());
        }

        Vector2D newPos = Vector2D(p.GetPosition().GetX() + p.GetVelocity().GetX() * TIME, p.GetPosition().GetY() + p.GetVelocity().GetY() * TIME);

        // Out-of-bounds checker
        if (outOfBounds(newPos, 'X'))
        {
            // cout << "---OUT OF BOUNDS IN THE X COORDINATE---" << endl;
            newVel.SetX(-newVel.GetX());
            newPos.SetX(p.GetPosition().GetX() + newVel.GetX() * TIME);
        }
        if (outOfBounds(newPos, 'Y'))
        {
            // cout << "---OUT OF BOUNDS IN THE Y COORDINATE---" << endl;
            // Recalculate the X-Position and X-Velocity of the particle
            newPos.SetY(550);
            float time = abs((newPos.GetY() - p.GetPosition().GetY()) / (newVel.GetY()));
            // newVel.SetX(p.GetVelocity().GetX() + (gForce.GetX() / p.GetMass()) * time);
            newPos.SetX(p.GetPosition().GetX() + newVel.GetX() * time);
            newVel.SetY(-newVel.GetY() + 25);
        }

        p.SetVelocity(newVel);
        p.SetPosition(newPos);
    }
}

// Simple out-of-bounds algorithm
bool outOfBounds(Vector2D pos, char axis)
{
    if (axis == 'X')
    {
        if (pos.GetX() < 50 || pos.GetX() > 750)
        {
            return true;
        }
    }
    if (axis == 'Y')
    {
        if (pos.GetY() < 50 || pos.GetY() > 550)
        {
            return true;
        }
    }
    return false;
}

bool inNet(Vector2D pos){
    if((pos.GetX() > 665 && pos.GetX() < 700) && (pos.GetY() > 365 && pos.GetY() < 370)){
        // cout << "BALL IN NET" << endl;
        return true;
    }
    return false;
}

// This method is used to draw the background of this application
void drawBackground(SDL_Renderer *renderer)
{

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    SDL_Rect ground{0, 550, 800, 50};

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &ground);
    SDL_RenderFillRect(renderer, &ground);

    SDL_Rect pole{700, 350, 10, 200};

    SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
    SDL_RenderDrawRect(renderer, &pole);
    SDL_RenderFillRect(renderer, &pole);

    SDL_Rect netHolder{665, 365, 35, 5};

    SDL_SetRenderDrawColor(renderer, 235, 55, 27, 255);
    SDL_RenderDrawRect(renderer, &netHolder);
    SDL_RenderFillRect(renderer, &netHolder);

    SDL_RenderPresent(renderer);
}

// This draws each particle slightly bigger
void drawParticle(SDL_Renderer *renderer, Particle p)
{

    SDL_SetRenderDrawColor(renderer, 148, 74, 0, 255);
    SDL_RenderDrawPoint(renderer, p.GetPosition().GetX(), p.GetPosition().GetY());

    for (int i = -3; i <= 0; i++)
    {
        for (int j = i + 3; j >= 0; j--)
        {
            SDL_RenderDrawPoint(renderer, p.GetPosition().GetX() + j, p.GetPosition().GetY() + i);
            SDL_RenderDrawPoint(renderer, p.GetPosition().GetX() - j, p.GetPosition().GetY() - i);
            SDL_RenderDrawPoint(renderer, p.GetPosition().GetX() + j, p.GetPosition().GetY() - i);
            SDL_RenderDrawPoint(renderer, p.GetPosition().GetX() - j, p.GetPosition().GetY() + i);
        }
    }
}