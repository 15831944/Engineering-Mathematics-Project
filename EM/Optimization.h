#pragma once

#include "Equation.h"

const int MAX_ITER = 10000,WAYS = 5;
const NumType OptDlt = 1e-6;
enum {Gradient,Powell};
const NumType StepSize[WAYS] = {0.1};

Vector getGradient(const Equation&, const Vector&);
Matrix getHessian(const Equation&, const Vector&);

void optimize(const Equation&, Vector&, const string&,string&);
