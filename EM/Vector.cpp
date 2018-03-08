#include "Vector.h"
#include <sstream>
using std::stringstream;

Vector::Vector() {
	this->dim_ = 0; // zero vector !!!
}

Vector::Vector(int dim) {
	if (dim < 0)
		throw "Dimension can't be negtive!";
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

Vector Vector::operator=(initializer_list<NumType> rhs) {
	this->dim_ = (int)rhs.size();
	this->data_.resize(this->dim_);

	// set the vector
	auto iter = rhs.begin();
	int i;
	for (i = 0; iter != rhs.end(); ++iter, ++i) {
		this->data_[i] = *iter;
	}
	return *this;
}

Vector Vector::operator=(const Vector& v) {
	if (v.dim_ == 0)
		return *this;
	this->dim_ = v.dim_;
	this->data_.resize(this->dim_);
	for (int i = 0; i < this->dim_; ++i) {
		this->data_[i] = v.data_[i];
	}
	return *this;
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

Vector Vector::operator+(const Vector& v) {
	// add zero vector
	if (this->dim_ == 0)
		return v;
	if (v.dim_ == 0)
		return *this;
	// dim not same
	if (this->dim_ != v.dim_)
		throw "Dimension is not same!";
	Vector result(this->dim_);
	result.data_ = this->data_ + v.data_;
	return result;
}

Vector Vector::operator-(const Vector& v) {
	// add zero vector
	if (this->dim_ == 0) {
		Vector tmp = v;
		tmp.data_ *= -1.0;
		return tmp;
	}
	if (v.dim_ == 0)
		return *this;
	// dim not same
	if (this->dim_ != v.dim_)
		throw "Dimension is not same!";

	Vector result(this->dim_);
	result.data_ = this->data_ - v.data_;
	return result;
}
