#ifndef CANVAS_H
#define CANVAS_H

#include "Color.h"
#include <algorithm>
#include <cmath>

class Canvas
{
private:
    // Custom clamp function
    template <typename T>
    T clamp(T value, T low, T high) {
        return std::max(low, std::min(value, high));
    }

public:
    int width;
    int height;
    std::vector<std::vector<Color>> pixels;

    Canvas(int width, int height)
        : width(width), height(height), pixels(height, std::vector<Color>(width, Color(0.0, 0.0, 0.0))) {}

    Canvas(int width, int height, Color color)
        : width(width), height(height), pixels(height, std::vector<Color>(width, color)) {}

    Color pixelAt(int x, int y) const
    {
        return pixels[y][x];
    }

    void writePixel(int x, int y, Color color)
    {
        pixels[y][x] = color;
    }

    std::vector<std::string> canvasToPPM()
    {
        std::vector<std::string> ppm;

        ppm.push_back("P3\n");
        ppm.push_back(std::to_string(width) + " " + std::to_string(height) + "\n");
        ppm.push_back("255\n");

        int currentLength = 0;

        for (int y = 0; y < height; y++)
        {
            std::string row;
            for (int x = 0; x < width; x++)
            {
                Color col = pixelAt(x, y);
                int red = clamp(static_cast<int>(std::round(col.getRed() * 255)), 0, 255);
                int green = clamp(static_cast<int>(std::round(col.getGreen() * 255)), 0, 255);
                int blue = clamp(static_cast<int>(std::round(col.getBlue() * 255)), 0, 255);
                std::string pixel = std::to_string(red) + " " +
                                    std::to_string(green) + " " +
                                    std::to_string(blue) + " ";

                row += pixel;
                currentLength += pixel.length();
            }
            row.pop_back();
            ppm.push_back(row + "\n");
        }

        return ppm;
    }
};

#endif