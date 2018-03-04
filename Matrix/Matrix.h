#pragma once
#include <valarray>

using std::valarray;

template <class Type>
class Matrix {
private:
	int shape_[2];
	valarray<Type> data_;

public:

	Matrix(int, int);
	bool Set(Type, ...); // if the parameter is correct



	

};

template <class Type>
Matrix<Type>::Matrix(int rSize, int cSize) {
	this->data_.resize(rSize*cSize);
	this->shape_[0] = rSize;
	this->shape_[1] = cSize;
}

template <class Type>
bool Matrix<Type>::Set(Type first, ...) {
	va_list list;
	__va_start(list, first);
	int size = this->data_.size();
	this->data_[0] = first;
	for (int i = 1; i < size; ++i) {
		this->data_[i] = __va_arg(list, Type);
	}

}
