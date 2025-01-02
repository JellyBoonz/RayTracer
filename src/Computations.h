#ifndef COMPUTATIONS_H
#define COMPUTATIONS_H

#include "Intersection.h"
#include "Ray.h"

const float EPSILON = 0.00001f;

class Computations
{
public:
    float t;
    const Intersectable *object;
    Tuple point;
    Tuple eyev;
    Tuple normalv;
    bool inside;
    Tuple overPoint;
    Tuple underPoint;
    Tuple reflectv;

    Computations(Intersection i, Ray r)
    {
        t = i.t;
        object = i.object;
        point = r.position(t);
        eyev = -r.direction;
        normalv = object->normalAt(point);
        if (normalv.dot(eyev) < 0)
        {
            inside = true;
            normalv = -normalv;
        }
        else
        {
            inside = false;
        }
        overPoint = point + normalv * EPSILON;
        underPoint = point - normalv * EPSILON;
        reflectv = r.direction.reflect(normalv);
    }
};
#endif