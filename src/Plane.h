#ifndef PLANE_H
#define PLANE_H

#include "Intersectable.h"
#include "Material.h"

class Plane : public Intersectable
{
public:
    Plane() : Intersectable() {}
    const Tuple normalAt(Tuple worldPoint) const override
    {
        return Tuple::vector(0, 1, 0);
    }
};

#endif