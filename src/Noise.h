#ifndef NOISE_H
#define NOISE_H

#include "Tuple.h"
#include "Matrix.h"
#include "Color.h"
#include <vector>
#include <cmath>
#include <random>

class Noise
{
public:
    static double perlinNoise(const Tuple &point);
    static std::vector<double> generateNoiseRange(const Tuple &point, int count);

private:
    static const int permutation[];
    static std::vector<int> p;

    static double fade(double t);
    static double lerp(double t, double a, double b);
    static double grad(int hash, double x, double y, double z);
    static void initializePermutation();
};

#endif