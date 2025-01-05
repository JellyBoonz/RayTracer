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
    Intersectable() : mat(Matrix::ID_MAT) {}
    virtual ~Intersectable() = default;
    virtual Matrix getTransform() const
    {
        return mat;
    };
    virtual Matrix setTransform(Matrix t)
    {
        mat = t;
        return mat;
    };
    virtual const Tuple normalAt(Tuple worldPoint) const = 0;
};

#endif