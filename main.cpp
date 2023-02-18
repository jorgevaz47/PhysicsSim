#include "Vector2D.h"
#include "Vector2D.cpp"
#include "Particle.h"
#include "Particle.cpp"
#include "iostream"
#include <iomanip>
#include <random>
#include <chrono>

using namespace std;

int main(){

    mt19937 generator(static_cast<long unsigned int>(chrono::high_resolution_clock::now().time_since_epoch().count()));
    uniform_int_distribution<int> height(50, 100);
    uniform_int_distribution<int> velocity(0, 25);
    uniform_int_distribution<int> mass(1, 15);
    int y_pos = height(generator);
    int x_vel = velocity(generator);
    int y_vel = velocity(generator);
    int part_mass = mass(generator);

    Particle particleOne = Particle(Vector2D(0, y_pos), Vector2D(x_vel, y_vel), part_mass);

    cout << particleOne;
}