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

const vector<char> useless = { '(',')',' ' };

const char OP[] = {'=','+','-','*','|'};
const int INF = 0x7fffffff;

struct Var {
	string type;
	void* data;
};

extern map<string, Var> vars;
extern int vCounter, mCounter;

inline int getPiority(char op);

void loadVars(string path);

string dealFormula(string f);

int checkFormula(string f);

string rmUseless(string f);
string trimUseless(string f);

Var getVal(string f);

Var regularCale(Var a, Var b, char op);

Var funcCale(string cmd, string argument);

Var ExecFormula(string f);

