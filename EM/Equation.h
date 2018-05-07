#pragma once

#include <string>
#include <vector>
#include <fstream>
#include "Matrix.h"


using std::string;
using std::vector;

/*
only two variables x y
*/

struct Nomial
{
	NumType powX;
	NumType powY;
	NumType coef;
};

class Equation
{
private:
	vector<Nomial> polynomial_;
	int dim_;

public:
	Equation(string);
	int getDim();
	static NumType calcEquation(Equation, Vector);
	Equation PartialDerivative(char respectTo);

	Equation operator=(const Equation& rhs);
	Equation operator=(const string& rhs);

};

extern vector<Equation> equations;

vector<string> loadEquations(string);


