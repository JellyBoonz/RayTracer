#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "Intersectable.h"

class Intersection
{
public:
    float t;
    const Intersectable *object;
    // Initialize the intersection with a default constructor
    Intersection() : t(0), object(nullptr) {}
    Intersection(float t, const Intersectable *obj) : t(t), object(obj) {}
};

#endif