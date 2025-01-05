#include "Sphere.h"

int Sphere::nextId = 0;

Sphere::Sphere() : Intersectable(), id(nextId++) {}

Matrix Sphere::getTransform() const
{
    return Intersectable::mat;
}

Matrix Sphere::setTransform(Matrix t)
{
    Intersectable::mat = t;
    return Intersectable::mat;
}

const Tuple Sphere::normalAt(Tuple worldPoint) const
{
    Tuple objectPoint = mat.inverse() * worldPoint;
    Tuple objectNormal = objectPoint - Tuple::point(0, 0, 0);
    Tuple worldNormal = mat.inverse().transpose() * objectNormal;
    worldNormal.w = 0;
    return worldNormal.normalize();
}