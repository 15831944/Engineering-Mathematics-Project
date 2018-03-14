#include "Matrix.h"

Matrix::Matrix(int rSize, int cSize) {
	this->data_.resize(rSize*cSize);
	this->shape_[0] = rSize;
	this->shape_[1] = cSize;
}

Matrix::Matrix(int rSize, int cSize, initializer_list<NumType> args) {
	this->data_.resize(rSize*cSize);
	this->shape_[0] = rSize;
	this->shape_[1] = cSize;

	auto iter = args.begin();
	int i;
	for (i = 0; iter != args.end(); ++iter, ++i) {
		this->data_[i] = *iter;
	}
}

string Matrix::ToString() {
	// check

	if (this->shape_[0] == 0 || this->shape_[1] == 0)
		return "";

	stringstream ss;

	for (int i = 0; i < this->shape_[0]; ++i) {
		ss << this->data_[i*this->shape_[1]];
		for (int j = 1; j < this->shape_[1]; ++j) {
			ss << ' ' << this->data_[i*this->shape_[1] + j];
		}
		ss << '\n';
	}

	return ss.str();
}

bool Matrix::IsSquare() {
	return this->shape_[0] > 1 && this->shape_[1] > 1 && this->shape_[0] == this->shape_[1];
}

Matrix Matrix::Cofactor(int row, int col) {
	// check

	if (!this->IsSquare())
		throw "No a Square Matrix !";
	if (row <= 0 || col <= 0)
		throw "Row and Column are start from 1!";
	if (row > this->shape_[0] || col > this->shape_[1])
		throw "Row or Column is out of range!";

	/*  calc Minor
		Note that row and col start form 1 !
	*/

	Matrix result(this->shape_[0] - 1, this->shape_[1] - 1);
	int minorIdx = 0;
	for (int i = 0; i < this->shape_[0]; ++i) {
		for (int j = 0; j < this->shape_[1]; ++j) {
			if (i + 1 == row || j + 1 == col)
				continue;
			int idx = i * this->shape_[1] + j;
			result.data_[minorIdx] = this->data_[idx];
			++minorIdx;
		}
	}

	// calc cofactor

	int c = (row + col) % 2 == 0 ? 1 : -1;
	result.data_ *= c;

	return result;
}

