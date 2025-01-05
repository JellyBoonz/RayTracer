#ifndef COLOR_H
#define COLOR_H
#include "Tuple.h"

class Color : public Tuple
{
public:
    Color()
        : Tuple(0.0, 0.0, 0.0, 0.0) {}
    Color(double red, double green, double blue)
        : Tuple(red, green, blue, 0.0) {}

    double getRed() const { return x; }
    double getGreen() const { return y; }
    double getBlue() const { return z; }

    Color &operator=(const Color &other)
    {
        if (this != &other) // Check for self-assignment
        {
            x = other.x;
            y = other.y;
            z = other.z;
        }
        return *this;
    }

    Color operator*(const Color &other) const
    {
        return Color(
            x * other.x,
            y * other.y,
            z * other.z);
    }

    Color operator*(double scalar) const
    {
        return Color(
            x * scalar,
            y * scalar,
            z * scalar);
    }

    Color operator+(const Color &other) const
    {
        return Color(
            x + other.x,
            y + other.y,
            z + other.z);
    }

    Color operator-(const Color &other) const
    {
        return Color(
            x - other.x,
            y - other.y,
            z - other.z);
    }
};

#endif