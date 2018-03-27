#include "Matrix.h"


Matrix::Matrix(int rSize, int cSize) {
	// check
	if (rSize <= 0 || cSize <= 0)
		throw "Wrong Size!";
	//
	this->data_.resize(rSize*cSize);
	this->shape_[0] = rSize;
	this->shape_[1] = cSize;
}

Matrix::Matrix(int rSize, int cSize, initializer_list<NumType> args) {
	// check
	if (rSize <= 0 || cSize <= 0)
		throw "Wrong Size!";
	//
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
	//
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

Matrix Matrix::MiniorMat_(int row, int col) {
	// check
	if (!this->IsSquare())
		throw "Not a Square Matrix !";
	if (row < 0 || col < 0)
		throw "Row and Column are start from 1!";
	if (row >= this->shape_[0] || col >= this->shape_[1])
		throw "Row or Column is out of range!";
	//

	/*  calc Minor
		Note that row and col start form 0 !
	*/

	Matrix result(this->shape_[0] - 1, this->shape_[1] - 1);
	int minorIdx = 0;
	for (int i = 0; i < this->shape_[0]; ++i) {
		for (int j = 0; j < this->shape_[1]; ++j) {
			if (i == row || j == col)
				continue;
			int idx = i * this->shape_[1] + j;
			result.data_[minorIdx] = this->data_[idx];
			++minorIdx;
		}
	}

	return result;
}

Matrix Matrix::Trans() {
	// check
	if (this->shape_[0] == 0 || this->shape_[1] == 0)
		throw "Empty Matrix!";
	//

	Matrix result(this->shape_[1], this->shape_[0]);
	for (int i = 0; i < this->shape_[0]; ++i) {
		for (int j = 0; j < this->shape_[1]; ++j) {
			result.data_[j*this->shape_[0] + i] = this->data_[i*this->shape_[1] + j];
		}
	}
	return result;
}

Matrix Matrix::Adj() {
	// check
	if (!this->IsSquare())
		throw "Not a Square Matrix !";
	//

	Matrix result(this->shape_[0], this->shape_[1]);
	for (int i = 0; i < this->shape_[0]; ++i) {
		for (int j = 0; j < this->shape_[1]; ++j) {
			result.data_[i*this->shape_[1] + j] = this->Cofactor(i, j);
		}
	}
	return result.Trans();
}

Matrix Matrix::Inv() {
	// check
	if (!this->IsSquare())
		throw "Not a Square Matrix !";
	//

	NumType det = this->Det();
	if (det == 0.0)
		throw "singular";

	Matrix result = this->Adj();
	result.data_ *= 1 / det;

	return result;
}

NumType Matrix::Cofactor(int row, int col) {
	// check
	if (!this->IsSquare())
		throw "Not a Square Matrix !";
	//

	//Note that row and col start form 0 !
	NumType result = (row + col) % 2 == 0 ? 1.0 : -1.0;
	result *= this->MiniorMat_(row, col).Det();
	return result;
}

NumType Matrix::Det() {
	// check
	if (!this->IsSquare()) 
		throw "Not a Square Matrix !";
	//

	return Det(*this);
}

NumType Matrix::Det(Matrix mat) {
#ifdef DEBUG
	cout << mat.shape_[0] << " " << mat.shape_[1] << '\n';
#endif // DEBUG

	if (mat.shape_[0] == 2) {
		return mat.data_[0] * mat.data_[3] - mat.data_[1] * mat.data_[2];
	}
	
	// expand by first row
	NumType result = 0;
	int sc = 1;
	for (int i = 0; i < mat.shape_[1]; ++i) {
		result += sc * mat.data_[i] * Det(mat.MiniorMat_(0,i));
		sc *= -1;
	}
	return result;
}
