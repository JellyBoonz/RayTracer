#ifndef SPHERE_H
#define SPHERE_H

#include "Tuple.h"
#include "Intersectable.h"
#include "Matrix.h"
#include "Material.h"

class Sphere : public Intersectable
{
private:
    int id;
    static int nextId; // Static allows the data to persist across all instantiations.
    Matrix mat = Matrix::ID_MAT;

public:
    Tuple center = Tuple::point(0, 0, 0);
    float radius = 1.0;

    Sphere();

    Matrix getTransform() override;
    Matrix setTransform(Matrix t);

    const Tuple normalAt(Tuple worldPoint) const override;
};

#endif