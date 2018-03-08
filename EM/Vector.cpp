#include "Vector.h"
#include <sstream>
using std::stringstream;

Vector::Vector() {
	this->dim_ = 0;
}

Vector::Vector(int dim) {
	this->data_.resize(dim);
	this->dim_ = dim;
}

Vector::Vector(initializer_list<NumType> v) {
	this->dim_ = (int)v.size();
	this->data_.resize(this->dim_);
	
	// set the vector
	auto iter= v.begin();
	int i;
	for ( i=0;iter != v.end(); ++iter,++i) {
		this->data_[i] = *iter;
	}
}

string Vector::ToString(){
	if (this->dim_ == 0)
		return "";
	stringstream ss;
	ss << "(" << this->data_[0];
	for (int i = 1; i < this->dim_; ++i) {
		ss << ", " << this->data_[i];
	}
	ss << ")";
	return ss.str();
}