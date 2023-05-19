/* Name: Jorge Vazuqez
 * Date: 5/18/2023
 * Description: Vector2D implementation file
 * 
*/

#include "Vector2D.h"
#include "iostream"

Vector2D::Vector2D(float newX, float newY)
{
    x = newX;
    y = newY;
}

void Vector2D::SetX(float newX)
{
    x = newX;
}

void Vector2D::SetY(float newY)
{
    y = newY;
}

void Vector2D::operator=(const Vector2D &vector)
{
    x = vector.GetX();
    y = vector.GetY();
}

Vector2D Vector2D::operator+(Vector2D const &newVector2D)
{
    return Vector2D(x + newVector2D.GetX(), y + newVector2D.GetY());
}

Vector2D Vector2D::operator-(Vector2D const &newVector2D)
{
    return Vector2D(x - newVector2D.GetX(), y - newVector2D.GetY());
}

std::ostream &operator<<(std::ostream &output, Vector2D const &vector)
{
    output << "(" << vector.GetX() << ", " << vector.GetY() << ")";
    return output;
}