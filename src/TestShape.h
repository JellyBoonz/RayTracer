#ifndef TESTSHAPE_H
#define TESTSHAPE_H

#include "Intersectable.h"
#include "Tuple.h"
#include "Material.h"

class TestShape : public Intersectable
{
private:
    Matrix mat;

public:
    Material material;

    TestShape() : Intersectable() {}
    const Tuple normalAt(Tuple worldPoint) const override
    {
        return Tuple::vector(worldPoint.x, worldPoint.y, worldPoint.z);
    }
    Matrix getTransform() override
    {
        return mat;
    }
    Matrix setTransform(Matrix t) override
    {
        mat = t;
        return mat;
    }
};

#endif