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

    public:
    Tuple center = Tuple::point(0, 0, 0);
    float radius = 1.0;

    Sphere();

    static Sphere glassSphere();
    Matrix getTransform() const override;
    Matrix setTransform(Matrix t) override;

    const Tuple normalAt(Tuple worldPoint) const override;
};

#endif