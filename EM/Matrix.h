#pragma once
#include "Defines.h"
#include "Vector.h"

class Matrix {
public:
	int shape_[2];
	valarray<NumType> data_;
	Matrix MiniorMat_(int, int);
	valarray<NumType> GetRow(int);

	Matrix() {}

	Matrix(int, int);
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

	void rowAdd(int rowFrom,NumType scale,int addTo);
	void rowScale(int row, NumType scale);
private:
	void swap(int, int);
};

