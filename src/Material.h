#ifndef MATERIAL_H
#define MATERIAL_H

#include "Color.h"

class Material
{
public:
    Color color;
    float ambient;
    float diffuse;
    float specular;
    float shininess;

    Material() : color(Color(1.0, 1.0, 1.0)), ambient(0.1), diffuse(0.9), specular(0.9), shininess(200.0) {}

    Material(Color color, float ambient, float diffuse, float specular, float shininess)
        : color(color), ambient(ambient), diffuse(diffuse), specular(specular), shininess(shininess) {}
};

#endif