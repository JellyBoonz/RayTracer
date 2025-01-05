#ifndef INTERSECTIONS_H
#define INTERSECTIONS_H

#include "Intersection.h"
#include <iostream>
#include <algorithm>
#include <limits>

using std::vector;

class Intersections
{
public:
    vector<Intersection> xs;

    Intersections(vector<Intersection> list)
    {
        xs = list;
        sort(xs.begin(), xs.end(), [](const Intersection &a, const Intersection &b)
             { return a.t < b.t; });
    }

    bool empty() const
    {
        return xs.empty();
    }

    Intersection hit()
    {
        for (const auto &intersection : xs)
        {
            if (intersection.t >= 0)
            {
                return intersection;
            }
        }
        // No valid intersection found
        return Intersection();
    }
};

#endif
