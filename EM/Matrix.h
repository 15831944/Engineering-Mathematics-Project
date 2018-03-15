#pragma once
#include "Defines.h"

class Matrix {
private:
	int shape_[2];
	valarray<NumType> data_;
	Matrix MiniorMat_(int, int);

public:
	Matrix(int, int);

	Matrix(int, int, initializer_list<NumType>);

	Matrix Trans();
	Matrix Adj();
	Matrix Inv();

	string ToString();

	bool IsSquare();

	NumType Cofactor(int, int);
	NumType Det();

	static NumType Det(Matrix);

	

};

