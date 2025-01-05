#include "Tuple.h"
#include <stdexcept>
#include <iostream>

Tuple::Tuple() : x(0.0), y(0.0), z(0.0), w(0.0) {}
Tuple::Tuple(double x, double y, double z, double w) : x(x), y(y), z(z), w(w) {}

Tuple Tuple::point(double x, double y, double z)
{
    return Tuple(x, y, z, 1.0);
}

Tuple Tuple::vector(double x, double y, double z)
{
    return Tuple(x, y, z, 0.0);
}

bool Tuple::isPoint() const
{
    return w == 1.0;
}

bool Tuple::isVector() const
{
    return w == 0.0;
}

double Tuple::magnitude()
{
    if (isVector())
    {
        return (sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2) + pow(w, 2)));
    }
    else
    {
        throw std::invalid_argument("Cannot take magnitude of non-vector Tuple.");
    }
}

Tuple Tuple::normalize()
{
    double mag = magnitude();
    if (isVector())
    {
        return Tuple(x / mag, y / mag, z / mag, w / mag);
    }
    else
    {
        throw std::invalid_argument("Cannot take magnitude of non-vector Tuple.");
    }
}

Tuple Tuple::reflect(Tuple &normal)
{
    return *this - normal * (2.0 * dot(normal));
}

double Tuple::dot(const Tuple &other)
{
    if (isVector() && other.isVector())
    {
        return x * other.x + y * other.y + z * other.z + w * other.w;
    }
    else
    {
        throw std::invalid_argument("Cannot take magnitude of non-vector Tuple.");
    }
}

Tuple Tuple::cross(const Tuple &other)
{
    if (isVector() && other.isVector())
    {
        return Tuple(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x, 0.0);
    }
    else
    {
        throw std::invalid_argument("Cannot take magnitude of non-vector Tuple.");
    }
}

bool Tuple::operator==(const Tuple &other) const
{
    return std::abs(x - other.x) < 1e-5 &&
           std::abs(y - other.y) < 1e-5 &&
           std::abs(z - other.z) < 1e-5 &&
           std::abs(w - other.w) < 1e-5;
}

void Tuple::operator=(const Tuple &other)
{
    x = other.x;
    y = other.y;
    z = other.z;
    w = other.w;
}

Tuple Tuple::operator+(const Tuple &other) const
{
    return Tuple(x + other.x, y + other.y, z + other.z, w + other.w);
}

Tuple Tuple::operator-(const Tuple &other)
{
    return Tuple(x - other.x, y - other.y, z - other.z, w - other.w);
}

Tuple Tuple::operator-()
{
    return Tuple(0.0 - x, 0.0 - y, 0.0 - z, w);
}

Tuple Tuple::operator*(const double num)
{
    return Tuple(x * num, y * num, z * num, w);
}

Tuple Tuple::operator*(const Tuple &other)
{
    return Tuple(x * other.x, y * other.y, z * other.z, w * other.w);
}

Tuple Tuple::operator/(const double num)
{
    if (isVector())
    {
        return Tuple(x / num, y / num, z / num, w);
    }
    else
    {
        throw std::invalid_argument("Cannot divide non-vector Tuple by a scalar.");
    }
}

std::ostream &operator<<(std::ostream &os, const Tuple &tuple)
{
    os << "(" << tuple.x << ", " << tuple.y << ", " << tuple.z << ", " << tuple.w << ")";
    return os;
}