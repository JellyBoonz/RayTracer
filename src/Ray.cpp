#include "Ray.h"
#include "Tuple.h"
#include "Transforms.h"
#include "Intersection.h"
#include <algorithm>

Ray::Ray(Tuple o, Tuple dir) : origin(o), direction(dir) {}

Tuple Ray::position(float d)
{
    return origin + direction * d;
}

std::vector<Intersection> Ray::intersectSphere(Sphere &s)
{
    Transforms t;
    Matrix inverseTransform = s.getTransform().inverse();
    t.setTransformMat({inverseTransform});

    Ray transformed = t.applyTo(*this);

    std::vector<Intersection> xs;
    Tuple L = transformed.origin - s.center;
    float a = transformed.direction.dot(transformed.direction);
    float b = 2 * transformed.direction.dot(L);
    float c = L.dot(L) - pow(s.radius, 2.0);
    float discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
    {
        return xs;
    }
    else if (discriminant == 0)
    {
        float t = -b / (2 * a);
        Intersection i(t, &s);
        xs.push_back(i);
    }
    else
    {
        float sqrt_discriminant = sqrt(discriminant);
        float t1 = (-b - sqrt_discriminant) / (2 * a);
        float t2 = (-b + sqrt_discriminant) / (2 * a);
        Intersection i1(t1, &s);
        Intersection i2(t2, &s);
        xs.push_back(i1);
        xs.push_back(i2);
    }

    sort(xs.begin(), xs.end(), [](const Intersection &a, const Intersection &b)
         { return a.t < b.t; });
    return xs;
}

std::vector<Intersection> Ray::intersectPlane(Plane &p)
{
    std::vector<Intersection> xs;
    if (abs(direction.y) < EPSILON)
    {
        return xs;
    }

    float t = -origin.y / direction.y;
    Intersection i(t, &p);
    xs.push_back(i);
    return xs;
}

std::vector<Intersection> Ray::intersect(Intersectable *object)
{
    if (Sphere *s = dynamic_cast<Sphere *>(object))
    {
        return intersectSphere(*s);
    }
    else if (Plane *p = dynamic_cast<Plane *>(object))
    {
        return intersectPlane(*p);
    }
    else
    {
        std::vector<Intersection> xs;
        return xs;
    }
}