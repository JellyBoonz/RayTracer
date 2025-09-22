#include "World.h"
#include "Ray.h"
#include "Intersection.h"
#include "Intersections.h"
#include "Computations.h"
#include <algorithm>

World::World()
{
    auto s1 = std::make_shared<Sphere>();
    s1->material.color = Color(0.8, 1.0, 0.6);
    s1->material.diffuse = 0.7;
    s1->material.specular = 0.2;

    auto s2 = std::make_shared<Sphere>();
    Transforms t;
    t.scale(0.5, 0.5, 0.5);
    s2->setTransform(t.getTransformMat());

    objects.push_back(s1);
    objects.push_back(s2);
}

Intersections World::getIntersections(Ray &ray)
{
    std::vector<Intersection> xs;
    for (auto &object : objects)
    {
        std::vector<Intersection> objectIntersections = ray.intersect(object.get());
        xs.insert(xs.end(), objectIntersections.begin(), objectIntersections.end());
    }

    sort(xs.begin(), xs.end(), [](const Intersection &a, const Intersection &b)
         { return a.t < b.t; });
    return xs;
}

Color World::shadeHit(Computations comps, int remaining)
{
    Color surface = Color(0, 0, 0);
    bool shadowed = isShadowed(comps.overPoint, comps.object);
    surface = light.Lighting(comps.point, comps.normalv, comps.eyev, comps.object->material, *comps.object, shadowed);

    Color reflectedColor = this->reflectedColor(comps, remaining);

    return surface + reflectedColor;
}

Color World::colorAt(Ray &ray, const Intersectable *excludeObject, int remaining)
{
    auto intersections = getIntersections(ray);
    auto hit = intersections.hit();

    // Skip the excluded object to avoid self-intersection
    if (excludeObject && hit.object == excludeObject)
    {
        auto it = std::find_if(intersections.xs.begin(), intersections.xs.end(),
                               [&hit](const Intersection &i)
                               { return i.t > hit.t; });
        if (it != intersections.xs.end())
        {
            hit = *it;
        }
        else
        {
            hit = Intersection(std::numeric_limits<double>::infinity(), nullptr);
        }
    }

    // check if object pointer is valid hit.t >= 0
    if (hit.t >= 0 && hit.object != nullptr)
    {
        Computations comps(hit, ray);
        return shadeHit(comps, remaining);
    }

    return Color(0, 0, 0);
}

Color World::reflectedColor(Computations comps, int remaining)
{
    if (remaining <= 0)
    {
        return Color(0.0, 0.0, 0.0);
    }

    if (comps.object->material.reflective == 0.0)
    {
        return Color(0.0, 0.0, 0.0);
    }
    Ray reflectRay(comps.overPoint, comps.reflectv);
    Color c = colorAt(reflectRay, comps.object, remaining - 1);

    return c * comps.object->material.reflective;
}

bool World::isShadowed(Tuple &point, const Intersectable *excludeObject)
{
    Tuple v = light.position - point;
    float distance = (v).magnitude();
    Ray l(point, v.normalize());
    auto intersections = getIntersections(l);
    auto hit = intersections.hit();

    // Skip the excluded object to avoid self-intersection
    if (excludeObject && hit.object == excludeObject)
    {
        auto it = std::find_if(intersections.xs.begin(), intersections.xs.end(),
                               [&hit](const Intersection &i)
                               { return i.t > hit.t; });
        if (it != intersections.xs.end())
        {
            hit = *it;
        }
        else
        {
            hit = Intersection(std::numeric_limits<double>::infinity(), nullptr);
        }
    }

    if (hit.t < distance && hit.object != nullptr)
    {
        return true;
    }

    return false;
}

void World::clear()
{
    objects.clear();
}