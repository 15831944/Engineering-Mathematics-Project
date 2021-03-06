#include "Matrix.h"

int rowOptime;

Matrix::Matrix(int rSize, int cSize) {
	// check
	if (rSize <= 0 || cSize <= 0)
		throw std::runtime_error("Wrong Size!");
	//
	this->data_.resize(rSize*cSize);
	this->shape_[0] = rSize;
	this->shape_[1] = cSize;
}

Matrix::Matrix(Vector v) {
	Matrix m(v.dim_, 1);
	m.data_ = v.data_;
	*this = m;
}

Matrix::Matrix(int rSize, int cSize, initializer_list<NumType> args) {
	// check
	if (rSize <= 0 || cSize <= 0)
		throw std::runtime_error("Wrong Size!");
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
		throw std::runtime_error("Dimension is not same!");
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
		throw std::runtime_error("Dimension is not same!");
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
	this->data_ = m.data_;
	return *this;
}

Matrix Matrix::operator=(initializer_list<NumType> args) {
	if(this->data_.size()!=args.size())
		throw std::runtime_error("Dimension is not same!");
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
		throw std::runtime_error("Error dimension!");
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

Matrix Matrix::operator*(const Vector& rhs) {
	Matrix r(rhs.dim_, 1);
	r.data_ = rhs.data_;
	return *this * r;
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

Matrix Matrix::Scale(NumType scale) {
	Matrix result = *this;
	result.data_ *= scale;
	return result;
}

bool Matrix::IsSquare() {
	return this->shape_[0] >= 1 && this->shape_[1] >= 1 && this->shape_[0] == this->shape_[1];
}

Matrix Matrix::MiniorMat_(int row, int col) {
	// check
	if (!this->IsSquare())
		throw std::runtime_error("Not a Square Matrix !");
	if (row < 0 || col < 0)
		throw std::runtime_error("Row and Column are start from 1!");
	if (row >= this->shape_[0] || col >= this->shape_[1])
		throw std::runtime_error("Row or Column is out of range!");
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
		if (abs(tmp.data_[row*this->shape_[1] + row])>=0.000001) {//耞琌0
			for (int col = row + 1; col < this->shape_[0]; col++) {
				NumType mult = tmp.data_[col*this->shape_[1]+row] / tmp.data_[row*this->shape_[1] + row];
				//tmp.data_[col*tmp.shape_[1] + row] = 0;
				for (int i = row; i < tmp.shape_[1]; i++) {
					tmp.data_[col*tmp.shape_[1] + i] -= mult * tmp.data_[row*this->shape_[1] + i];
				}
			}
		}
		else
		{
			for (int i = row + 1; i < tmp.shape_[0]; i++) {
				if (abs(tmp.data_[i*tmp.shape_[1]+row])>=0.000001) {
					tmp.swap(row, i);
					row--;
					break;
				}
			}
		}
	}
	bool check = true;
	for (int i = 0; i < tmp.shape_[0]; i++) {//耞0Τ碭
		check = true;
		for (int j = 0; j < tmp.shape_[1]; j++) {
			if (abs(tmp.data_[i*tmp.shape_[1] + j])>= 0.000001) {
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
		throw std::runtime_error("Empty Matrix!");
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
		throw std::runtime_error("Not a Square Matrix !");
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
		throw std::runtime_error("Not a Square Matrix !");
	//
	if (this->shape_[0] == 1) {
		if(this->data_[0] == 0.0)
			throw std::runtime_error("Invertable !");
		Matrix inv(1, 1);
		inv.data_[0] = 1 / this->data_[0];
		return inv;
	}


	//
	NumType det = this->Det();
	if (det == 0.0)
		throw std::runtime_error("singular");

	Matrix result = this->Adj();
	result.data_ *= 1 / det;

	return result;
}

NumType Matrix::Cofactor(int row, int col) {
	// check
	if (!this->IsSquare())
		throw std::runtime_error("Not a Square Matrix !");
	//

	//Note that row and col start form 0 !
	NumType result = (row + col) % 2 == 0 ? 1.0 : -1.0;
	result *= this->MiniorMat_(row, col).Det();
	return result;
}

NumType Matrix::Det() {
	// check
	if (!this->IsSquare()) 
		throw std::runtime_error("Not a Square Matrix !");
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
		throw std::runtime_error("ぃ秆");
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
			scale = -mat.data_[j*mat.shape_[0] + i] / (mat.data_[i*mat.shape_[0] + i]+DELTA);
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
		throw std::runtime_error("Not a Square Matrix !");
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
		throw std::runtime_error("ぃ秆");
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
			scale = -mat.data_[j*mat.shape_[0] + i] / (mat.data_[i*mat.shape_[0] + i]+DELTA);
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
			scale = -p.data_[j*mat.shape_[0] + i]/(p.data_[i*mat.shape_[0] + i]+DELTA);
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
			NumType scale = -p.data_[j*mat.shape_[0] + i]/ (p.data_[i*mat.shape_[0] + i]+DELTA);
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
		throw std::runtime_error("Dimension is not same!");
	bool zero = true;
	for (int i = 0; i < m.data_.size(); i++) {//耞B琌0
		if (m.data_[i] != 0) {
			zero = false;
			break;
		}
	}
	if (zero) {//B0
		if (this->Rank() == this->shape_[0]) {//斑А0秆
			Matrix ans(this->shape_[0],1);
			for (int i = 0; i < ans.data_.size(); i++)
				ans.data_[i] = 0;
			return ans;
		}
		else {//把计秆
			throw std::runtime_error("Error!");
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
					if (LU[1].data_[i*this->shape_[0] + k]) {//耞碭ゼ计
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
	else {//B獶0
		Matrix tmp(this->shape_[0],this->shape_[1]+1);//A|B
		for (int i = 0; i < tmp.data_.size(); i++) {
			if (i%tmp.shape_[1] == tmp.shape_[1] - 1) {
				tmp.data_[i] = m.data_[i / tmp.shape_[1]];
			}
			else
				tmp.data_[i] = this->data_[i - i / tmp.shape_[1]];
		}
		//int a = this->Rank();
		//int b = tmp.Rank();
		if (this->Rank() == tmp.Rank()) {//Consistent
			
			if (this->Rank() == this->shape_[0]) {//斑秆
				return this->Inv()*m;
			}
			else {//把计秆
				int rank = this->shape_[0];
				for (int row = 0; row < tmp.shape_[0]; row++) {
					if (abs(tmp.data_[row*tmp.shape_[1] + row]) >= 0.000001) {//耞琌0
						for (int col = row + 1; col < tmp.shape_[0]; col++) {
							NumType mult = tmp.data_[col*tmp.shape_[1] + row] / tmp.data_[row*tmp.shape_[1] + row];
							for (int i = row; i < tmp.shape_[1]; i++) {
								tmp.data_[col*tmp.shape_[1] + i] -= mult * tmp.data_[row*tmp.shape_[1] + i];
							}
						}
					}
					else
					{
						for (int i = row + 1; i < tmp.shape_[0]; i++) {
							if (abs(tmp.data_[i*tmp.shape_[1] + row]) >= 0.000001) {
								tmp.swap(row, i);
								row--;
								break;
							}
						}
					}
				}

				int n = tmp.shape_[0] - tmp.Rank();
				Matrix ans(this->shape_[0],  n + 1);


				bool *check = NULL;
				check = new bool[this->shape_[1]];
				for (int i = 0; i < this->shape_[1]; i++) {
					check[i] = false;
				}
				int t = 0;
				for (int i = this->shape_[0] - 1; i >= 0; i--) {
					valarray<NumType> solution;
					solution.resize(n+1);
					solution[n] = tmp.data_[(i+1)*tmp.shape_[1] -1];
					int count = 0;
					for (int k = 0; k <tmp.shape_[1]-1; k++) {
						if (abs(tmp.data_[i*tmp.shape_[1] + k]) >0.000001) {//耞碭ゼ计
							if (!check[k])
								count++;
						}
					}
					for (int j = this->shape_[1] - 1; j >= i; j--) {
						if (count == 0)
							break;
						else if (count == 1) {//逞ゼ计
							if (!check[j]) {
								for (int col = 0; col < solution.size(); col++) {
									ans.data_[j*ans.shape_[1] + col] = solution[col]/tmp.data_[i*tmp.shape_[1]+j];
								}
								count--;
								check[j] = true;
							}
						}
						else {//ゼ计
							if (!check[j]) {//ゼ倒把计ぇゼ计
								ans.data_[j*ans.shape_[1] + t] = 1;
								solution[t] -= tmp.data_[i*tmp.shape_[1] + j];
								check[j] = true;
								t++;
							}
							else {//计
								for (int col = 0; col < solution.size(); col++) {
									solution[col] -= tmp.data_[i*tmp.shape_[1] + j] * ans.data_[j*ans.shape_[1] + col];
								}
							}
							count--;
						}
					}
					
				}
				return ans;
			}
		}
		else {//礚秆
			throw std::runtime_error("Inconsistent!");
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
		throw std::runtime_error("Not a Square Matrix !");
	valarray<Matrix> ans;
	ans.resize(2);
	if (this->shape_[0] == 2) {
		NumType det=(this->data_[0]+this->data_[3])*(this->data_[0] + this->data_[3])-4*(-this->data_[1]*this->data_[2]+this->data_[0]*this->data_[3]);
		if (det < 0 && abs(det) >=0.000001 )
			throw std::runtime_error("Not support imaginary number solution!");
		else if (abs(det) <= 0.000001) {//
			NumType v1, v2;
			v1 = ((this->data_[0] + this->data_[3])) / 2;
			Matrix K1(2, 1);
			NumType a1, a2;
			a1 = this->data_[0] - v1;
			a2 = this->data_[1];
			Vector tmp(2);
			tmp.data_[0] = a1;
			tmp.data_[1] = -a2;
			tmp = tmp.Normalization();
			K1.data_[0] = tmp.data_[0];
			K1.data_[1] = tmp.data_[1];

			Matrix P(2, 2);
			P.data_[0] = K1.data_[0];
			P.data_[1] = K1.data_[0];
			P.data_[2] = K1.data_[1];
			P.data_[3] = K1.data_[1];

			Matrix D(2, 2);
			D.data_[0] = v1;
			D.data_[3] = v1;

			ans[0] = D;
			ans[1] = P;
			return ans;
		}
		else
		{
			NumType v1, v2;
			v1 = ((this->data_[0] + this->data_[3]) + sqrt(det)) / 2;
			Matrix K1(2, 1);
			NumType a1, a2;
			a1 = this->data_[0] - v1;
			a2 = this->data_[1];
			Vector tmp(2);
			tmp.data_[0] = a2;
			tmp.data_[1] = -a1;
			tmp = tmp.Normalization();
			K1.data_[0] = tmp.data_[0];
			K1.data_[1] = tmp.data_[1];


			v2 = ((this->data_[0] + this->data_[3]) - sqrt(det)) / 2;
			Matrix K2(2, 1);
			a1 = this->data_[0] - v2;
			a2 = this->data_[1];
			tmp.data_[0] = a2;
			tmp.data_[1] = -a1;
			tmp = tmp.Normalization();
			K2.data_[0] = tmp.data_[0];
			K2.data_[1] = tmp.data_[1];

			Matrix P(2, 2);
			P.data_[0] = K1.data_[0];
			P.data_[1] = K2.data_[0];
			P.data_[2] = K1.data_[1];
			P.data_[3] = K2.data_[1];

			Matrix D(2, 2);
			D.data_[0] = v1;
			D.data_[3] = v2;

			ans[0] = D;
			ans[1] = P;
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
		if (det > 0.000001) {
			throw std::runtime_error("Not support imaginary number solution!");
		}
		else {
			NumType Alpha, Beta;
			Alpha = (-pow(b, 3) / (27 * pow(a, 3)) + (-d) / (2 * a) + b * c / (6 * pow(a, 2)));
			Beta = c / (3 * a) - pow(b, 2) / (9 * pow(a, 2));
			NumType x[3];
			x[0] = -b / (3 * a) + 2 * sqrt(-Beta)*cos(acos(Alpha / (sqrt(pow(-Beta, 3)))) / 3);
			x[1] = -b / (3 * a) + 2 * sqrt(-Beta)*cos((acos(Alpha / (sqrt(pow(-Beta, 3)))) + 2 * PI) / 3);
			x[2] = -b / (3 * a) + 2 * sqrt(-Beta)*cos((acos(Alpha / (sqrt(pow(-Beta, 3)))) - 2 * PI) / 3);


			Matrix D(3, 3);
			D.data_[0] = x[0];
			D.data_[4] = x[1];
			D.data_[8] = x[2];

			valarray<Vector> E_vector;
			E_vector.resize(3);
			for (int i = 0; i < 3; i++)
			{
				E_vector[i].data_.resize(3);
				E_vector[i].dim_ = 3;
				E_vector[i]=E_vector[i].Scalar(0);
			}

			for (int j = 0; j < 3; j++)
			{

				Matrix tmp = *this;
				tmp.data_[0] -= x[j];
				tmp.data_[4] -= x[j];
				tmp.data_[8] -= x[j];

				for (int row = 0; row < tmp.shape_[0]; row++) {
				if (abs(tmp.data_[row*this->shape_[1] + row]) >= 0.000001) {//耞琌0
					for (int col = row + 1; col < this->shape_[0]; col++) {
						NumType mult = tmp.data_[col*this->shape_[1] + row] / tmp.data_[row*this->shape_[1] + row];
						//tmp.data_[col*tmp.shape_[1] + row] = 0;
						for (int i = row; i < tmp.shape_[1]; i++) {
							tmp.data_[col*tmp.shape_[1] + i] -= mult * tmp.data_[row*this->shape_[1] + i];
						}
					}
				}
				else
				{
					for (int i = row + 1; i < tmp.shape_[0]; i++) {
						if (abs(tmp.data_[i*tmp.shape_[1] + row]) >= 0.000001) {
							tmp.swap(row, i);
							row--;
							break;
						}
					}
				}
			}

				if (abs(tmp.data_[5]) >= 0.000001)
				{
					if (abs(tmp.data_[4]) >= 0.000001)
					{
						E_vector[j].data_[2] = 1;
						E_vector[j].data_[1] = -tmp.data_[5] / tmp.data_[4];
						if (abs(tmp.data_[0]) >= 0.000001)
							E_vector[j].data_[0] = -(tmp.data_[1] * E_vector[j].data_[1] + tmp.data_[2] * E_vector[j].data_[2]) / tmp.data_[0];
					}
					else
					{
						E_vector[j].data_[2] = 0;
						E_vector[j].data_[0] = tmp.data_[1];
						E_vector[j].data_[1] = -tmp.data_[0];
					}
				}
				else
				{
					E_vector[j].data_[1] = 0;
					E_vector[j].data_[0] = tmp.data_[2];
					E_vector[j].data_[2] = -tmp.data_[0];
				}

				E_vector[j]=E_vector[j].Normalization();
			}
			
			Matrix P(3, 3);
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					P.data_[3*j+i] = E_vector[i].data_[j];
				}
			}
			ans[0] = D;
			ans[1] = P;
			return ans;
		}
	}
	
}

valarray<Matrix> Matrix::PowerEigen() {
	if (!IsSquare())
		throw std::runtime_error("not a square");
	int times=15;
	Matrix tmp;
	tmp.shape_[0] = this->shape_[0];
	tmp.shape_[1] = 1;
	tmp.data_.resize(tmp.shape_[0]);
	for (int i = 0; i < tmp.data_.size(); i++)
		tmp.data_[i] = 1;
	for (int i = 0; i < times; i++)
		tmp = *this*tmp;
	valarray<NumType> data;
	data = tmp.data_;
	Vector ans(data);
	Matrix E_value(1,1);
	E_value.data_[0] = ans.Norm();
	ans = ans.Normalization();
	data = ans.data_;
	Matrix E_vector;
	E_vector.shape_[0] = this->shape_[0];
	E_vector.shape_[1] = 1;
	E_vector.data_ = data;
	valarray<Matrix> eigen;
	eigen.resize(2);
	eigen[0] = E_value;
	eigen[1] = E_vector;
	return eigen;
}

Matrix Matrix::vecMulMat(Vector v1, Vector v2) {
	Matrix m1(v1.dim_, 1), m2(1, v2.dim_);
	m1.data_ = v1.data_;
	m2.data_ = v2.data_;
	return m1 * m2;
}
