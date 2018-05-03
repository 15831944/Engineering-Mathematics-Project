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

public:
	Equation(string);
	
	static NumType calcEquation(Equation, NumType, NumType);


};

extern vector<Equation> equations;

vector<string> loadEquations(string);


