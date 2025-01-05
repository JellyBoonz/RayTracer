#include <gtest/gtest.h>
#include "Sphere.h"
#include "Transforms.h"

TEST(SphereTests, NormalOnXAxis)
{
    Sphere s;
    Tuple p = Tuple::point(1, 0, 0);
    Tuple n = s.normalAt(p);
    Tuple expected = Tuple::vector(1, 0, 0);
    EXPECT_EQ(n, expected);
}

TEST(SphereTests, NormalOnYAxis)
{
    Sphere s;
    Tuple p = Tuple::point(0, 1, 0);
    Tuple n = s.normalAt(p);
    Tuple expected = Tuple::vector(0, 1, 0);
    EXPECT_EQ(n, expected);
}

TEST(SphereTests, NormalOnZAxis)
{
    Sphere s;
    Tuple p = Tuple::point(0, 0, 1);
    Tuple n = s.normalAt(p);
    Tuple expected = Tuple::vector(0, 0, 1);
    EXPECT_EQ(n, expected);
}

TEST(SphereTests, NormalAtNonAxialPoint)
{
    Sphere s;
    Tuple p = Tuple::point(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3);
    Tuple n = s.normalAt(p);
    Tuple expected = Tuple::vector(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3);
    EXPECT_EQ(n, expected);
}

TEST(SphereTests, NormalIsNormalized)
{
    Sphere s;
    Tuple p = Tuple::point(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3);
    Tuple n = s.normalAt(p);
    Tuple expected = n.normalize();
    EXPECT_EQ(n, expected);
}

TEST(SphereTests, NormalOnTranslatedSphere)
{
    Sphere s;
    Transforms t;
    t.translate(0, 1, 0);
    s.setTransform(t.getTransformMat());
    Tuple p = Tuple::point(0, 1.70711, -0.70711);
    Tuple n = s.normalAt(p);
    Tuple expected = Tuple::vector(0, 0.70711, -0.70711);
    EXPECT_EQ(n, expected);
}

TEST(SphereTests, NormalOnTransformedSphere)
{
    Sphere s;
    Transforms t;
    t.scale(1, 0.5, 1).rotateZ(M_PI / 5);
    s.setTransform(t.getTransformMat());
    Tuple p = Tuple::point(0, sqrt(2) / 2, -sqrt(2) / 2);
    Tuple n = s.normalAt(p);
    Tuple expected = Tuple::vector(0, 0.97014, -0.24254);
    EXPECT_EQ(n, expected);
}

TEST(SphereTest, SphereHasDefaultMaterial)
{
    Sphere s;
    Material m = s.material;
    EXPECT_EQ(m.color, Color(1.0, 1.0, 1.0));
    EXPECT_NEAR(m.ambient, 0.1, 1e-5);
    EXPECT_NEAR(m.diffuse, 0.9, 1e-5);
    EXPECT_NEAR(m.specular, 0.9, 1e-5);
    EXPECT_NEAR(m.shininess, 200.0, 1e-5);
}

TEST(SphereTest, SphereCanBeAssignedMaterial)
{
    Sphere s;
    Material m = Material();
    m.ambient = 1;
    s.material = m;
    EXPECT_EQ(s.material.ambient, m.ambient);
    EXPECT_EQ(s.material.color, m.color);
    EXPECT_EQ(s.material.diffuse, m.diffuse);
    EXPECT_EQ(s.material.specular, m.specular);
    EXPECT_EQ(s.material.shininess, m.shininess);
}

TEST(SphereTest, SphereIsAnIntersectableObject)
{
    Sphere s;
    Intersectable *i = &s;
    EXPECT_EQ(i->material.color, Color(1.0, 1.0, 1.0));
    EXPECT_NEAR(i->material.ambient, 0.1, 1e-5);
    EXPECT_NEAR(i->material.diffuse, 0.9, 1e-5);
    EXPECT_NEAR(i->material.specular, 0.9, 1e-5);
    EXPECT_NEAR(i->material.shininess, 200.0, 1e-5);
    EXPECT_EQ(i->getTransform(), s.getTransform());
}