#ifndef RAY_H
#define RAY_H

#include "Tuple.h"
#include "Sphere.h"
#include "Intersection.h"
#include "Intersectable.h"
#include "World.h"

class Ray
{
private:
public:
    Tuple origin;
    Tuple direction;

    Ray(Tuple o, Tuple dir);
    Tuple position(float d);
    std::vector<Intersection> intersect(Sphere &s);
};

#endif