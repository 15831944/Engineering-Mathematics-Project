#include "Vector.h"

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

double Vector::Dot(const Vector& v){
	if (this->dim_!=v.dim_){
		throw "Dimension is not same!";
	}
	else{
		NumType tmp=0;
		for (int i = 0; i < this->dim_; i++) {
			tmp += this->data_[0] * v.data_[0];
		}
		return tmp;
	}
}

Vector Vector::Scalar(NumType s){
	for (int i = 0; i < this->dim_; i++)
		this->data_[0] *= s;
	return *this;
}

NumType Vector::Norm() {
	NumType tmp = 0;
	for (int i = 0; i < this->dim_; i++){
		tmp += pow(this->data_[i], 2);
	}
	return sqrt(tmp);
}

Vector Vector::Normalization() {
	return (this->Scalar(1.0 / this->Norm));
}

Vector Vector::Cross(const Vector& v) {
	if(this->dim_!=v.dim_)
		throw "Dimension is not same!";
	else {
		Vector tmp(this->dim_);
		int dim = this->dim_;
		for (int i = 0; i < tmp.dim_; i++)
			tmp.data_[i] == this->data_[(i + 1) % dim] * v.data_[(i + 2) % dim] - this->data_[(i + 2) % dim] * v.data_[(i + 1) % dim];
		return tmp;
	}
}

NumType Vector::Component(const Vector& v) {
	if (this->dim_ != v.dim_)
		throw "Dimension is not same!";
	else {
		Vector tmp = v;
		return this->Dot(tmp.Normalization);
	}
}

Vector Vector::Projection(const Vector& v) {
	Vector tmp = v;
	return (this->Component(v)*tmp.Normalization);
}

NumType Vector::TriangleArea(const Vector& v) {
	return (this->Cross(v).Norm/2.0);
}

bool Vector::Parallel(const Vector& v) {
	if (this->Cross(v).Norm == 0)
		return true;
	return false;
}

bool Vector::Orthogonal(const Vector& v) {
	if (this->Dot(v) == 0)
		return true;
	return false;
}

NumType Vector::Getangle(const Vector& v) {
	Vector tmp = this->Dot(v);
	return (acos(tmp / (this->Norm*v.Norm)) * 180.0 / PI);
}

Vector Vector::PlaneNormal(const Vector& v) {
	Vector tmp = this->Cross(v);
	return tmp;
}