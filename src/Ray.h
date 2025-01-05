#ifndef RAY_H
#define RAY_H

#include "Tuple.h"
#include "Sphere.h"
#include "Intersection.h"
#include "Intersectable.h"
#include "Plane.h"
#include "World.h"

class Ray
{
private:
    const float EPSILON = 0.00001;

public:
    Tuple origin;
    Tuple direction;

    Ray(Tuple o, Tuple dir);
    Tuple position(float d);
    std::vector<Intersection> intersectSphere(Sphere &s);
    std::vector<Intersection> intersectPlane(Plane &p);
    std::vector<Intersection> intersect(Intersectable *object);
};

#endif