#pragma once
#include "Matrix.h"
#include <vector>
#include <complex>
using namespace System::Drawing;
using std::vector;
using std::complex;

Bitmap^ ToGrayscale(Bitmap^);
Matrix ToGrayscaleMat(Bitmap^);
Matrix FourierPanning(Matrix);
Matrix FourierPadding(Matrix);
Matrix FastFourierTransform(Matrix);
Matrix DiscreteFourierTransform(Matrix);
Matrix InvDiscreteFourierTransform(Matrix);

Bitmap^ FastFourierTransform(Bitmap^);
Bitmap^ InvFastFourierTransform(Bitmap^);
Bitmap^ LowPassSpect(Bitmap^);
Bitmap^ LowPassFilter(Bitmap^);
Bitmap^ HighPassSpect(Bitmap^);
Bitmap^ HighPassFilter(Bitmap^);
Bitmap^ DiscreteFourierTransform(Bitmap^);
Bitmap^ InvDiscreteFourierTransform(Bitmap^);

void getBuffer(Bitmap^ pic, vector<vector<complex<NumType>>>&buf);

Bitmap^ bufToPic(vector<vector<complex<NumType>>> buf);

void bufFFT(vector<vector<complex<NumType>>>&);
void bufIFFT(vector<vector<complex<NumType>>>&);
void bufH(vector<vector<complex<NumType>>>&);
void bufL(vector<vector<complex<NumType>>>&);

Bitmap^ Test(Bitmap^ pic);
