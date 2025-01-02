#include "Canvas.h"
#include "Color.h"
#include <gtest/gtest.h>

TEST(CanvasTests, CreateCanvas)
{
    Canvas c = Canvas(720, 1080);

    EXPECT_EQ(c.width, 720);
    EXPECT_EQ(c.height, 1080);
}

TEST(CanvasTests, WritePixelColor)
{
    Canvas c = Canvas(720, 1080);
    Color col = Color(1.0, 0.0, 0.0);

    c.writePixel(2, 3, col);

    EXPECT_EQ(c.pixelAt(2, 3), col);
}

TEST(CanvasTests, ConstructPPMHeader)
{
    Canvas c = Canvas(720, 1080);
    std::vector<std::string> ppm = c.canvasToPPM();

    EXPECT_EQ(ppm[0], "P3\n");
    EXPECT_EQ(ppm[1], "720 1080\n");
    EXPECT_EQ(ppm[2], "255\n");
}

TEST(CanvasTests, ConstructPPMPixelData)
{
    Canvas c(5, 3);

    Color c1(1.5, 0, 0);
    Color c2(0, 0.5, 0);
    Color c3(-0.5, 0, 1);

    c.writePixel(0, 0, c1);
    c.writePixel(2, 1, c2);
    c.writePixel(4, 2, c3);

    EXPECT_EQ(c.pixelAt(0, 0), c1);

    std::vector<std::string> ppm = c.canvasToPPM();

    std::vector<std::string> expected = {
        "255 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n",
        "0 0 0 0 0 0 0 128 0 0 0 0 0 0 0\n",
        "0 0 0 0 0 0 0 0 0 0 0 0 0 0 255\n"};

    for (int i = 0; i < 3; ++i)
    {
        EXPECT_EQ(ppm[i + 3], expected[i]);
    }
}

// TEST(CanvasTest, SplitLongLines)
// {
//     Canvas c = Canvas(10, 2);
//     Color col = Color(1.0, 0.8, 0.6);

//     std::vector<std::string> ppm = c.canvasToPPM();

//     std::vector<std::string> expected = {
//         "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204\n",
//         "153 255 204 153 255 204 153 255 204 153 255 204 153\n",
//         "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204\n",
//         "153 255 204 153 255 204 153 255 204 153 255 204 153\n"};

//     for (int i = 0; i < 4; ++i)
//     {
//         EXPECT_EQ(ppm[i + 3], expected[i]);
//     }
// }