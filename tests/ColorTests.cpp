#include "Color.h"
#include <gtest/gtest.h>

TEST(ColorTests, CreateColor)
{
    Color color = Color(0.5, 0.2, 0.9);

    EXPECT_EQ(color.getRed(), 0.5);
    EXPECT_EQ(color.getGreen(), 0.2);
    EXPECT_EQ(color.getBlue(), 0.9);
}

TEST(ColorTests, AddColors)
{
    Color color1 = Color(0.9, 0.6, 0.75);
    Color color2 = Color(0.7, 0.1, 0.25);

    EXPECT_EQ(color1 + color2, Color(1.6, 0.7, 1.0));
}

TEST(ColorTests, SubtractColors)
{
    Color color1 = Color(0.9, 0.6, 0.75);
    Color color2 = Color(0.7, 0.1, 0.25);

    EXPECT_EQ(color1 - color2, Color(0.2, 0.5, 0.5));
}

TEST(ColorTests, ScalarMultiply)
{
    Color color1 = Color(0.2, 0.3, 0.4);

    EXPECT_EQ(color1 * 2, Color(0.4, 0.6, 0.8));
}

TEST(ColorTests, MultiplyColors)
{
    Color color1 = Color(1.0, 0.2, 0.4);
    Color color2 = Color(0.9, 1.0, 0.1);

    EXPECT_EQ(color1 * color2, Color(0.9, 0.2, 0.04));
}
