#include "Pattern.h"
#include "Intersectable.h"
#include "Noise.h"
#include <cmath>
#include <iostream>

Color StripePattern::patternAt(const Tuple &point) const
{
    return (static_cast<int>(floor(point.x)) % 2 == 0) ? a : b;
}

Color StripePattern::patternAtObject(const Intersectable &object, const Tuple &worldPoint) const
{

    Matrix objInv = object.getTransform().inverse();
    Matrix patInv = this->getTransform().inverse();

    Tuple objectPoint = objInv * worldPoint;
    Tuple patternPoint = patInv * objectPoint;
    return patternAt(patternPoint);
}

Color GradientPattern::patternAt(const Tuple &point) const
{
    return a + (b - a) * (point.x - floor(point.x));
}

Color GradientPattern::patternAtObject(const Intersectable &object, const Tuple &worldPoint) const
{
    Matrix objInv = object.getTransform().inverse();
    Matrix patInv = this->getTransform().inverse();

    Tuple objectPoint = objInv * worldPoint;
    Tuple patternPoint = patInv * objectPoint;
    return patternAt(patternPoint);
}

Color RingPattern::patternAt(const Tuple &point) const
{
    if (static_cast<int>(floor(sqrt(point.x * point.x + point.z * point.z))) % 3 == 0)
    {
        return a;
    }
    else
    {
        return b;
    }
}

Color RingPattern::patternAtObject(const Intersectable &object, const Tuple &worldPoint) const
{
    Matrix objInv = object.getTransform().inverse();
    Matrix patInv = this->getTransform().inverse();

    Tuple objectPoint = objInv * worldPoint;
    Tuple patternPoint = patInv * objectPoint;
    return patternAt(patternPoint);
}

Color CheckerPattern::patternAt(const Tuple &point) const
{
    return (static_cast<int>(floor(point.x) + floor(point.y) + floor(point.z)) % 2 == 0) ? a : b;
}

Color CheckerPattern::patternAtObject(const Intersectable &object, const Tuple &worldPoint) const
{
    Matrix objInv = object.getTransform().inverse();
    Matrix patInv = this->getTransform().inverse();

    Tuple objectPoint = objInv * worldPoint;
    Tuple patternPoint = patInv * objectPoint;
    return patternAt(patternPoint);
}

Color TestPattern::patternAt(const Tuple &point) const
{
    return Color(point.x, point.y, point.z);
}

Color TestPattern::patternAtObject(const Intersectable &object, const Tuple &worldPoint) const
{
    Matrix objInv = object.getTransform().inverse();
    Matrix patInv = this->getTransform().inverse();

    Tuple objectPoint = objInv * worldPoint;
    Tuple patternPoint = patInv * objectPoint;
    return patternAt(patternPoint);
}

Color PerturbedRingPattern::patternAt(const Tuple &point) const
{
    RingPattern ringPattern = RingPattern(a, b);
    const Tuple perturbedPoint = Tuple::point(Noise::perlinNoise(point), Noise::perlinNoise(point), Noise::perlinNoise(point)) * scale;
    return ringPattern.patternAt(perturbedPoint + Tuple::point(point.x, point.y, point.z));
}

Color PerturbedStripePattern::patternAt(const Tuple &point) const
{
    StripePattern stripePattern = StripePattern(a, b);
    const Tuple perturbedPoint = Tuple::point(Noise::perlinNoise(point), Noise::perlinNoise(point), Noise::perlinNoise(point)) * scale;
    return stripePattern.patternAt(perturbedPoint + Tuple::point(point.x, point.y, point.z));
}

Color PerturbedStripePattern::patternAtObject(const Intersectable &object, const Tuple &worldPoint) const
{
    Matrix objInv = object.getTransform().inverse();
    Matrix patInv = this->getTransform().inverse();

    Tuple objectPoint = objInv * worldPoint;
    Tuple patternPoint = patInv * objectPoint;
    return patternAt(patternPoint);
}

Color PerturbedRingPattern::patternAtObject(const Intersectable &object, const Tuple &worldPoint) const
{
    Matrix objInv = object.getTransform().inverse();
    Matrix patInv = this->getTransform().inverse();

    Tuple objectPoint = objInv * worldPoint;
    Tuple patternPoint = patInv * objectPoint;
    return patternAt(patternPoint);
}

Color PerturbedGradientPattern::patternAt(const Tuple &point) const
{
    GradientPattern gradientPattern = GradientPattern(a, b);
    const Tuple perturbedPoint = Tuple::point(Noise::perlinNoise(point), Noise::perlinNoise(point), Noise::perlinNoise(point)) * scale;
    return gradientPattern.patternAt(perturbedPoint + Tuple::point(point.x, point.y, point.z));
}

Color PerturbedGradientPattern::patternAtObject(const Intersectable &object, const Tuple &worldPoint) const
{
    Matrix objInv = object.getTransform().inverse();
    Matrix patInv = this->getTransform().inverse();

    Tuple objectPoint = objInv * worldPoint;
    Tuple patternPoint = patInv * objectPoint;
    return patternAt(patternPoint);
}