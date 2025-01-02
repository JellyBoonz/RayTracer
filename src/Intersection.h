#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "Intersectable.h"

class Intersection
{
public:
    float t;
    const Intersectable *object;
    Intersection() {};
    Intersection(float t, const Intersectable *obj) : t(t), object(obj) {}
};

#endif