#include "Matrix.h"

int rowOptime;

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

Matrix Matrix::operator+(const Matrix& m) {
	if(this->shape_[0]!=m.shape_[0]||this->shape_[1]!=m.shape_[1])
		throw "Dimension is not same!";
	else {
		Matrix result(this->shape_[0],this->shape_[1]);
		for (int i = 0; i < this->shape_[0]*this->shape_[1]; i++){
			result.data_[i] = this->data_[i] + m.data_[i];
		}
		return result;
	}		
}

Matrix Matrix::operator-(const Matrix& m) {
	if (this->shape_[0] != m.shape_[0] || this->shape_[1] != m.shape_[1])
		throw "Dimension is not same!";
	else {
		Matrix result(this->shape_[0], this->shape_[1]);
		for (int i = 0; i < this->shape_[0] * this->shape_[1]; i++) {
			result.data_[i] = this->data_[i] - m.data_[i];
		}
		return result;
	}
}

Matrix Matrix::operator=(const Matrix& m) {
	this->shape_[0] = m.shape_[0];
	this->shape_[1] = m.shape_[1];
	this->data_.resize(m.shape_[0] * m.shape_[1]);
	for (int i = 0; i < m.shape_[0] * m.shape_[1]; i++) {
		this->data_[i] = m.data_[i];
	}
	return *this;
}

Matrix Matrix::operator=(initializer_list<NumType> args) {
	if(this->data_.size()!=args.size())
		throw "Dimension is not same!";
	else {
		auto iter = args.begin();
		int i;
		for (i = 0; iter != args.end(); ++iter, ++i) {
			this->data_[i] = *iter;
		}
		return *this;
	}
}

Matrix Matrix::operator*(const Matrix& m) {
	if (this->shape_[1] != m.shape_[0])
		throw "Error dimension!";
	else
	{
		Matrix result(this->shape_[0], m.shape_[1]);
		for (int i = 0; i<this->shape_[0]; ++i) {
			for (int j = 0; j<m.shape_[1]; ++j) {
				NumType sum = 0.0;
				for (int k = 0; k<m.shape_[0]; ++k) {
					sum += this->data_[i*this->shape_[1]+k] * m.data_[k*m.shape_[1] + j];
				}
				result.data_[i*m.shape_[1]+j] = sum;
			}
		}
		return result;
	}
}

string Matrix::getSizeInfo() {
	stringstream ss;
	ss << this->shape_[0] << "x" << this->shape_[1];
	return ss.str();
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

valarray<NumType> Matrix::GetRow(int x) {
	valarray<NumType> tmp;
	tmp.resize(this->shape_[1]);
	for (int i = 0; i < tmp.size(); i++) {
		tmp[i] = this->data_[x*this->shape_[1] + i];
	}
	return tmp;
}
void Matrix::swap(int a,int b) {
	for (int i = 0; i < this->shape_[1]; i++) {
		NumType tmp;
		tmp = this->data_[a*this->shape_[1] + i];
		this->data_[a*this->shape_[1] + i] = this->data_[b*this->shape_[1] + i];
		this->data_[b*this->shape_[1] + i] = tmp;
	}
}

int Matrix::Rank() {
	Matrix tmp = *this;
	int rank = this->shape_[0];
	for (int row = 0; row < tmp.shape_[0]; row++) {
		if (tmp.data_[row*this->shape_[1] + row]) {//判斷是否為0
			for (int col = row + 1; col < this->shape_[0]; col++) {
				NumType mult = tmp.data_[col*this->shape_[1]+row] / tmp.data_[row*this->shape_[1] + row];
				for (int i = 0; i < tmp.shape_[1]; i++) {
					tmp.data_[col*tmp.shape_[1] + i] -= mult * tmp.data_[row*this->shape_[1] + i];
				}
			}
		}
		else
		{
			for (int i = row + 1; i < tmp.shape_[0]; i++) {
				if (tmp.data_[i*tmp.shape_[1]+row]) {
					tmp.swap(row, i);
					row--;
					break;
				}
			}
		}
	}
	for (int i = 0; i < tmp.shape_[0]; i++) {//判斷0列有幾列
		bool check = true;
		for (int j = 0; j < tmp.shape_[1]; j++) {
			if (!tmp.data_[i*tmp.shape_[0] + j]) {
				check = false;
				break;
			}		
		}
		if (check)
			rank--;
	}
	return rank;
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
	if (mat.shape_[0] == 1)
		return mat.data_[0];
	if (mat.shape_[0] == 2)
		return mat.data_[0] * mat.data_[3] - mat.data_[1] * mat.data_[2];
	NumType result = 1;
	rowOptime = 0;
	bool rowFlag = true;
	for (int i = 0; i<mat.shape_[0]; ++i) {
		if (mat.data_[i*mat.shape_[0] + i] == 0.0) {
			rowFlag = false;
			for (int j = 0; j<mat.shape_[0]; ++j) {
				if (j == i)continue;
				if (mat.data_[j*mat.shape_[0] + i] != 0.0) {
					rowFlag = true;
					mat.swap(i, j);
					rowOptime++;
				}
			}
			if (!rowFlag)break;
		}
	}
	if (!rowFlag)
		throw "不可解";
	for (int i = 0; i < mat.shape_[0]; ++i) {
		NumType scale = mat.data_[i*mat.shape_[0] + i];
		if (scale == 0.0) {
			for (int k = i + 1; k < mat.shape_[0]; ++k) {
				if (mat.data_[k*mat.shape_[0] + i] != 0.0) {
					mat.swap(i, k);
					rowOptime++;
					break;
				}
			}
		}
		for (int j = i + 1; j < mat.shape_[0]; j++) {
			scale = -mat.data_[j*mat.shape_[0] + i] / mat.data_[i*mat.shape_[0] + i];
			if (scale == 0.0) continue;
			mat.rowAdd(i, scale, j);
		}
	}
	for (int i = 0; i < mat.shape_[0]; ++i)
		result *= mat.data_[i*mat.shape_[0] + i];
	result *= rowOptime % 2 == 0 ? 1 : -1;
	/*
	this method slow to dead
	int sc = 1;
	for (int i = 0; i < mat.shape_[1]; ++i) {
		result += sc * mat.data_[i] * Det(mat.MiniorMat_(0,i));
		sc *= -1;
	}
	*/
	return result;
}

valarray<Matrix> Matrix::reff() {
	
	if (!this->IsSquare())
		throw "Not a Square Matrix !";
	valarray<Matrix> LU(2);
	Matrix mat = *this;
	Matrix L(this->shape_[0], this->shape_[1]);
	Matrix U(this->shape_[0], this->shape_[1]);
	Matrix p(mat.shape_[0], mat.shape_[0]);
	for (int i = 0; i < mat.shape_[0]; ++i)
		p.data_[i*shape_[0] + i] = 1;
	// row swap
	rowOptime = 0;
	bool rowFlag = true;
	for (int i = 0; i<mat.shape_[0]; ++i) {
		if (mat.data_[i*mat.shape_[0]+i] == 0.0) {
			rowFlag = false;
			for (int j = 0; j<mat.shape_[0]; ++j) {
				if (j == i)continue;
				if (mat.data_[j*mat.shape_[0] + i] != 0.0) {
					rowFlag = true;
					mat.swap(i, j);
					//p.swap(i, j);
					rowOptime++;
				}
			}
			if (!rowFlag)break;
		}
	}
	if (!rowFlag)
		throw "不可解";
	for (int i = 0; i < mat.shape_[0]; ++i) {
		NumType scale = mat.data_[i*mat.shape_[0]+i];
		if (scale == 0.0) {
			for (int k = i + 1; k < mat.shape_[0]; ++k) {
				if (mat.data_[k*mat.shape_[0] + i] != 0.0) {
					mat.swap(i, k);
					p.swap(i, k);
					
					rowOptime++;
					break;
				}
			}
		}
		for (int j = i + 1; j < mat.shape_[0]; j++) {
			scale = -mat.data_[j*mat.shape_[0] + i] / mat.data_[i*mat.shape_[0] + i];
			if (scale == 0.0) continue;
			mat.rowAdd(i, scale, j);
			p.rowAdd(i, scale, j);
		}
	}
	Matrix R = p* *this;
	U = mat;
	// bug below
	for (int i = 0; i < mat.shape_[0]; ++i)
		L.data_[i*shape_[0] + i] = 1;
	for (int i = 0; i<mat.shape_[0]; ++i) {
		if (p.data_[i*mat.shape_[0] + i] == 0.0) {
			for (int j = 0; j<mat.shape_[0]; ++j) {
				if (j == i)continue;
				if (p.data_[j*mat.shape_[0] + i] != 0.0) {
					p.swap(i, j);
					L.swap(i, j);
				}
			}
		}
	}
	

	for (int i = 0; i < mat.shape_[0]; ++i) {
		NumType scale = p.data_[i*mat.shape_[0] + i];
		if (scale == 0.0) {
			for (int k = i + 1; k < mat.shape_[0]; ++k) {
				if (p.data_[k*mat.shape_[0] + i] != 0.0) {
					p.swap(i, k);
					L.swap(i, k);
					scale = p.data_[i*mat.shape_[0] + i];
					break;
				}
			}
		}
		
		
		for (int j = i + 1; j < mat.shape_[0]; j++) {
			scale = -p.data_[j*mat.shape_[0] + i]/p.data_[i*mat.shape_[0] + i];
			if (scale == 0.0) continue;
			p.rowAdd(i, scale, j);
			L.rowAdd(i, scale, j);
		}
		scale = p.data_[i*mat.shape_[0] + i];
		p.rowScale(i, scale);
		L.rowScale(i, scale);
	}

	
	for (int i = mat.shape_[0]-1; i > 0; --i) {
		for (int j = 0; j < i; j++) {
			NumType scale = -p.data_[j*mat.shape_[0] + i]/ p.data_[i*mat.shape_[0] + i];
			if (scale == 0.0)
				continue;
			p.rowAdd(i, scale, j);
			L.rowAdd(i, scale, j);
		}
	}


	LU[0] = L;
	LU[1] = U;
	return LU;
}

void Matrix::rowAdd(int rowFrom, NumType scale, int addTo) {
	for (int i = 0; i < this->shape_[0]; ++i) {
		this->data_[addTo*this->shape_[0] + i] += scale * this->data_[rowFrom*this->shape_[0] + i];
	}
}
void Matrix::rowScale(int row, NumType scale) {
	for (int i = 0; i < this->shape_[0]; ++i) {
		this->data_[row*this->shape_[0] + i] *= scale;
	}
}

Matrix Matrix::SolveLinear(const Matrix& m) {//Ax=B
	if(this->shape_[0]!=m.shape_[0])
		throw "Dimension is not same!";
	bool zero = true;
	for (int i = 0; i < m.data_.size(); i++) {//判斷B是否為0
		if (m.data_[i] != 0) {
			zero = false;
			break;
		}
	}
	if (zero) {//B為0
		if (this->Rank() == this->shape_[0]) {//唯一均為0解
			Matrix ans(this->shape_[0],1);
			for (int i = 0; i < ans.data_.size(); i++)
				ans.data_[i] = 0;
			return ans;
		}
		else {//參數解
			valarray<Matrix> LU;
			LU.resize(2);
			LU = this->reff();
			int n = this->shape_[0] - this->Rank();
			Matrix y(this->shape_[0], 1);
			Matrix ans(this->shape_[0], n + 1);
			for (int i = 0; i < ans.data_.size(); i++)
				ans.data_[i] = 0;
			for (int i = 0; i < this->shape_[0]; i++) {//Ly=B
				NumType tmp = m.data_[i];
				for (int j = 0; j <= i; j++) {
					if (i == j)
						y.data_[i] = tmp;
					else
						tmp -= LU[0].data_[i*this->shape_[1] + j] * y.data_[j];
				}
			}
			bool *check = NULL;
			check = new bool[this->shape_[0]];
			for (int i = 0; i < this->shape_[0]; i++) {
				check[i] = false;
			}
			int t = 0;
			for (int i = this->shape_[0] - 1; i >= 0; i--) {//Ux=y
				int count = 0;
				for (int k = 0; k <= i; k++) {
					if (LU[1].data_[i*this->shape_[0] + k]) {//判斷幾個未知數
						if (!check[k])
							count++;
					}
				}
				valarray <NumType> tmp;
				tmp.resize(ans.shape_[1]);
				for (int i = 0; i < tmp.size() - 1; i++)
					tmp[i] = 0;
				for (int j = this->shape_[1] - 1; j >= i; j--) {
					tmp[tmp.size()] = y.data_[i];
					if (count == 0)
						break;
					else if (count == 1) {
						if (!check[j]) {
							for (int a = 0; a < ans.shape_[1]; a++)
								ans.data_[j*ans.shape_[1] + a] = tmp[a] / LU[1].data_[i*this->shape_[1] + j];
							count--;
							check[j] = true;
						}
						else {
							for (int a = 0; a < ans.shape_[1]; a++) {
								tmp[a] -= LU[1].data_[i*this->shape_[1] + j] * ans.data_[j*ans.shape_[1] + a];
							}
							count--;
						}
					}
					else {
						if (!check[j]) {
							ans.data_[j*ans.shape_[1]+t]=1;
							t++;
						}
						for (int a = 0; a < ans.shape_[1]; a++) {
							tmp[a] -= LU[1].data_[i*this->shape_[1] + j] * ans.data_[j*ans.shape_[1] + a];
						}
						count--;
					}
				}
				return ans;
			}
		}
	}
	else {//B非0
		Matrix tmp(this->shape_[0],this->shape_[1]);//A|B
		for (int i = 0; i < tmp.data_.size(); i++) {
			if (i%tmp.shape_[1] == tmp.shape_[1] - 1) {
				tmp.data_[i] = m.data_[i / tmp.shape_[1]];
			}
			else
				tmp.data_[i] = this->data_[i - i / tmp.shape_[1]];
		}
		if (this->Rank() == tmp.Rank()) {//Consistent
			if (this->Rank() == this->shape_[0]) {//唯一解
				return this->Inv()*m;
			}
			else {//參數解
				valarray<Matrix> LU;
				LU.resize(2);
				LU = this->reff();
				int n = this->shape_[0] - this->Rank();
				Matrix y(this->shape_[0], 1);
				Matrix ans(this->shape_[0], n + 1);
				for (int i = 0; i < ans.data_.size(); i++)
					ans.data_[i] = 0;
				for (int i = 0; i < this->shape_[0]; i++) {//Ly=B
					NumType tmp = m.data_[i];
					for (int j = 0; j <= i; j++) {
						if (i == j)
							y.data_[i] = tmp;
						else
							tmp -= LU[0].data_[i*this->shape_[1] + j] * y.data_[j];
					}
				}
				bool *check = NULL;
				check = new bool[this->shape_[0]];
				for (int i = 0; i < this->shape_[0]; i++) {
					check[i] = false;
				}
				int t = 0;
				for (int i = this->shape_[0] - 1; i >= 0; i--) {//Ux=y
					int count = 0;
					for (int k = 0; k <= i; k++) {
						if (LU[1].data_[i*this->shape_[0] + k]) {//判斷幾個未知數
							if (!check[k])
								count++;
						}
					}
					valarray <NumType> tmp;
					tmp.resize(ans.shape_[1]);
					for (int i = 0; i < tmp.size() - 1; i++)
						tmp[i] = 0;
					for (int j = this->shape_[1] - 1; j >= i; j--) {
						tmp[tmp.size()] = y.data_[i];
						if (count == 0)
							break;
						else if (count == 1) {
							if (!check[j]) {
								for (int a = 0; a < ans.shape_[1]; a++)
									ans.data_[j*ans.shape_[1] + a] = tmp[a] / LU[1].data_[i*this->shape_[1] + j];
								count--;
								check[j] = true;
							}
							else {
								for (int a = 0; a < ans.shape_[1]; a++) {
									tmp[a] -= LU[1].data_[i*this->shape_[1] + j] * ans.data_[j*ans.shape_[1] + a];
								}
								count--;
							}
						}
						else {
							if (!check[j]) {
								ans.data_[j*ans.shape_[1] + t] = 1;
								t++;
							}
							for (int a = 0; a < ans.shape_[1]; a++) {
								tmp[a] -= LU[1].data_[i*this->shape_[1] + j] * ans.data_[j*ans.shape_[1] + a];
							}
							count--;
						}
					}
					return ans;
				}
			}
		}
		else {//無解
			throw "Inconsistent!";
		}
	}
}

Matrix Matrix::LeastSquare(const Matrix& y) {
	Matrix ans;
	ans = (this->Trans()**this).Inv()*this->Trans()*y;
	return ans;
}

valarray<Matrix> Matrix::Eigen() {
	if(!this->IsSquare())
		throw "Not a Square Matrix !";
	valarray<Matrix> ans;
	ans.resize(2);
	if (this->shape_[0] == 2) {
		NumType det=(this->data_[0]+this->data_[3])*(this->data_[0] + this->data_[3])+4*(this->data_[1]*this->data_[2]+this->data_[0]*this->data_[3]);
		if (det < 0)
			throw "Not support imaginary number solution!";
		else if (det == 0) {
			Matrix E_value(2,2);
			E_value.data_[0] = (this->data_[0]+this->data_[3])/(-2);
			E_value.data_[3] = E_value.data_[0];
			ans[0] = E_value;
			Matrix E_vector(2, 2);
			Vector tmp(2);
			tmp.data_[0] = this->data_[0] - E_value.data_[0];
			tmp.data_[1] = this->data_[2];
			E_vector.data_[0] = tmp.Normalization().data_[0];
			E_vector.data_[1] = E_vector.data_[0];
			E_vector.data_[2] = tmp.Normalization().data_[1];
			E_vector.data_[3] = E_vector.data_[2];
			ans[1] = E_vector;
			return ans;
		}
		else {
			ans.resize(4);
			Matrix E_value(2, 2);
			E_value.data_[0] = (this->data_[0] + this->data_[3]) / (-2) + det;
			E_value.data_[3] = (this->data_[0] + this->data_[3]) / (-2) - det;
			ans[0] = E_value;
			Matrix E_vector(2, 2);
			Vector tmp(2);
			tmp.data_[0] = this->data_[0] - E_value.data_[0];
			tmp.data_[1] = this->data_[2];
			E_vector.data_[0] = tmp.Normalization().data_[0];
			E_vector.data_[2] = tmp.Normalization().data_[1];


			tmp.data_[0] = this->data_[0] - E_value.data_[3];
			tmp.data_[1] = this->data_[2];
			E_vector.data_[1] = tmp.Normalization().data_[0];
			E_vector.data_[3] = tmp.Normalization().data_[1];
			ans[1] = E_vector;
			return ans;
		}
	}
	else if (this->shape_[0] == 3) {
		/*
		[ a-x  b    c]
		[ d   e-x   f]  det=0
		[ g    h  i-x]
		*/
		//-x^3 + (a+e+i)x^2 + (-ae-ai-ei+cg+hf+bd)x+ (aei+cdh+bfg-cge-ahf-bdi) = 0 
		NumType a = -1;
		NumType b = this->data_[0] + this->data_[4] + this->data_[8];
		NumType c = -this->data_[0] * this->data_[4] - this->data_[0] * this->data_[8] - this->data_[4] * this->data_[8] + this->data_[2] * this->data_[6] + this->data_[7] * this->data_[5] + this->data_[1] * this->data_[3];
		NumType d = this->data_[0] * this->data_[4] * this->data_[8] + this->data_[2] * this->data_[3] * this->data_[7] + this->data_[1] * this->data_[5] * this->data_[6] - this->data_[2] * this->data_[6] * this->data_[4] - this->data_[0] * this->data_[7] * this->data_[5] - this->data_[1] * this->data_[3] * this->data_[8];

		NumType det = pow(36 * a*b*c - 8 * pow(b, 3) - 108 * pow(a, 2)*d, 2) + pow(12 * a*c - 4 * pow(b, 2), 3);
		if (det > 0) {
			throw "Not support imaginary number solution!";
		}
		else{
			NumType Alpha, Beta;
			Alpha = (-pow(b, 3) / (27 * pow(a, 3)) + (-d) / (2 * a) + b * c / (6 * pow(a, 2)));
			Beta = c / (3 * a) - pow(b, 2) / (9 * pow(a, 2));
			NumType x[3];
			x[0] = -b / (3 * a) + 2 * sqrt(-Beta)*cos(acos(Alpha / (sqrt(pow(-Beta, 3)))) / 3);
			x[1] = -b / (3 * a) + 2 * sqrt(-Beta)*cos(acos(Alpha / (sqrt(pow(-Beta, 3))))+2*PI / 3);
			x[2] = -b / (3 * a) + 2 * sqrt(-Beta)*cos(acos(Alpha / (sqrt(pow(-Beta, 3))))-2*PI / 3);
			for (int i = 0; i < 2; i++) {//大的放前面
				for (int j = i + 1; j < 3; j++) {
					if (x[j] > x[i]) {
						NumType tmp = x[i];
						x[i] = x[j];
						x[j] = tmp;
					}
				}
			}

			Matrix E_value(3, 3);
			E_value.data_[0] = x[0];
			E_value.data_[4] = x[1];
			E_value.data_[8] = x[2];

			Matrix E_vector(3, 3);
			
			Vector tmp(3);
			tmp.data_[0] = this->data_[0] - x[0];
			tmp.data_[1] = this->data_[3];
			tmp.data_[2] = this->data_[6];

			E_vector.data_[0] = tmp.Normalization().data_[0];
			E_vector.data_[3] = tmp.Normalization().data_[1];
			E_vector.data_[6] = tmp.Normalization().data_[2];

			tmp.data_[0] = this->data_[0] - x[1];
			tmp.data_[1] = this->data_[3];
			tmp.data_[2] = this->data_[6];

			E_vector.data_[1] = tmp.Normalization().data_[0];
			E_vector.data_[4] = tmp.Normalization().data_[1];
			E_vector.data_[7] = tmp.Normalization().data_[2];

			tmp.data_[0] = this->data_[0] - x[2];
			tmp.data_[1] = this->data_[3];
			tmp.data_[2] = this->data_[6];

			E_vector.data_[2] = tmp.Normalization().data_[0];
			E_vector.data_[5] = tmp.Normalization().data_[1];
			E_vector.data_[8] = tmp.Normalization().data_[2];

			ans[0] = E_value;
			ans[1] = E_vector;
			return ans;
		}
	}
	
}