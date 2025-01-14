#ifndef LIGHT_H
#define LIGHT_H

#include "Tuple.h"
#include "Color.h"
#include "Material.h"
#include "Intersectable.h"

class Light
{
public:
    Tuple position;
    Color intensity;

    Light(Tuple position, Color intensity);
    Color Lighting(Tuple point, Tuple normal, Tuple eye, Material material, const Intersectable &object, bool inShadow = false);
};

#endif