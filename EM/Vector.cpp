#include "Vector.h"

Vector::Vector(int dim) {
	this->data_.resize(dim);
	this->dim_ = dim;
}