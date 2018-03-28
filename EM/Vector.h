#pragma once
#include "Defines.h"

class Vector {
public:
	int dim_;
	valarray<NumType> data_;
	Vector();
	Vector(int);
	Vector(initializer_list<NumType>);
	Vector operator=(initializer_list<NumType>);
	Vector operator=(const Vector&);
	Vector operator+(const Vector&);
	Vector operator-(const Vector&);
	NumType Dot(const Vector&);
	Vector Scalar(NumType);
	NumType Norm() const;
	Vector Normalization();
	Vector Cross(const Vector&);
	NumType Component(const Vector&);
	Vector Projection(const Vector& v);//project onto v
	NumType TriangleArea(const Vector&);
	bool Parallel(const Vector&);
	bool Orthogonal(const Vector&);
	NumType Getangle(const Vector&);
	Vector PlaneNormal(const Vector&);
	string ToString();
};
