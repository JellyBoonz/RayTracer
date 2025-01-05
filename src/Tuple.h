#ifndef TUPLE_H
#define TUPLE_H

#include <cmath>
#include <iostream>

class Tuple
{
public:
	double x, y, z, w;

	Tuple();

	Tuple(double x, double y, double z, double w);

	bool isPoint() const;
	bool isVector() const;
	double magnitude();
	Tuple normalize();
	Tuple reflect(Tuple &normal);
	double dot(const Tuple &other);
	Tuple cross(const Tuple &other);

	bool operator==(const Tuple &other) const;
	void operator=(const Tuple &other);
	Tuple operator+(const Tuple &other) const;
	Tuple operator-(const Tuple &other);
	Tuple operator-();
	Tuple operator*(const double num);
	Tuple operator*(const Tuple &other);
	Tuple operator/(const double num);

	friend std::ostream &operator<<(std::ostream &os, const Tuple &tup);

	static Tuple point(double x, double y, double z);
	static Tuple vector(double x, double y, double z);
};

#endif
