#include "Vector2D.h"
#include "Vector2D.cpp"
#include "Particle.h"
#include "Particle.cpp"
#include "iostream"
#include <iomanip>

using namespace std;

int main(){
    Vector2D firstVector2D(10.0, 12.0);
    Vector2D secondVector2D(-5.0, 25);

    cout << "First 2D vector:" << endl;
    cout << "X: " << firstVector2D.GetX() << "\tY: " << firstVector2D.GetY() << endl;
    
    cout << "Second 2D vector:" << endl;
    cout << "X: " << secondVector2D.GetX() << "\tY: " << secondVector2D.GetY() << endl;

    Vector2D resultSum = firstVector2D + secondVector2D;

    cout << "First 2D Vector + Second 2D Vector:" << endl;
    cout << resultSum << endl;

    cout << "First 2D vector:" << endl;
    cout << "X: " << firstVector2D.GetX() << "\tY: " << firstVector2D.GetY() << endl;
    
    cout << "Second 2D vector:" << endl;
    cout << "X: " << secondVector2D.GetX() << "\tY: " << secondVector2D.GetY() << endl;

    Particle firstParticle();
    Particle secondParticle(firstVector2D, secondVector2D, 10.0);

    cout << firstParticle << endl;
    cout << secondParticle << endl;

}