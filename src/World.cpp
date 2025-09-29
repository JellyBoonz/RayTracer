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
    Color refractedColor = this->refractedColor(comps, remaining);

    Material material = comps.object->material;
    if (material.reflective > 0 && material.transparency > 0)
    {
        float reflectance = schlick(comps);
        return surface + reflectedColor * reflectance + refractedColor * (1 - reflectance);
    }

    return surface + reflectedColor + refractedColor;
}

float World::schlick(Computations comps)
{
    float cos = comps.eyev.dot(comps.normalv);

    // Total internal reflection can only occur if n1 > n2
    if (comps.n1 > comps.n2)
    {
        float n = comps.n1 / comps.n2;
        float sin2T = n * n * (1.0 - cos * cos);
        if (sin2T > 1.0) // Impossible sin angle. TIR
        {
            return 1.0;
        }

        float cosT = sqrt(1.0 - sin2T);
        cos = cosT; // When n1 > n2, use cosT instead
    }

    float r0 = ((comps.n1 - comps.n2) / (comps.n1 + comps.n2));
    r0 = r0 * r0;
    return r0 + (1 - r0) * pow((1 - cos), 5);
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
        std::vector<Intersection> allIntersections = intersections.xs;
        Computations comps(hit, ray, allIntersections);
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

Color World::refractedColor(Computations comps, int remaining)
{
    if (comps.object->material.transparency == 0.0 || remaining <= 0)
    {
        return Color(0.0, 0.0, 0.0);
    }
    // Snell's Law
    float nRatio = comps.n1 / comps.n2;
    float cosI = comps.eyev.dot(comps.normalv);
    float sin2T = nRatio * nRatio * (1 - cosI * cosI);

    if (sin2T > 1.0)
    {
        return Color(0.0, 0.0, 0.0);
    }
    float cosT = sqrt(1.0 - sin2T);
    Tuple direction = comps.normalv * (nRatio * cosI - cosT) - comps.eyev * nRatio;
    Ray refractRay(comps.underPoint, direction);

    Color c = colorAt(refractRay, nullptr, remaining - 1) * comps.object->material.transparency;

    return c;
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