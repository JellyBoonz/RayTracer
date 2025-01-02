#ifndef TRANSFORMS_H
#define TRANSFORMS_H

#include "Matrix.h"
#include "Tuple.h"
#include <vector>

class Ray;

class Transforms
{
private:
    std::vector<Matrix> transformations;

public:
    Transforms();

    Transforms &translate(float tx, float ty, float tz);
    Transforms &scale(float sx, float sy, float sz);
    Transforms &rotateX(float angle);
    Transforms &rotateY(float angle);
    Transforms &rotateZ(float angle);
    Transforms &shear(float xy, float xz, float yx, float yz, float zx, float zy);
    Transforms &inverse();

    Matrix getTransformMat();
    Matrix viewTransform(Tuple from, Tuple to, Tuple up);
    void setTransformMat(std::vector<Matrix> m);

    Tuple applyTo(Tuple &tup);
    Ray applyTo(Ray &ray);
};

#endif // TRANSFORMS_H