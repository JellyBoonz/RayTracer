#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "Intersectable.h"

class Intersection
{
public:
    // Define the equality operator for Intersection objects
    bool operator==(const Intersection& other) const {
        return t == other.t && object == other.object;
    }
public:
    float t; // Distance along the ray where intersection occurs
    const Intersectable *object;
    // Initialize the intersection with a default constructor
    Intersection() : t(0), object(nullptr) {}
    Intersection(float t, const Intersectable *obj) : t(t), object(obj) {}
};

#endif