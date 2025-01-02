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

std::vector<Intersection> World::getIntersections(Ray &ray)
{
    std::vector<Intersection> xs;
    for (auto &object : objects)
    {
        if (auto sphere = std::dynamic_pointer_cast<Sphere>(object))
        {
            std::vector<Intersection> objectIntersections = ray.intersect(*sphere);
            xs.insert(xs.end(), objectIntersections.begin(), objectIntersections.end());
        }
    }

    sort(xs.begin(), xs.end(), [](const Intersection &a, const Intersection &b)
         { return a.t < b.t; });
    return xs;
}

Color World::shadeHit(Computations comps)
{
    Color surface = Color(0, 0, 0);
    for (auto &object : objects)
    {
        if (auto sphere = std::dynamic_pointer_cast<Sphere>(object))
        {
            surface = light.Lighting(comps.point, comps.normalv, comps.eyev, comps.object->material);
        }
    }
    return surface;
}

Color World::colorAt(Ray &ray)
{
    auto intersections = getIntersections(ray);
    if (intersections.empty())
    {
        return Color(0, 0, 0);
    }

    for (const auto &intersection : intersections)
    {
        if (intersection.t >= 0)
        {
            Computations comps(intersection, ray);
            return shadeHit(comps);
        }
    }

    return Color(0, 0, 0);
}

void World::clear()
{
    objects.clear();
}