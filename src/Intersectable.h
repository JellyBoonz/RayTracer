#ifndef INTERSECTABLE_H
#define INTERSECTABLE_H

#include "Material.h"
#include "Matrix.h"
#include "Tuple.h"

class Intersectable
{
protected:
    Matrix mat;

public:
    Material material;
    virtual ~Intersectable() = default;
    virtual Matrix getTransform()
    {
        return mat;
    };
    virtual const Tuple normalAt(Tuple worldPoint) const = 0;
};

#endif