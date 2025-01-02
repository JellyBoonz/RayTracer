#include "Sphere.h"

int Sphere::nextId = 0;

Sphere::Sphere() : id(nextId++) {}

Matrix Sphere::getTransform()
{
    return mat;
}

Matrix Sphere::setTransform(Matrix t)
{
    mat = t;
    return mat;
}

const Tuple Sphere::normalAt(Tuple worldPoint) const
{
    Tuple objectPoint = mat.inverse() * worldPoint;
    Tuple objectNormal = objectPoint - Tuple::point(0, 0, 0);
    Tuple worldNormal = mat.inverse().transpose() * objectNormal;
    worldNormal.w = 0;
    return worldNormal.normalize();
}