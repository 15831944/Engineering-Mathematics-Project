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

enum ERRORS{NoError,Syntax,Math};

const vector<string> OpCMD = {"Dot","Pow"};

const vector<string> CMDs = {};

const char OP[] = {'+','-'};

struct Var {
	string type;
	void* data;
};

extern map<string, Var> vars;
extern int vCounter, mCounter;

void loadVars(string path);

string dealFormula(string f);

int checkFormula(string f);

Var ExecFormula(string f);
