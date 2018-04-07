#pragma once
#include <map>
#include <string>
#include <vector>
#include "Vector.h"
#include "Matrix.h"
using std::map;
using std::string;
using std::vector;
using System::String;
using System::Windows::Forms::ListViewItem;

const vector<string> CMDS = {"Dot"};

struct Var {
	string type;
	void* data;
};

extern map<string, Var> vars;
extern int vCounter, mCounter;

void loadVars(string path);

string dealFormula(string f);

