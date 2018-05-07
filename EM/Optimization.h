#pragma once

#include "Equation.h"

Vector getGradient(Equation,Vector); // To determine what equation should partial derivative be store

Vector getDirection(Equation,Vector,string);

