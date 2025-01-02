#include <gtest/gtest.h>
#include "Tuple.h"
#include "Color.h"
#include "Light.h"

TEST(LightTests, PointLight)
{
    Color intensity = Color(1.0, 1.0, 1.0);
    Tuple position = Tuple::point(0.0, 0.0, 0.0);
    Light light = Light(position, intensity);

    EXPECT_EQ(light.position, position);
    EXPECT_EQ(light.intensity, intensity);
}

TEST(LightTests, Lighting)
{
    Material m = Material();
    Tuple position = Tuple::point(0.0, 0.0, 0.0);
    Tuple eye = Tuple::vector(0.0, 0.0, -1.0);
    Tuple normal = Tuple::vector(0.0, 0.0, -1.0);
    Color intensity = Color(1.0, 1.0, 1.0);
    Light light = Light(Tuple::point(0.0, 0.0, -10.0), intensity);

    Color result = light.Lighting(position, normal, eye, m);

    EXPECT_EQ(result, Color(1.9, 1.9, 1.9));
}

TEST(LightTests, LightingEyeBetweenLightAndSurface)
{
    Material m = Material();
    Tuple position = Tuple::point(0.0, 0.0, 0.0);
    Tuple eye = Tuple::vector(0.0, sqrt(2) / 2, -sqrt(2) / 2);
    Tuple normal = Tuple::vector(0.0, 0.0, -1.0);
    Color intensity = Color(1.0, 1.0, 1.0);
    Light light = Light(Tuple::point(0.0, 0.0, -10.0), intensity);

    Color result = light.Lighting(position, normal, eye, m);

    EXPECT_EQ(result, Color(1.0, 1.0, 1.0));
}

TEST(LightTests, LightingEyeOppositeSurfaceLightOffset45)
{
    Material m = Material();
    Tuple position = Tuple::point(0.0, 0.0, 0.0);
    Tuple eye = Tuple::vector(0.0, 0.0, -1.0);
    Tuple normal = Tuple::vector(0.0, 0.0, -1.0);
    Color intensity = Color(1.0, 1.0, 1.0);
    Light light = Light(Tuple::point(0.0, 10.0, -10.0), intensity);

    Color result = light.Lighting(position, normal, eye, m);

    EXPECT_EQ(result, Color(0.7364, 0.7364, 0.7364));
}

TEST(LightTests, LightingEyeInPathOfReflectionVector)
{
    Material m = Material();
    Tuple position = Tuple::point(0.0, 0.0, 0.0);
    Tuple eye = Tuple::vector(0.0, -sqrt(2) / 2, -sqrt(2) / 2);
    Tuple normal = Tuple::vector(0.0, 0.0, -1.0);
    Color intensity = Color(1.0, 1.0, 1.0);
    Light light = Light(Tuple::point(0.0, 10.0, -10.0), intensity);

    Color result = light.Lighting(position, normal, eye, m);

    EXPECT_EQ(result, Color(1.6364, 1.6364, 1.6364));
}

TEST(LightTests, LightingLightBehindSurface)
{
    Material m = Material();
    Tuple position = Tuple::point(0.0, 0.0, 0.0);
    Tuple eye = Tuple::vector(0.0, 0.0, -1.0);
    Tuple normal = Tuple::vector(0.0, 0.0, -1.0);
    Color intensity = Color(1.0, 1.0, 1.0);
    Light light = Light(Tuple::point(0.0, 0.0, 10.0), intensity);

    Color result = light.Lighting(position, normal, eye, m);

    EXPECT_EQ(result, Color(0.1, 0.1, 0.1));
}