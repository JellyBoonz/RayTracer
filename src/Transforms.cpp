#include "Transforms.h"
#include "Ray.h"
#include <cmath>

Transforms::Transforms()
{
    // Start with an identity matrix
    transformations.push_back(Matrix::ID_MAT);
}

Transforms &Transforms::translate(float tx, float ty, float tz)
{
    Matrix translation = {
        {1, 0, 0, tx},
        {0, 1, 0, ty},
        {0, 0, 1, tz},
        {0, 0, 0, 1}};
    transformations.push_back(translation);
    return *this;
}

Transforms &Transforms::scale(float sx, float sy, float sz)
{
    Matrix scaling = {
        {sx, 0, 0, 0},
        {0, sy, 0, 0},
        {0, 0, sz, 0},
        {0, 0, 0, 1}};
    transformations.push_back(scaling);
    return *this;
}

Transforms &Transforms::rotateX(float angle)
{
    Matrix rotationX = {
        {1, 0, 0, 0},
        {0, cos(angle), -sin(angle), 0},
        {0, sin(angle), cos(angle), 0},
        {0, 0, 0, 1}};
    transformations.push_back(rotationX);
    return *this;
}

Transforms &Transforms::rotateY(float angle)
{
    Matrix rotationY = {
        {cos(angle), 0, sin(angle), 0},
        {0, 1, 0, 0},
        {-sin(angle), 0, cos(angle), 0},
        {0, 0, 0, 1}};
    transformations.push_back(rotationY);
    return *this;
}

Transforms &Transforms::rotateZ(float angle)
{
    Matrix rotationZ = {
        {cos(angle), -sin(angle), 0, 0},
        {sin(angle), cos(angle), 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}};
    transformations.push_back(rotationZ);
    return *this;
}

Transforms &Transforms::shear(float xy, float xz, float yx, float yz, float zx, float zy)
{
    Matrix shear = {
        {1, xy, xz, 0},
        {yx, 1, yz, 0},
        {zx, zy, 1, 0},
        {0, 0, 0, 1}};
    transformations.push_back(shear);
    return *this;
}

Transforms &Transforms::inverse()
{
    transformations.back() = transformations.back().inverse();
    return *this;
}

Matrix Transforms::getTransformMat()
{
    Matrix combinedTransform = Matrix::ID_MAT;
    for (const auto &transform : transformations)
    {
        combinedTransform = combinedTransform * transform;
    }

    return combinedTransform;
}

Matrix Transforms::viewTransform(Tuple from, Tuple to, Tuple up)
{
    Tuple forward = (to - from).normalize();
    Tuple left = forward.cross(up.normalize());
    Tuple trueUp = left.cross(forward);
    Transforms t;

    //Orienting the world such that it is aligned with the camera orientation
    Matrix orientation = {
        {left.x, left.y, left.z, 0},
        {trueUp.x, trueUp.y, trueUp.z, 0},
        {-forward.x, -forward.y, -forward.z, 0},
        {0, 0, 0, 1}};

    // Translating the world away from the camera to put the camera at the origin
    return orientation * t.translate(-from.x, -from.y, -from.z).getTransformMat();
}

Tuple Transforms::applyTo(Tuple &tup)
{
    // Combine all transformations from left to right
    Matrix combinedTransform = Matrix::ID_MAT;
    for (const auto &transform : transformations)
    {
        combinedTransform = combinedTransform * transform;
    }

    return combinedTransform * tup;
}

void Transforms::setTransformMat(std::vector<Matrix> m)
{
    transformations = m;
}

Ray Transforms::applyTo(Ray &ray)
{
    Tuple newOrigin = applyTo(ray.origin);
    Tuple newDirection = applyTo(ray.direction);
    return Ray(newOrigin, newDirection);
}
