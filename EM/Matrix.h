#pragma once
#include "Defines.h"

class Matrix {
public:
	int shape_[2];
	valarray<NumType> data_;
	Matrix MiniorMat_(int, int);


	Matrix(int, int);

	Matrix(int, int, initializer_list<NumType>);
	Matrix operator+(const Matrix&);
	Matrix operator-(const Matrix&);
	Matrix operator=(const Matrix&);
	Matrix operator=(initializer_list<NumType>);
	Matrix operator*(const Matrix&);

	Matrix Trans();
	Matrix Adj();
	Matrix Inv();

	string ToString();

	bool IsSquare();

	NumType Cofactor(int, int);
	NumType Det();

	static NumType Det(Matrix);

	

};

