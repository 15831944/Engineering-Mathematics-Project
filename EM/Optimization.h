#pragma once

#include "Equation.h"

const int MAX_ITER = 10000;
const NumType OptDlt = 0.001;

Vector getGradient(Equation,Vector); // To determine what equation should partial derivative be store

Vector getDirection(Equation,Vector,string);

