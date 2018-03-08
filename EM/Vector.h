#pragma once
#include "Defines.h"

class Vector {
private:
	int dim_;
	valarray<NumType> data_;
public:
	Vector();
	Vector(int);
	Vector(initializer_list<NumType>);
	Vector operator=(initializer_list<NumType>);
	Vector operator=(const Vector&);
	Vector operator+(const Vector&);
	Vector operator-(const Vector&);

	string ToString();


};
