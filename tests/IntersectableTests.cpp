#include <gtest/gtest.h>
#include "TestShape.h"
#include "Transforms.h"

TEST(IntersectableTests, DefaultTransformation)
{
    TestShape s = TestShape();
    EXPECT_EQ(s.getTransform(), Matrix::ID_MAT);
}

TEST(IntersectableTests, AssigningTransformation)
{
    TestShape s = TestShape();
    Transforms t;
    t.translate(2, 3, 4);
    s.setTransform(t.getTransformMat());
    EXPECT_EQ(s.getTransform(), t);
}

TEST(IntersectableTests, DefaultMaterial)
{
    TestShape s = TestShape();
    Material m = s.material;
    EXPECT_EQ(m, Material());
}

TEST(IntersectableTests, AssigningMaterial)
{
    TestShape s = TestShape();
    Material m;
    m.ambient = 1;
    s.material = m;
    EXPECT_EQ(s.material, m);
}