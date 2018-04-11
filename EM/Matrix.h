#pragma once
#include "Defines.h"
#include "Vector.h"

class Matrix {
public:
	int shape_[2];
	valarray<NumType> data_;
	Matrix MiniorMat_(int, int);
	valarray<NumType> GetRow(int);

	Matrix(int, int);
	Matrix() { shape_[0] = 0; shape_[1] = 0; };
	Matrix(int, int, initializer_list<NumType>);
	Matrix operator+(const Matrix&);
	Matrix operator-(const Matrix&);
	Matrix operator=(const Matrix&);
	Matrix operator=(initializer_list<NumType>);
	Matrix operator*(const Matrix&);
	
	int Rank();
	Matrix Trans();
	Matrix Adj();
	Matrix Inv();

	
	string ToString();

	bool IsSquare();

	NumType Cofactor(int, int);
	NumType Det();

	static NumType Det(Matrix);
	valarray<Matrix> reff();//¦^¶ÇL©MU
	Matrix SolveLinear(const Matrix&);
private:
	void swap(int, int);
};

