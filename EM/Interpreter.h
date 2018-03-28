#pragma once
#include <map>
#include <string>
#include "Vector.h"
#include "Matrix.h"
using std::map;
using std::string;
using System::Array;
using System::String;
using System::Windows::Forms::ListViewItem;

struct Var {
	string type;
	void* data;
};

extern map<string, Var> vars;
extern int vCounter, mCounter;

void loadVars(string path);

