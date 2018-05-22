#include "Vector.h"

Vector::Vector() {
	this->dim_ = 0; // zero vector !!!
}

Vector::Vector(int dim) {
	if (dim < 0)
		throw std::runtime_error("Dimension can't be negtive!");
	this->data_.resize(dim);
	this->dim_ = dim;
}

Vector::Vector(Matrix m) {
	this->dim_ = m.data_.size();
	this->data_ = m.data_;
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

Vector::Vector(valarray<NumType> v) {
	this->dim_ = v.size();
	this->data_.resize(this->dim_);
	for (int i = 0; i < this->dim_; i++) {
		this->data_[i] = v[i];
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

string Vector::getSizeInfo() {
	stringstream ss;
	ss << this->dim_;
	return ss.str();
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
		throw std::runtime_error("Dimension is not same!");
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
		throw std::runtime_error("Dimension is not same!");

	Vector result(this->dim_);
	result.data_ = this->data_ - v.data_;
	return result;
}

double Vector::Dot(const Vector& v){
	if (this->dim_!=v.dim_){
		throw std::runtime_error("Dimension is not same!");
	}
	else{
		return (v.data_ * this->data_).sum();
	}
}

Vector Vector::Scalar(NumType s){
	Vector tmp = *this;
	tmp.data_ = tmp.data_ * s;
	return tmp;
}

NumType Vector::Norm() const{
	NumType tmp = 0;
	for (int i = 0; i < this->dim_; i++){
		tmp += pow(this->data_[i], 2);
	}
	return sqrt(tmp);
}

NumType Vector::Dist(const Vector& v) {
	NumType tmp = 0;
	for (int i = 0; i < this->dim_; i++) {
		tmp += pow(this->data_[i]-v.data_[i], 2);
	}
	return sqrt(tmp);
}

Vector Vector::Normalization() {
	if (this->Norm()==0)
		return *this;
	return (this->Scalar(1.0 / this->Norm()));
}

Vector Vector::Cross(const Vector& v) {
	if(this->dim_!=v.dim_)
		throw std::runtime_error("Dimension is not same!");
	else {
		Vector tmp(this->dim_);
		int dim = this->dim_;
		for (int i = 0; i < tmp.dim_; i++)
			tmp.data_[i] = this->data_[(i + 1) % dim] * v.data_[(i + 2) % dim] - this->data_[(i + 2) % dim] * v.data_[(i + 1) % dim];
		return tmp;
	}
}

NumType Vector::Component(const Vector& v) {
	if (this->dim_ != v.dim_)
		throw std::runtime_error("Dimension is not same!");
	else {
		Vector tmp = v;
		return this->Dot(tmp.Normalization());
	}
}

Vector Vector::Projection(const Vector& v) {
	if (this->Dot(v) == 0)
		throw std::runtime_error("two vector are vertical");
	Vector tmp = v;
	tmp.Normalization();
	return (tmp.Normalization().Scalar(this->Component(v)));
}

NumType Vector::TriangleArea(const Vector& v) {
	return this->Norm()*v.Norm()*sin(this->Getangle(v)*PI/180.0f) / 2;
	//return (this->Cross(v).Norm()/2.0);
}

bool Vector::Parallel(Vector& v) {
	if(this->dim_!=v.dim_)
		throw std::runtime_error("Dimension is not the same");
	Vector v1, v2;
	v1 = this->Normalization();
	v2 = v.Normalization();
	for (int i = 0; i < v1.dim_; i++)
	{
		if (abs(v1.data_[i] - v2.data_[i]) > 0.000001)
			return false;
	}
	return true;
}

bool Vector::Orthogonal(const Vector& v) {
	if (this->Dot(v) == 0)
		return true;
	return false;
}

NumType Vector::Getangle(const Vector& v){
	NumType tmp = this->Dot(v);
	if (this->Norm() == 0 || v.Norm() == 0)
		throw std::runtime_error("vector can't be zero vector");
	return (acos(tmp / (this->Norm()* v.Norm())) * 180.0 / PI);
}

Vector Vector::PlaneNormal(const Vector& v) {
	Vector tmp = this->Cross(v);
	return tmp;
}

bool Vector::LinearIndependent(const valarray<Vector>& v){
	int dim = v[0].dim_;
	for (int i = 1; i < v.size(); i++) {
		if(v[i].dim_!=dim)
			throw std::runtime_error("Dimension is not same!");
	}
	/*if (dim > v.size())//col>row
		return false;*/
	Matrix tmp(v.size(), dim);
	for (int i = 0; i < v.size(); i++)
		for (int j = 0; j < dim; j++)
			tmp.data_[i*dim + j]=v[i].data_[j];
	if (tmp.Rank() == v.size())
		return true;
	else
		return false;
}

valarray<Vector> Vector::Gram_Schmidt_Orthogonal(valarray<Vector>& v) {
	int dim = v[0].dim_;
	for (int i = 1; i < v.size(); i++) {
		if (v[i].dim_ != dim)
			throw std::runtime_error("Dimension is not same!");
	}
	valarray<Vector> tmp;
	tmp.resize(v.size());
	for (int i = 0; i < v.size(); i++) {
		tmp[i] = v[i];
		for (int j = 0; j < i; j++) {
			tmp[i] = tmp[i] - tmp[j].Scalar(v[i].Dot(tmp[j]) / tmp[j].Dot(tmp[j]));
		}
	}
	for (int i = 0; i < tmp.size(); i++)
		tmp[i]=tmp[i].Normalization();
	return tmp;
}

