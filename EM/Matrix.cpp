#include "Matrix.h"

Matrix::Matrix(int rSize, int cSize) {
	this->data_.resize(rSize*cSize);
	this->shape_[0] = rSize;
	this->shape_[1] = cSize;
}


