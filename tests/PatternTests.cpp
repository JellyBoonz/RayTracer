#include <gtest/gtest.h>
#include "Pattern.h"
#include "Sphere.h"
#include "Transforms.h"

TEST(PatternTests, CreateStripePattern)
{
    Color a = Color(1, 1, 1);
    Color b = Color(0, 0, 0);
    StripePattern pattern = StripePattern(a, b);

    EXPECT_EQ(pattern.a, a);
    EXPECT_EQ(pattern.b, b);
}

TEST(PatternTests, StripePatternConstantInY)
{
    Color a = Color(1, 1, 1);
    Color b = Color(0, 0, 0);
    StripePattern pattern = StripePattern(a, b);

    EXPECT_EQ(pattern.patternAt(Tuple::point(0, 0, 0)), a);
    EXPECT_EQ(pattern.patternAt(Tuple::point(0, 1, 0)), a);
    EXPECT_EQ(pattern.patternAt(Tuple::point(0, 2, 0)), a);
}

TEST(PatternTests, StripePatternConstantInZ)
{
    Color a = Color(1, 1, 1);
    Color b = Color(0, 0, 0);
    StripePattern pattern = StripePattern(a, b);

    EXPECT_EQ(pattern.patternAt(Tuple::point(0, 0, 0)), a);
    EXPECT_EQ(pattern.patternAt(Tuple::point(0, 0, 1)), a);
    EXPECT_EQ(pattern.patternAt(Tuple::point(0, 0, 2)), a);
}

TEST(PatternTests, StripePatternAlternatesInX)
{
    Color a = Color(1, 1, 1);
    Color b = Color(0, 0, 0);
    StripePattern pattern = StripePattern(a, b);

    EXPECT_EQ(pattern.patternAt(Tuple::point(0, 0, 0)), a);
    EXPECT_EQ(pattern.patternAt(Tuple::point(0.9, 0, 0)), a);
    EXPECT_EQ(pattern.patternAt(Tuple::point(1, 0, 0)), b);
    EXPECT_EQ(pattern.patternAt(Tuple::point(-0.1, 0, 0)), b);
    EXPECT_EQ(pattern.patternAt(Tuple::point(-1, 0, 0)), b);
}

TEST(PatternTests, StripesWithObjectTransform)
{
    Sphere s;
    StripePattern pattern = StripePattern(Color(1, 1, 1), Color(0, 0, 0));
    Transforms t;
    t.scale(2, 2, 2);
    s.setTransform(t.getTransformMat());
    Color c = pattern.patternAtObject(s, Tuple::point(1.5, 0, 0));

    EXPECT_EQ(c, Color(1, 1, 1));
}

TEST(PatternTests, StripesWithPatternTransform)
{
    Sphere s;
    StripePattern pattern = StripePattern(Color(1, 1, 1), Color(0, 0, 0));
    Transforms t;
    t.scale(2, 2, 2);
    pattern.setTransform(t.getTransformMat());
    Color c = pattern.patternAtObject(s, Tuple::point(1.5, 0, 0));

    EXPECT_EQ(c, Color(1, 1, 1));
}

TEST(PatternTests, StripesWithObjectAndPatternTransform)
{
    Sphere s;
    StripePattern pattern = StripePattern(Color(1, 1, 1), Color(0, 0, 0));
    Transforms t1;
    t1.scale(2, 2, 2);
    s.setTransform(t1.getTransformMat());
    Transforms t2;
    t2.translate(0.5, 0, 0);
    pattern.setTransform(t2.getTransformMat());
    Color c = pattern.patternAtObject(s, Tuple::point(2.5, 0, 0));

    EXPECT_EQ(c, Color(1, 1, 1));
}

TEST(PatternTests, GradientLinearlyInterpolating)
{
    GradientPattern pattern = GradientPattern(Color(1, 1, 1), Color(0, 0, 0));

    EXPECT_EQ(pattern.patternAt(Tuple::point(0, 0, 0)), Color(1, 1, 1));
    EXPECT_EQ(pattern.patternAt(Tuple::point(0.25, 0, 0)), Color(0.75, 0.75, 0.75));
    EXPECT_EQ(pattern.patternAt(Tuple::point(0.5, 0, 0)), Color(0.5, 0.5, 0.5));
    EXPECT_EQ(pattern.patternAt(Tuple::point(0.75, 0, 0)), Color(0.25, 0.25, 0.25));
}

TEST(PatternTests, RingExtendsInXandZ)
{
    RingPattern pattern = RingPattern(Color(1, 1, 1), Color(0, 0, 0));

    EXPECT_EQ(pattern.patternAt(Tuple::point(0, 0, 0)), Color(1, 1, 1));
    EXPECT_EQ(pattern.patternAt(Tuple::point(1, 0, 0)), Color(0, 0, 0));
    EXPECT_EQ(pattern.patternAt(Tuple::point(0, 0, 1)), Color(0, 0, 0));
    EXPECT_EQ(pattern.patternAt(Tuple::point(0.708, 0, 0.708)), Color(0, 0, 0));
}

TEST(PatternTest, CheckersRepeatX)
{
    CheckerPattern pattern = CheckerPattern(Color(1, 1, 1), Color(0, 0, 0));

    EXPECT_EQ(pattern.patternAt(Tuple::point(0, 0, 0)), Color(1, 1, 1));
    EXPECT_EQ(pattern.patternAt(Tuple::point(0.99, 0, 0)), Color(1, 1, 1));
    EXPECT_EQ(pattern.patternAt(Tuple::point(1.01, 0, 0)), Color(0, 0, 0));
}

TEST(PatternTest, CheckersRepeatY)
{
    CheckerPattern pattern = CheckerPattern(Color(1, 1, 1), Color(0, 0, 0));

    EXPECT_EQ(pattern.patternAt(Tuple::point(0, 0, 0)), Color(1, 1, 1));
    EXPECT_EQ(pattern.patternAt(Tuple::point(0, 0.99, 0)), Color(1, 1, 1));
    EXPECT_EQ(pattern.patternAt(Tuple::point(0, 1.01, 0)), Color(0, 0, 0));
}

TEST(PatternTest, CheckersRepeatZ)
{
    CheckerPattern pattern = CheckerPattern(Color(1, 1, 1), Color(0, 0, 0));

    EXPECT_EQ(pattern.patternAt(Tuple::point(0, 0, 0)), Color(1, 1, 1));
    EXPECT_EQ(pattern.patternAt(Tuple::point(0, 0, 0.99)), Color(1, 1, 1));
    EXPECT_EQ(pattern.patternAt(Tuple::point(0, 0, 1.01)), Color(0, 0, 0));
}