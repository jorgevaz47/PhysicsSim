/* Name: Jorge Vazuqez
 * Date: 5/18/2023
 * Description: Shaper header file
 * UNUSED IN PROJECT
 * 
*/
#pragma once
#include "Shape.h"

class Square: public Shape 
{
public:
    Square(float newBase = 1.0, float newHeight = 1.0);
    float GetBase() const { return base; };
    float GetHeight() const { return height; };
    void SetBase(float newBase) { base = newBase; };
    void SetHeight(float newHeight) { height = newHeight; };
};