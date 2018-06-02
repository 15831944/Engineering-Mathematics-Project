#pragma once

#include "Equation.h"

const int MAX_ITER = 10000;
const NumType OptDlt = 1e-6, GoldenRatio = 0.61803398875f,NumDlt = 1e-6,BIGNUM=1e9;

extern bool newtonStepping;

Vector getGradient(const Equation&, const Vector&, bool);
Matrix getHessian(const Equation&, const Vector&, bool);

Vector DeriGetGradient(const Equation&, const Vector&);
Matrix DeriGetHessian(const Equation&, const Vector&);

Vector goldenSectionSearch(const Equation&, const Vector&, const Vector&, int );

NumType goldenSectionSearch(const Equation&, const Vector&, const Vector&, Vector , Vector,NumType,NumType);

void optimize(const Equation&, Vector&, Vector&, Vector&,  const string&,string&, bool ,int);

Vector numericalGetGradient(const Equation&, const Vector&);
Matrix numericalGetHessian(const Equation&, const Vector&);

Vector calcBound(const Vector&, const Vector&, Vector , Vector );