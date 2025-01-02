#include "Tuple.h"
#include "Canvas.h"
#include "Matrix.h"
#include "Transforms.h"
#include <stdio.h>
#include <iostream>
#include <fstream>

int main(void)
{
    int canvasSize = 400;
    Canvas c(canvasSize, canvasSize);
    Color white(1, 1, 1);

    Transforms centerTransform;
    centerTransform.translate(canvasSize / 2.0f, canvasSize / 2.0f, 0);

    float radius = canvasSize * 0.4f;

    for (int hour = 0; hour < 12; ++hour)
    {
        Tuple point = Tuple::point(0, 1, 0) * radius;

        Transforms hourTransform;
        hourTransform.rotateZ(hour * (M_PI / 6));

        hourTransform.applyTo(point);
        centerTransform.applyTo(point);

        c.writePixel(round(point.x), round(canvasSize - point.y), white);
    }

    std::ofstream ppmFile("clock.ppm");

    if (ppmFile.is_open())
    {
        std::vector<std::string> ppmContent = c.canvasToPPM();
        for (const auto &line : ppmContent)
        {
            ppmFile << line;
        }
        ppmFile.close();
        std::cout << "PPM file created successfully!" << std::endl;
    }
    else
    {
        std::cerr << "Unable to open file for writing" << std::endl;
    }

    return 0;
}