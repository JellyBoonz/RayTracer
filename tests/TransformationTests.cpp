#include "Transforms.h"
#include "Tuple.h"
#include "Sphere.h"
#include <gtest/gtest.h>
#include <cmath>

TEST(TransformationTests, Translate)
{
    Transforms t;
    Tuple p = Tuple::point(-3, 4, 5);
    Tuple result = t.translate(5, -3, 2).applyTo(p);
    EXPECT_EQ(result.x, 2);
    EXPECT_EQ(result.y, 1);
    EXPECT_EQ(result.z, 7);
}

TEST(TransformationTests, InverseTranslate)
{
    Transforms t;
    Tuple p = Tuple::point(-3, 4, 5);
    Tuple result = t.translate(5, -3, 2).inverse().applyTo(p);
    EXPECT_EQ(result.x, -8);
    EXPECT_EQ(result.y, 7);
    EXPECT_EQ(result.z, 3);
}

TEST(TransformationTests, TranslateDoesNotWorkForVectors)
{
    Transforms t;
    Tuple v = Tuple::vector(5, -3, 2);
    Tuple result = t.translate(5, -3, 2).applyTo(v);
    EXPECT_EQ(result, Tuple::vector(5, -3, 2));
}

TEST(TransformationTests, ScalePoint)
{
    Transforms t;
    Tuple p = Tuple::point(-4, 6, 8);
    Tuple result = t.scale(2, 3, 4).applyTo(p);
    EXPECT_EQ(result, Tuple::point(-8, 18, 32));
}

TEST(TransformationTests, ScaleVector)
{
    Transforms t;
    Tuple v = Tuple::point(-4, 6, 8);
    Tuple result = t.scale(2, 3, 4).applyTo(v);
    EXPECT_EQ(result, Tuple::point(-8, 18, 32));
}

TEST(TransformationTests, InverseScaleVector)
{
    Transforms t;
    Tuple v = Tuple::point(-4, 6, 8);
    Tuple result = t.scale(2, 3, 4).inverse().applyTo(v);
    EXPECT_EQ(result, Tuple::point(-2, 2, 2));
}

TEST(TransformationTest, ReflectionByScaling)
{
    Transforms t;
    Tuple p = Tuple::point(2, 3, 4);
    Tuple result = t.scale(-1, 1, 1).applyTo(p);
    EXPECT_EQ(result, Tuple::point(-2, 3, 4));
}

TEST(TransformationTest, InverseRotateX)
{
    Transforms t;
    Tuple p = Tuple::point(0, 1, 0);
    Tuple result = t.rotateX(M_PI / 4).inverse().applyTo(p);
    EXPECT_EQ(result, Tuple::point(0, sqrt(2) / 2, -sqrt(2) / 2));
}

TEST(TransformationTest, RotateX)
{
    Transforms t;
    Tuple p = Tuple::point(0, 1, 0);
    Tuple result1 = t.rotateX(M_PI / 4).applyTo(p);
    EXPECT_EQ(result1, Tuple::point(0, sqrt(2) / 2, sqrt(2) / 2));

    t = Transforms();
    Tuple result2 = t.rotateX(M_PI / 2).applyTo(p);
    EXPECT_EQ(result2, Tuple::point(0, 0, 1));
}

TEST(TransformationTest, RotateY)
{
    Transforms t;
    Tuple p = Tuple::point(0, 0, 1);
    Tuple result1 = t.rotateY(M_PI / 4).applyTo(p);
    EXPECT_EQ(result1, Tuple::point(sqrt(2) / 2, 0, sqrt(2) / 2));

    t = Transforms();
    Tuple result2 = t.rotateY(M_PI / 2).applyTo(p);
    EXPECT_EQ(result2, Tuple::point(1, 0, 0));
}

TEST(TransformationTest, RotateZ)
{
    Transforms t;
    Tuple p = Tuple::point(0, 1, 0);
    Tuple result1 = t.rotateZ(M_PI / 4).applyTo(p);
    EXPECT_EQ(result1, Tuple::point(-sqrt(2) / 2, sqrt(2) / 2, 0));

    t = Transforms();
    Tuple result2 = t.rotateZ(M_PI / 2).applyTo(p);
    EXPECT_EQ(result2, Tuple::point(-1, 0, 0));
}

TEST(TransformationTests, ShearingX)
{
    Transforms t;
    Tuple p = Tuple::point(2, 3, 4);
    Tuple result = t.shear(1, 0, 0, 0, 0, 0).applyTo(p);
    EXPECT_EQ(result, Tuple::point(5, 3, 4));
}

TEST(TransformationTests, ShearingY)
{
    Transforms t;
    Tuple p = Tuple::point(2, 3, 4);
    Tuple result = t.shear(0, 0, 1, 0, 0, 0).applyTo(p);
    EXPECT_EQ(result, Tuple::point(2, 5, 4));
}

TEST(TransformationTests, ShearingZ)
{
    Transforms t;
    Tuple p = Tuple::point(2, 3, 4);
    Tuple result = t.shear(0, 0, 0, 0, 1, 0).applyTo(p);
    EXPECT_EQ(result, Tuple::point(2, 3, 6));
}

TEST(TransformationTests, ShearingXYZ)
{
    Transforms t;
    Tuple p = Tuple::point(2, 3, 4);
    Tuple result = t.shear(1, 0, 0, 1, 0, 1).applyTo(p);
    EXPECT_EQ(result, Tuple::point(5, 7, 7));
}

TEST(TransformationTests, ShearingTransformComposition)
{
    Transforms t;
    Tuple p = Tuple::point(2, 3, 4);
    Tuple result = t.shear(1, 1, 1, 0, 0, 0).applyTo(p);
    EXPECT_EQ(result, Tuple::point(9, 5, 4));
}

TEST(TransformationTests, ApplyTransforms)
{
    Transforms t;
    Tuple p = Tuple::point(1, 0, 1);
    Tuple result = t.translate(10, 5, 7).scale(5, 5, 5).rotateX(M_PI / 2).applyTo(p);
    EXPECT_EQ(result, Tuple::point(15, 0, 7));
}

TEST(TransformationTests, ApplyTransformToSphere)
{
    Transforms t;
    Sphere s;
    t.translate(2, 3, 4);
    s.setTransform(t.getTransformMat());
    EXPECT_EQ(s.getTransform(), t.getTransformMat());
}

TEST(TransformationTests, DefaultCameraOrientation)
{
    Tuple from = Tuple::point(0, 0, 0);
    Tuple to = Tuple::point(0, 0, -1);
    Tuple up = Tuple::vector(0, 1, 0);
    Transforms t;
    Matrix viewTransform = t.viewTransform(from, to, up);
    EXPECT_EQ(viewTransform, Matrix::ID_MAT);
}

TEST(TransformationTests, ViewTransformPositiveZ)
{
    Tuple from = Tuple::point(0, 0, 0);
    Tuple to = Tuple::point(0, 0, 1);
    Tuple up = Tuple::vector(0, 1, 0);
    Transforms t;
    Matrix viewTransform = t.viewTransform(from, to, up);
    EXPECT_EQ(viewTransform, t.scale(-1, 1, -1).getTransformMat());
}

TEST(TransformationTests, ViewTransformMovesWorld)
{
    Tuple from = Tuple::point(0, 0, 8);
    Tuple to = Tuple::point(0, 0, 0);
    Tuple up = Tuple::vector(0, 1, 0);
    Transforms t;
    Matrix viewTransform = t.viewTransform(from, to, up);
    EXPECT_EQ(viewTransform, t.translate(0, 0, -8).getTransformMat());
}

TEST(TransformationTests, ArbitraryViewTransform)
{
    Tuple from = Tuple::point(1, 3, 2);
    Tuple to = Tuple::point(4, -2, 8);
    Tuple up = Tuple::vector(1, 1, 0);
    Transforms t;
    Matrix viewTransform = t.viewTransform(from, to, up);
    Matrix expected = {
        {-0.50709, 0.50709, 0.67612, -2.36643},
        {0.76772, 0.60609, 0.12122, -2.82843},
        {-0.35857, 0.59761, -0.71714, 0.00000},
        {0.00000, 0.00000, 0.00000, 1.00000}};

    for (int row = 0; row < 4; ++row)
    {
        for (int col = 0; col < 4; ++col)
        {
            EXPECT_NEAR(viewTransform.at(row, col), expected.at(row, col), 1e-5);
        }
    }
}