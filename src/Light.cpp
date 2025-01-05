#include "Light.h"

Light::Light(Tuple position, Color intensity) : position(position), intensity(intensity) {}

Color Light::Lighting(Tuple point, Tuple normal, Tuple eye, Material material, const Intersectable &object, bool inShadow)
{
    Color color;

    if (material.pattern)
    {
        color = material.pattern->patternAtObject(object, point);
    }
    else
    {
        color = material.color;
    }

    Color effectiveColor = color * intensity;
    Tuple lightVector = (position - point).normalize();
    Color ambient = effectiveColor * material.ambient;
    double lightDotNormal = lightVector.dot(normal);

    Color diffuse;
    Color specular;

    if (lightDotNormal < 0 || inShadow)
    {
        diffuse = Color(0.0, 0.0, 0.0);
        specular = Color(0.0, 0.0, 0.0);
    }
    else
    {
        // Modify the diffuse color based on the position
        diffuse = effectiveColor * material.diffuse * lightDotNormal;

        Tuple reflectVector = (-lightVector).reflect(normal);
        double reflectDotEye = reflectVector.dot(eye);

        if (reflectDotEye <= 0)
        {
            specular = Color(0.0, 0.0, 0.0);
        }
        else
        {
            double factor = pow(reflectDotEye, material.shininess);
            specular = intensity * material.specular * factor;
        }
    }

    return ambient + diffuse + specular;
}