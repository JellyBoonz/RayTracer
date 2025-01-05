#ifndef WORLD_H
#define WORLD_H

class Computations;

#include "Light.h"
#include "Intersectable.h"
#include "Sphere.h"
#include "Color.h"
#include "Transforms.h"
#include "Intersections.h"

class Ray;

class World
{
public:
    Light light = Light(Tuple::point(-10, 10, -10), Color(1.0, 1.0, 1.0));
    std::vector<std::shared_ptr<Intersectable>> objects;
    World();
    void update();
    void render();
    void clear();
    Color shadeHit(Computations comps);
    bool isShadowed(Tuple &point);
    Color colorAt(Ray &ray);
    Intersections getIntersections(Ray &ray);
};
#endif