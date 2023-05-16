#pragma once

class Shape
{
public:
    virtual float GetBase() const = 0;
    virtual float GetHeight() const = 0;
    virtual void SetBase(float newBase) = 0;
    virtual void SetHeight(float newHeight) = 0;
protected:
    float base;
    float height;
};