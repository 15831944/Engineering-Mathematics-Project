#pragma once
#include "Defines.h"

class Matrix {
private:
	int shape_[2];
	valarray<NumType> data_;

public:
	Matrix(int, int);

	Matrix(int, int, initializer_list<NumType>);

	string ToString();

	bool IsSquare();

	NumType Det();
	static NumType Det(const Matrix&, int, int, int, int);

	Matrix Cofactor(int, int);
};

