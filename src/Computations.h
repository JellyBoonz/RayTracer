#ifndef COMPUTATIONS_H
#define COMPUTATIONS_H

#include "Intersection.h"
#include "Ray.h"

const float EPSILON = 0.001f;

class Computations
{
public:
    float t;
    float n1; // Refractive index of the material being exited
    float n2; // Refractive index of the material being entered
    const Intersectable *object;
    Tuple point;
    Tuple eyev;
    Tuple normalv;
    bool inside;
    Tuple overPoint;
    Tuple underPoint;
    Tuple reflectv;

    Computations(Intersection i, Ray r, std::vector<Intersection> xs = {})
    {
        if (xs.empty())
        {
            xs.push_back(i);
        }

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

        // Compute n1 and n2 for refraction
        std::vector<const Intersectable *> containers;
        n1 = 1.0;
        n2 = 1.0;

        for (size_t it = 0; it < xs.size(); it++)
        {
            if (xs[it].t >= 0 && xs[it].object != nullptr)
            {
                n1 = containers.empty() ? 1.0 : containers.back()->material.refractiveIndex;
            }
            if (std::find(containers.begin(), containers.end(), xs[it].object) != containers.end())
            {
                containers.erase(std::remove(containers.begin(), containers.end(), xs[it].object), containers.end());
            }
            else
            {
                containers.push_back(xs[it].object);
            }
            if (xs[it].t >= 0 && xs[it].object != nullptr)
            {
                n2 = containers.empty() ? 1.0 : containers.back()->material.refractiveIndex;
            }
        }
    }
};
#endif