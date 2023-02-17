#include "Vector2D.h"
#include "Vector2D.cpp"
#include "Particle.h"
#include "Particle.cpp"
#include "iostream"
#include <iomanip>
#include <random>

using namespace std;

int main(){

    default_random_engine generator;
    uniform_int_distribution<int> height(50, 100);
    uniform_int_distribution<int> velocity(1, 20);
    int y_pos = height(generator);
    int x_vel = velocity(generator);
    int y_vel = velocity(generator);

    Particle particleOne = Particle(Vector2D(0, y_pos), Vector2D(x_vel, y_vel));

    cout << particleOne;
}