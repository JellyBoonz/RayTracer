#ifndef PATTERN_H
#define PATTERN_H

#include "Tuple.h"
#include "Matrix.h"
#include "Color.h"

class Intersectable;

class Pattern
{
private:
    Matrix mat;

public:
    Pattern() : mat(Matrix::ID_MAT) {}
    virtual ~Pattern() = default;
    virtual Color patternAt(const Tuple &point) const = 0;
    virtual Color patternAtObject(const Intersectable &object, const Tuple &worldPoint) const = 0;
    void setTransform(const Matrix &m) { mat = m; }
    Matrix getTransform() const { return mat; }
};

class StripePattern : public Pattern
{
public:
    const Color a;
    const Color b;

    StripePattern(const Color &a, const Color &b) : Pattern(), a(a), b(b) {}

    Color patternAt(const Tuple &point) const;

    Color patternAtObject(const Intersectable &object, const Tuple &worldPoint) const;
};

class GradientPattern : public Pattern
{
public:
    const Color a;
    const Color b;

    GradientPattern(const Color &a, const Color &b) : Pattern(), a(a), b(b) {}

    Color patternAt(const Tuple &point) const;

    Color patternAtObject(const Intersectable &object, const Tuple &worldPoint) const;
};

class RingPattern : public Pattern
{
public:
    const Color a;
    const Color b;

    RingPattern(const Color &a, const Color &b) : Pattern(), a(a), b(b) {}

    Color patternAt(const Tuple &point) const;

    Color patternAtObject(const Intersectable &object, const Tuple &worldPoint) const;
};

class CheckerPattern : public Pattern
{
public:
    const Color a;
    const Color b;

    CheckerPattern(const Color &a, const Color &b) : Pattern(), a(a), b(b) {}

    Color patternAt(const Tuple &point) const;

    Color patternAtObject(const Intersectable &object, const Tuple &worldPoint) const;
};

class PerturbedRingPattern : public Pattern
{
public:
    const Color a;
    const Color b;
    const double scale;

    PerturbedRingPattern(const Color &a, const Color &b, const double scale) : Pattern(), a(a), b(b), scale(scale) {}

    Color patternAt(const Tuple &point) const;

    Color patternAtObject(const Intersectable &object, const Tuple &worldPoint) const;
};

class PerturbedStripePattern : public Pattern
{
public:
    const Color a;
    const Color b;
    const double scale;

    PerturbedStripePattern(const Color &a, const Color &b, const double scale) : Pattern(), a(a), b(b), scale(scale) {}

    Color patternAt(const Tuple &point) const;

    Color patternAtObject(const Intersectable &object, const Tuple &worldPoint) const;
};

class PerturbedGradientPattern : public Pattern
{
public:
    const Color a;
    const Color b;
    const double scale;

    PerturbedGradientPattern(const Color &a, const Color &b, const double scale) : Pattern(), a(a), b(b), scale(scale) {}

    Color patternAt(const Tuple &point) const;

    Color patternAtObject(const Intersectable &object, const Tuple &worldPoint) const;
};

#endif