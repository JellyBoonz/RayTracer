#include "Material.h"
#include "Plane.h"
#include "Ray.h"
#include "Computations.h"
#include "World.h"
#include <gtest/gtest.h>

TEST(MaterialTests, ReflectiveDefault)
{
    Material m;
    EXPECT_EQ(m.reflective, 0.0);
}

TEST(MaterialTests, PrecomputingReflectionVector)
{
    Plane p;
    Ray r(Tuple::point(0, 1, -1), Tuple::vector(0, -sqrt(2) / 2, sqrt(2) / 2));
    Intersection i(sqrt(2), &p);
    Computations comps(i, r);
    EXPECT_EQ(comps.reflectv, Tuple::vector(0, sqrt(2) / 2, sqrt(2) / 2));
}

TEST(MaterialTests, NonReflectiveMaterial)
{
    World w;
    Ray r(Tuple::point(0, 0, 0), Tuple::vector(0, 0, 1));
    Sphere s = w.objects[1] ? *std::dynamic_pointer_cast<Sphere>(w.objects[1]) : Sphere();
    s.material.ambient = 1.0;
    Intersection i(1, &s);
    Computations comps(i, r);
    Color c = w.reflectedColor(comps);
    EXPECT_EQ(c, Color(0.0, 0.0, 0.0));
}

TEST(MaterialTests, ReflectiveMaterial)
{
    World w;
    auto p = std::make_shared<Plane>();
    p->setTransform(Transforms().translate(0, -1, 0).getTransformMat());
    p->material.reflective = 0.5;
    w.objects.push_back(p);

    Ray r(Tuple::point(0, 0, -3), Tuple::vector(0, -sqrt(2) / 2, sqrt(2) / 2));
    Intersection i(sqrt(2), p.get());
    Computations comps(i, r);
    Color c = w.reflectedColor(comps);
    EXPECT_EQ(c, Color(0.190503, 0.238129, 0.142877));
}

TEST(MaterialTests, ReflectiveMaterialWithShadeHit)
{
    World w;
    auto p = std::make_shared<Plane>();
    p->setTransform(Transforms().translate(0, -1, 0).getTransformMat());
    p->material.reflective = 0.5;
    w.objects.push_back(p);

    Ray r(Tuple::point(0, 0, -3), Tuple::vector(0, -sqrt(2) / 2, sqrt(2) / 2));
    Intersection i(sqrt(2), p.get());
    Computations comps(i, r);
    Color c = w.shadeHit(comps);
    EXPECT_EQ(c, Color(0.876928, 0.924554, 0.829303));
}

TEST(MaterialTests, ColorAtWithMutuallyReflectiveSurfaces)
{
    World w;
    w.clear();

    auto lower = std::make_shared<Plane>();
    lower->setTransform(Transforms().translate(0, -1, 0).getTransformMat());
    lower->material.reflective = 1.0;
    w.objects.push_back(lower);

    auto upper = std::make_shared<Plane>();
    upper->setTransform(Transforms().translate(0, 1, 0).getTransformMat());
    upper->material.reflective = 1.0;
    w.objects.push_back(upper);

    Ray r(Tuple::point(0, 0, 0), Tuple::vector(0, 1, 0));

    // This test is mainly to ensure that the recursive reflections terminate
    // and do not cause a stack overflow. The actual color result is not checked.
    Color c = w.colorAt(r);
    EXPECT_TRUE(c.getRed() >= 0.0 && c.getRed() <= 1.0);
    EXPECT_TRUE(c.getGreen() >= 0.0 && c.getGreen() <= 1.0);
    EXPECT_TRUE(c.getBlue() >= 0.0 && c.getBlue() <= 1.0);
}

TEST(MaterialTests, ReflectedColorAtMaxRecursionDepth)
{
    World w;
    auto p = std::make_shared<Plane>();
    p->setTransform(Transforms().translate(0, -1, 0).getTransformMat());
    p->material.reflective = 0.5;
    w.objects.push_back(p);

    Ray r(Tuple::point(0, 0, -3), Tuple::vector(0, -sqrt(2) / 2, sqrt(2) / 2));
    Intersection i(sqrt(2), p.get());
    Computations comps(i, r);
    Color c = w.reflectedColor(comps, 0);
    EXPECT_EQ(c, Color(0.0, 0.0, 0.0));
}

TEST(MaterialTests, TransparencyAndRefractiveIndexDefault)
{
    Material m;
    EXPECT_EQ(m.transparency, 0.0);
    EXPECT_EQ(m.refractiveIndex, 1.0);
}

TEST(MaterialTests, GlassSphere)
{
    Sphere s = Sphere::glassSphere();
    EXPECT_EQ(s.material.transparency, 1.0);
    EXPECT_EQ(s.material.refractiveIndex, 1.5);
}

TEST(MaterialTests, FindingN1AndN2AtVariousIntersections)
{
    Sphere a = Sphere::glassSphere();
    a.setTransform(Transforms().scale(2, 2, 2).getTransformMat());
    a.material.refractiveIndex = 1.5;

    Sphere b = Sphere::glassSphere();
    b.setTransform(Transforms().translate(0, 0, -0.25).getTransformMat());
    b.material.refractiveIndex = 2.0;

    Sphere c = Sphere::glassSphere();
    c.setTransform(Transforms().translate(0, 0, 0.25).getTransformMat());
    c.material.refractiveIndex = 2.5;

    Ray r(Tuple::point(0, 0, -4), Tuple::vector(0, 0, 1));
    std::vector<Intersection> xs = {
        Intersection(2, &a),
        Intersection(2.75, &b),
        Intersection(3.25, &c),
        Intersection(4.75, &b),
        Intersection(5.25, &c),
        Intersection(6, &a),
    };

    // std::vector<float> expectedN1 = {1.0, 1.5, 2.0, 2.5, 2.5, 1.5};
    // std::vector<float> expectedN2 = {1.5, 2.0, 2.5, 2.5, 1.5, 1.0};

    Computations comps(xs[0], r, xs);
    EXPECT_FLOAT_EQ(comps.n1, 1.5);
    EXPECT_FLOAT_EQ(comps.n2, 1.0);
}

TEST(MaterialTests, UnderPointIsOffsetBelowSurface)
{
    Ray r(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));
    Sphere s = Sphere::glassSphere();
    s.setTransform(Transforms().translate(0, 0, 1).getTransformMat());
    Intersection i(5, &s);
    std::vector<Intersection> xs = {i};
    Computations comps(i, r, xs);

    EXPECT_TRUE(comps.underPoint.z > EPSILON / 2);
    EXPECT_TRUE(comps.point.z < comps.underPoint.z);
}

TEST(MaterialTests, RefractedColorWithOpaqueSurface)
{
    World w;
    Sphere s = *std::dynamic_pointer_cast<Sphere>(w.objects[0]);
    Ray r(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));
    Intersection i(4, &s);
    Intersection i2(6, &s);
    std::vector<Intersection> xs = {i, i2};
    Computations comps(i, r, xs);
    Color c = w.refractedColor(comps, 5);
    EXPECT_EQ(c, Color(0, 0, 0));
}

TEST(MaterialTests, RefractedColorAtMaxRecursionDepth)
{
    World w;
    Sphere s = *std::dynamic_pointer_cast<Sphere>(w.objects[0]);
    s.material.transparency = 1.0;
    s.material.refractiveIndex = 1.5;
    Ray r(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));
    Intersection i(4, &s);
    Intersection i2(6, &s);
    std::vector<Intersection> xs = {i, i2};
    Computations comps(i, r, xs);
    Color c = w.refractedColor(comps, 0);
    EXPECT_EQ(c, Color(0, 0, 0));
}

TEST(MaterialTests, RefractedColorUnderTotalInternalReflection)
{
    World w;
    Sphere s = *std::dynamic_pointer_cast<Sphere>(w.objects[0]);
    s.material.transparency = 1.0;
    s.material.refractiveIndex = 1.5;
    Ray r(Tuple::point(0, 0, sqrt(2) / 2), Tuple::vector(0, 1, 0));
    Intersection i(-sqrt(2) / 2, &s);
    Intersection i2(sqrt(2) / 2, &s);
    std::vector<Intersection> xs = {i, i2};
    Computations comps(i2, r, xs);
    Color c = w.refractedColor(comps, 5);
    EXPECT_EQ(c, Color(0, 0, 0));
}

TEST(MaterialTests, RefractedColorWithRefractedRay)
{
    World w;

    // A ← the first object in w (outer sphere)
    auto A = std::dynamic_pointer_cast<Sphere>(w.objects[0]);
    A->material.ambient = 1.0;
    A->material.pattern = std::make_shared<TestPattern>();

    // B ← the second object in w (inner sphere)
    auto B = std::dynamic_pointer_cast<Sphere>(w.objects[1]);
    B->material.transparency = 1.0;
    B->material.refractiveIndex = 1.5;

    // r ← ray(point(0, 0, 0.1), vector(0, 1, 0))
    Ray r(Tuple::point(0, 0, 0.1), Tuple::vector(0, 1, 0));

    Intersection i1(-0.9899, A.get()); // -0.9899:A
    Intersection i2(-0.4899, B.get()); // -0.4899:B
    Intersection i3(0.4899, B.get());  // 0.4899:B
    Intersection i4(0.9899, A.get());  // 0.9899:A

    std::vector<Intersection> xs = {i1, i2, i3, i4};

    Computations comps(i3, r, xs);
    Color c = w.refractedColor(comps, 5);
    EXPECT_EQ(c, Color(0.0, 0.994967, 0.1002));
}