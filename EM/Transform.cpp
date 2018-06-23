#include "Transform.h"

#include <cmath>




Bitmap^ ToGrayscale(Bitmap^ pic) {
	Bitmap^ result = gcnew Bitmap(pic->Size.Width, pic->Size.Height);
	for (int n = 0; n < pic->Size.Width; ++n) {
		for (int m = 0; m < pic->Size.Height; ++m) {
			Color c = pic->GetPixel(n, m);
			float gray = 0.299*c.R + 0.587*c.G + 0.114*c.B;
			result->SetPixel(n,m,Color::FromArgb(gray,gray,gray));
		}
	}
	return result;
}

Matrix ToGrayscaleMat(Bitmap^ pic) {
	Matrix result(pic->Size.Height, pic->Size.Width);
	for (int n = 0; n < pic->Size.Width; ++n) {
		for (int m = 0; m < pic->Size.Height; ++m) {
			Color c = pic->GetPixel(n, m);
			float gray = 0.299*c.R + 0.587*c.G + 0.144*c.B;
			result.data_[m*pic->Size.Width+n]=gray;
		}
	}
	return result;
}

Matrix FourierPanning(Matrix mat) {
	for (int n = 0; n < mat.shape_[1]; ++n) {
		for (int m = 0; m < mat.shape_[0]; ++m) {
			int idx = m * mat.shape_[1] + n;
			mat.data_[idx] *= pow(-1, n + m);
		}
	}
	return mat;
}

Matrix Scale(Matrix mat, int m, int n) {
	Matrix result(m, n);
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			int ni = i * mat.shape_[0] / m,nj=j*mat.shape_[1]/n;
			result.data_[i*n + j] = mat.data_[ni*mat.shape_[1] + nj];
		}
	}
	return result;
}

Matrix FourierPadding(Matrix mat) {
	int size[2];
	size[0] = pow(2, ceil(log2(mat.shape_[0])));
	size[1] = pow(2, ceil(log2(mat.shape_[1])));
	Matrix result = Scale(mat, size[0], size[1]);
	return result;
}

NumType dealCom(complex<NumType> c) {
	return log10(1 + sqrt(pow(c.real(), 2) + pow(c.imag(), 2))) * 255 / 4.0;
}

complex<NumType> DFT(const Matrix& mat, int u, int v) {
	complex<NumType> result(0,0);
	for (int m = 0; m < mat.shape_[0]; ++m) {
		for (int n = 0; n < mat.shape_[1]; ++n) {
			double t = -2.0 * PI*(u*m/(NumType)(mat.shape_[0]) + v * n / (NumType)(mat.shape_[1]));
			int idx = m * mat.shape_[1] + n;
			complex<NumType> tmp(cos(t), sin(t));
			result += mat.data_[idx] * tmp;
		}
	}
	result *= 1.0 / sqrt(mat.shape_[0] * mat.shape_[1]);
	return result;
}



Matrix DiscreteFourierTransform(Matrix mat) {
	Matrix result(mat.shape_[0], mat.shape_[1]);
	// panning
	mat = FourierPanning(mat);
	for (int u = 0; u < mat.shape_[0]; ++u) {
		for (int v = 0; v < mat.shape_[1]; ++v) {
			complex<NumType> tmp = DFT(mat, u, v);
			NumType val = dealCom(tmp); //sqrt(tmp.real()*tmp.real() + tmp.imag()*tmp.imag());

			result.data_[u*mat.shape_[1] + v] = val;
		}
	}
	result.data_ -= result.data_.min();
	result.data_ /= result.data_.max();
	result.data_ *= 255;
	return result;
}

Bitmap^ DiscreteFourierTransform(Bitmap^ pic) {
	Matrix mat = ToGrayscaleMat(pic);
	//mat = Scale(mat, 64, 64);
	mat = DiscreteFourierTransform(mat);
	Bitmap^ result = gcnew Bitmap(mat.shape_[0], mat.shape_[1]);
	for (int i = 0; i < mat.shape_[0]; ++i) {
		for (int j = 0; j < mat.shape_[1]; ++j) {
			float c = mat.data_[i*mat.shape_[1] + j];
			result->SetPixel(j, i, Color::FromArgb(c, c, c));
		}
	}
	return result;
}

complex<NumType> InvDFT(const Matrix& mat, int u, int v) {
	complex<NumType> result(0, 0);
	for (int m = 0; m < mat.shape_[0]; ++m) {
		for (int n = 0; n < mat.shape_[1]; ++n) {
			double t = 2.0 * PI*(u*m / (NumType)(mat.shape_[0]) + v * n / (NumType)(mat.shape_[1]));
			int idx = m * mat.shape_[1] + n;
			complex<NumType> tmp(cos(t),sin(t));
			result += mat.data_[idx] *tmp;
		}
	}
	result *= 1.0 / sqrt(mat.shape_[0] * mat.shape_[1]);
	return result;
}

Matrix InvDiscreteFourierTransform(Matrix mat) {
	Matrix result(mat.shape_[0], mat.shape_[1]);
	// panning
	mat = FourierPanning(mat);
	for (int u = 0; u < mat.shape_[0]; ++u) {
		for (int v = 0; v < mat.shape_[1]; ++v) {
			complex<NumType> tmp = InvDFT(mat, u, v);
			NumType val = dealCom(tmp);
			result.data_[u*mat.shape_[1] + v] = val;
		}
	}
	result.data_ -= result.data_.min();
	result.data_ /= result.data_.max();
	result.data_ *= 255;
	return result;
}

Bitmap^ InvDiscreteFourierTransform(Bitmap^ pic) {
	Matrix mat = ToGrayscaleMat(pic);
	Bitmap^ result = gcnew Bitmap(pic->Width, pic->Height);
	mat = InvDiscreteFourierTransform(mat);
	for (int i = 0; i < pic->Height; ++i) {
		for (int j = 0; j < pic->Width; ++j) {
			float c = mat.data_[i*pic->Width + j];
			result->SetPixel(j, i, Color::FromArgb(c, c, c));
		}
	}
	return result;
}


void separate(vector<complex<NumType>>::iterator a, int n) {
	vector<complex<double>> b (n / 2);  
	for (int i = 0; i<n / 2; i++)    
		b[i] = *(a+(i * 2 + 1));
	for (int i = 0; i<n / 2; i++)   
		a[i] = *(a + (i * 2));
	for (int i = 0; i<n / 2; i++)    
		a[i + n / 2] = b[i];
}
void fft2(vector<complex<NumType>>::iterator X, int N) {
	if (N <2)
		return;
	separate(X, N);      
	fft2(X, N / 2);   
	fft2(X + N / 2, N / 2); 						 
	for (int k = 0; k<N / 2; k++) {
		complex<double> e = *(X+k);  
		complex<double> o = *(X+k + N / 2);
		complex<double> w = exp(complex<double>(0, -2.*PI*k / N));
		X[k] = e + w * o;
		X[k + N / 2] = e - w * o;
	}
}

void invfft2(vector<complex<NumType>>::iterator X, int N) {
	if (N <2)
		return;
	separate(X, N);
	fft2(X, N / 2);
	fft2(X + N / 2, N / 2);
	for (int k = 0; k<N / 2; k++) {
		complex<double> e = *(X + k);
		complex<double> o = *(X + k + N / 2);
		complex<double> w = exp(complex<double>(0, 2.*PI*k / N));
		X[k] = e + w * o;
		X[k + N / 2] = e - w * o;
	}
}

Matrix FastFourierTransform(Matrix mat) {
	vector<vector<complex<NumType>>> result(mat.shape_[0]);

	mat = FourierPanning(mat);
	// matrix to store sp
	Matrix matResult(mat.shape_[0], mat.shape_[1]);
	// init result complex matrix 
	for (int i = 0; i < mat.shape_[0]; ++i)
		result[i].resize(mat.shape_[1]);

	// do for each row
	for (int m = 0; m < mat.shape_[0]; ++m) {
		vector<complex<NumType>>  tmp(mat.shape_[1]);
		// prepare row vector 
		for (int n = 0; n < mat.shape_[1]; ++n) {
			tmp[n] = mat.data_[m*mat.shape_[1] + n];
		}
		// do 1d fft
		//FFT1D(tmp);
		fft2(tmp.begin(), mat.shape_[1]);
		// store in complex matrix
		for (int n = 0; n < mat.shape_[1]; ++n) {
			result[m][n]=tmp[n] / sqrt(mat.shape_[1]);
		}
		//delete[] tmp;
	}
	
	for (int n = 0; n < mat.shape_[1]; ++n) {
		vector<complex<NumType>>  tmp(mat.shape_[0]);
		// prepare column vector
		for (int m = 0; m < mat.shape_[0]; ++m) {
			tmp[m] = result[m][n];
		}
		// do 1 d fft
		fft2(tmp.begin(), mat.shape_[0]);
		// store in mat
		for (int m = 0; m < mat.shape_[0]; ++m) {
			NumType val = dealCom(tmp[m]/sqrt(mat.shape_[0]));
			matResult.data_[m*mat.shape_[1] + n] = val;
		}
		
		//delete[] tmp;
	}
	matResult.data_ -= matResult.data_.min();
	matResult.data_ /= matResult.data_.max();
	matResult.data_ *= 255;
	return matResult;
}

Bitmap^ FastFourierTransform(Bitmap^ pic) {
	Matrix mat = ToGrayscaleMat(pic);
	mat = FourierPadding(mat);
	mat = FastFourierTransform(mat);

	// deal mat

	Bitmap^ result = gcnew Bitmap(mat.shape_[0], mat.shape_[1]);
	for (int i = 0; i < mat.shape_[0]; ++i) {
		for (int j = 0; j < mat.shape_[1]; ++j) {
			float c = mat.data_[i*mat.shape_[1] + j];
			result->SetPixel(j, i, Color::FromArgb(c, c, c));
		}
	}
	return result;
}

Matrix InvFastFourierTransform(Matrix mat) {
	vector<vector<complex<NumType>>> result(mat.shape_[0]);

	mat = FourierPanning(mat);
	// matrix to store sp
	Matrix matResult(mat.shape_[0], mat.shape_[1]);
	// init result complex matrix 
	for (int i = 0; i < mat.shape_[0]; ++i)
		result[i].resize(mat.shape_[1]);

	// do for each row
	for (int m = 0; m < mat.shape_[0]; ++m) {
		vector<complex<NumType>>  tmp(mat.shape_[1]);
		// prepare row vector 
		for (int n = 0; n < mat.shape_[1]; ++n) {
			tmp[n] = mat.data_[m*mat.shape_[1] + n];
		}
		// do 1d fft
		//FFT1D(tmp);
		invfft2(tmp.begin(), mat.shape_[1]);
		// store in complex matrix
		for (int n = 0; n < mat.shape_[1]; ++n) {
			result[m][n] = tmp[n]/sqrt(mat.shape_[1]);
		}
		//delete[] tmp;
	}

	for (int n = 0; n < mat.shape_[1]; ++n) {
		vector<complex<NumType>>  tmp(mat.shape_[0]);
		// prepare column vector
		for (int m = 0; m < mat.shape_[0]; ++m) {
			tmp[m] = result[m][n];
		}
		// do 1 d fft
		invfft2(tmp.begin(), mat.shape_[0]);
		// store in mat
		for (int m = 0; m < mat.shape_[0]; ++m) {
			NumType val = dealCom(tmp[m]/sqrt(mat.shape_[0]));
			matResult.data_[m*mat.shape_[1] + n] = val;
		}

		//delete[] tmp;
	}
	matResult.data_ -= matResult.data_.min();
	matResult.data_ /= matResult.data_.max();
	matResult.data_ *= 255;
	return matResult;
}

Bitmap^ InvFastFourierTransform(Bitmap^ pic) {
	Matrix mat = ToGrayscaleMat(pic);
	mat = FourierPadding(mat);
	mat = InvFastFourierTransform(mat);
	// deal mat
	Bitmap^ result = gcnew Bitmap(mat.shape_[0], mat.shape_[1]);
	for (int i = 0; i < mat.shape_[0]; ++i) {
		for (int j = 0; j < mat.shape_[1]; ++j) {
			float c = mat.data_[i*mat.shape_[1] + j];
			result->SetPixel(j, i, Color::FromArgb(c, c, c));
		}
	}
	return result;
}

vector<vector<complex<NumType>>> mat2Cmat(Matrix mat) {
	vector<vector<complex<NumType>>> cmat(mat.shape_[0]);
	for (int i = 0; i < mat.shape_[1]; ++i)
		cmat[i].resize(mat.shape_[1]);
	for (int m = 0; m < mat.shape_[0]; ++m) {
		for (int n = 0; n < mat.shape_[1]; ++n) {
			cmat[m][n] = mat.data_[m*mat.shape_[1] + n];
		}
	}
	return cmat;
}

Matrix cmat2Mat(vector<vector<complex<NumType>>> cmat,bool bound) {
	Matrix mat(cmat.size(), cmat[0].size());
	for (int m = 0; m < cmat.size(); ++m) {
		for (int n = 0; n < cmat[m].size(); ++n) {
			NumType val = dealCom(cmat[m][n]);
			mat.data_[m*mat.shape_[1] + n] = val;
		}
	}
	mat.data_ -= mat.data_.min();
	mat.data_ /= mat.data_.max();
	mat.data_ *= 255;
	for (int i = 0; i < mat.data_.size(); ++i) {
		mat.data_[i] = mat.data_[i] < 255 ? mat.data_[i] : 255;
		mat.data_[i] = mat.data_[i] > 0 ? mat.data_[i] : 0;
	}
	return mat;
}

vector<vector<complex<NumType>>> FFT(vector<vector<complex<NumType>>> cmat) {

	for (int m = 0; m < cmat.size(); ++m) {
		vector<complex<NumType>>  tmp(cmat[m].size());
		// prepare row vector 
		for (int n = 0; n < cmat[m].size(); ++n) {
			tmp[n] = cmat[m][n];
		}
		// do 1d fft
		//FFT1D(tmp);
		fft2(tmp.begin(), cmat[m].size());
		// store in complex matrix
		for (int n = 0; n < cmat[m].size(); ++n) {
			NumType div;
			div = 1;
			cmat[m][n] = tmp[n]/div;
		}
		//delete[] tmp;
	}

	for (int n = 0; n < cmat[0].size(); ++n) {
		vector<complex<NumType>>  tmp(cmat[n].size());
		// prepare column vector
		for (int m = 0; m < cmat[n].size(); ++m) {
			tmp[m] = cmat[m][n];
		}
		// do 1 d fft
		fft2(tmp.begin(), cmat[n].size());
		// store in mat
		for (int m = 0; m < cmat[n].size(); ++m) {
			NumType div;
			div = 1;
			cmat[m][n] = tmp[m]/div;
		}
		//delete[] tmp;
	}
	return cmat;
}

vector<vector<complex<NumType>>> iFFT(vector<vector<complex<NumType>>> cmat) {
	// v trans
	
	vector<vector<complex<NumType>>> tmp = cmat;
	for (int i = 0; i < cmat.size(); ++i) {
		for (int j = 0; j < cmat[i].size(); ++j) {
			cmat[i][j] = tmp[cmat.size()-1-i][cmat[i].size()-1-j];
		}
	}



	for (int m = 0; m < cmat.size(); ++m) {
		vector<complex<NumType>>  tmp(cmat[m].size());
		// prepare row vector 
		for (int n = 0; n < cmat[m].size(); ++n) {
			tmp[n] = cmat[m][n];
		}
		// do 1d fft
		//FFT1D(tmp);
		fft2(tmp.begin(), cmat[m].size());
		// store in complex matrix
		for (int n = 0; n < cmat[m].size(); ++n) {
			NumType div;
			div = cmat[m].size();
			cmat[m][n] = tmp[n] / div;
		}
		//delete[] tmp;
	}

	for (int n = 0; n < cmat[0].size(); ++n) {
		vector<complex<NumType>>  tmp(cmat[n].size());
		// prepare column vector
		for (int m = 0; m < cmat[n].size(); ++m) {
			tmp[m] = cmat[m][n];
		}
		// do 1 d fft
		fft2(tmp.begin(), cmat[n].size());
		// store in mat
		for (int m = 0; m < cmat[n].size(); ++m) {
			NumType div;
			div = cmat.size();
			cmat[m][n] = tmp[m] / div;
		}
		//delete[] tmp;
	}
	return cmat;

	
	return cmat;
}

Bitmap^ Test(Bitmap^ pic) {
	Matrix mat = ToGrayscaleMat(pic);
	mat = FourierPadding(mat);
	//mat = FourierPanning(mat);
	mat = cmat2Mat(iFFT(FFT(mat2Cmat(mat))),true);
	// deal mat

	Bitmap^ result = gcnew Bitmap(mat.shape_[0], mat.shape_[1]);
	for (int i = 0; i < mat.shape_[0]; ++i) {
		for (int j = 0; j < mat.shape_[1]; ++j) {
			float c = mat.data_[i*mat.shape_[1] + j];
			result->SetPixel(j, i, Color::FromArgb(c, c, c));
		}
	}
	return result;
}


void l(vector<vector<complex<NumType>>>& cmat, double d) {
	int h = cmat.size() / 2, w = cmat[0].size() / 2;
	for (int i = 0; i < cmat.size(); ++i) {
		for (int j = 0; j < cmat[0].size(); ++j) {
			double dis = sqrt(pow(h - i, 2) + pow(w - j, 2));
			cmat[i][j] *= 1/(1+pow(dis/d,2*cmat.size()));
		}
	}
}

void h(vector<vector<complex<NumType>>>& cmat, double d) {
	int h = cmat.size() / 2, w = cmat[0].size() / 2;
	for (int i = 0; i < cmat.size(); ++i) {
		for (int j = 0; j < cmat[0].size(); ++j) {
			double dis = sqrt(pow(h - i, 2) + pow(w - j, 2));
			cmat[i][j] *= 1 - ( 1 / (1 + pow(dis / d, 2 * cmat.size())));

		}
	}
}

Bitmap^ LowPassSpect(Bitmap^ pic) {
	Matrix mat = ToGrayscaleMat(pic);
	mat = FourierPadding(mat);
	mat = FourierPanning(mat);
	//mat = cmat2Mat(iFFT(FFT(mat2Cmat(mat))), true);
	vector<vector<complex<NumType>>> cmat = FFT(mat2Cmat(mat));
	l(cmat, mat.shape_[0] / 10);
	//cmat = iFFT(cmat);
	mat = cmat2Mat(cmat, true);

	// deal mat

	Bitmap^ result = gcnew Bitmap(mat.shape_[0], mat.shape_[1]);
	for (int i = 0; i < mat.shape_[0]; ++i) {
		for (int j = 0; j < mat.shape_[1]; ++j) {
			float c = mat.data_[i*mat.shape_[1] + j];
			result->SetPixel(j, i, Color::FromArgb(c, c, c));
		}
	}
	return result;
}

Bitmap^ LowPassFilter(Bitmap^ pic) {
	Matrix mat = ToGrayscaleMat(pic);
	mat = FourierPadding(mat);
	mat = FourierPanning(mat);
	//mat = cmat2Mat(iFFT(FFT(mat2Cmat(mat))), true);
	vector<vector<complex<NumType>>> cmat = FFT(mat2Cmat(mat));
	l(cmat, mat.shape_[0]/10);
	cmat = iFFT(cmat);
	mat = cmat2Mat(cmat, true);

	// deal mat

	Bitmap^ result = gcnew Bitmap(mat.shape_[0], mat.shape_[1]);
	for (int i = 0; i < mat.shape_[0]; ++i) {
		for (int j = 0; j < mat.shape_[1]; ++j) {
			float c = mat.data_[i*mat.shape_[1] + j];
			result->SetPixel(j, i, Color::FromArgb(c, c, c));
		}
	}
	return result;
}

Bitmap^ HighPassSpect(Bitmap^ pic) {
	Matrix mat = ToGrayscaleMat(pic);
	mat = FourierPadding(mat);
	mat = FourierPanning(mat);
	//mat = cmat2Mat(iFFT(FFT(mat2Cmat(mat))), true);
	vector<vector<complex<NumType>>> cmat = FFT(mat2Cmat(mat));
	h(cmat, mat.shape_[0] / 10);
	//cmat = iFFT(cmat);
	mat = cmat2Mat(cmat, true);

	// deal mat

	Bitmap^ result = gcnew Bitmap(mat.shape_[0], mat.shape_[1]);
	for (int i = 0; i < mat.shape_[0]; ++i) {
		for (int j = 0; j < mat.shape_[1]; ++j) {
			float c = mat.data_[i*mat.shape_[1] + j];
			result->SetPixel(j, i, Color::FromArgb(c, c, c));
		}
	}
	return result;
}

Bitmap^ HighPassFilter(Bitmap^ pic) {
	Matrix mat = ToGrayscaleMat(pic);
	mat = FourierPadding(mat);
	mat = FourierPanning(mat);
	//mat = cmat2Mat(iFFT(FFT(mat2Cmat(mat))), true);
	vector<vector<complex<NumType>>> cmat = FFT(mat2Cmat(mat));
	h(cmat, mat.shape_[0] / 10);
	cmat = iFFT(cmat);
	mat = cmat2Mat(cmat, true);

	// deal mat

	Bitmap^ result = gcnew Bitmap(mat.shape_[0], mat.shape_[1]);
	for (int i = 0; i < mat.shape_[0]; ++i) {
		for (int j = 0; j < mat.shape_[1]; ++j) {
			float c = mat.data_[i*mat.shape_[1] + j];
			result->SetPixel(j, i, Color::FromArgb(c, c, c));
		}
	}
	return result;
}

void getBuffer(Bitmap^ pic, vector<vector<complex<NumType>>>&buf) {
	Matrix mat = ToGrayscaleMat(pic);
	mat = FourierPadding(mat);
	mat = FourierPanning(mat);
	buf = mat2Cmat(mat);
}

Bitmap^ bufToPic(vector<vector<complex<NumType>>> buf) {
	Matrix mat = cmat2Mat(buf, true);
	Bitmap^ result = gcnew Bitmap(mat.shape_[0], mat.shape_[1]);
	for (int i = 0; i < mat.shape_[0]; ++i) {
		for (int j = 0; j < mat.shape_[1]; ++j) {
			float c = mat.data_[i*mat.shape_[1] + j];
			result->SetPixel(j, i, Color::FromArgb(c, c, c));
		}
	}
	return result;
}

void bufFFT(vector<vector<complex<NumType>>>& buf) {
	buf = FFT(buf);
}
void bufIFFT(vector<vector<complex<NumType>>>& buf) {
	buf = iFFT(buf);
}
void bufH(vector<vector<complex<NumType>>>& buf) {
	h(buf, buf.size() / 4);
}
void bufL(vector<vector<complex<NumType>>>& buf) {
	l(buf, buf.size() / 8);
}