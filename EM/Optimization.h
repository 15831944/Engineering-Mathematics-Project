#pragma once

#include "Equation.h"

const int MAX_ITER = 10000,WAYS = 5;
const NumType OptDlt = 1e-6, GoldenRatio = 0.61803398875f;

Vector getGradient(const Equation&, const Vector&);
Matrix getHessian(const Equation&, const Vector&);
Vector goldenSectionSearch(const Equation&, const Vector&, const Vector&, int );

NumType goldenSectionSearch(const Equation&, const Vector&, const Vector&, Vector , Vector,NumType,NumType);

void optimize(const Equation&, Vector&, Vector&, Vector&,  const string&,string&);
