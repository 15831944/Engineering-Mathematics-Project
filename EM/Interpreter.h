#pragma once
#include <map>
#include <fstream>
#include <string>
#include <vector>
#include "Vector.h"
#include "Matrix.h"
using std::map;
using std::string;
using std::vector;
using System::String;
using System::Windows::Forms::ListViewItem;

enum ERRORS { NoError, Syntax, Math };

const vector<string> OpCMD = {"Dot","Norm","Normli","Cross","Compo","Proj","Tri","Paral","Ortho","Angle","PlaneNorm","Indepen","GramS",
							  "Rank","Trans","Solve","Det","Inv","Adj","Eigen","LeastS"};

const vector<string> CMDs = {};

const vector<char> useless = { '(',')',' ' };

const char OP[] = {'=','+','-','*','|'};
const int INF = 0x7fffffff;

struct Var {
	string type;
	void* data;
};

Vector* ToVector(void* p);
Matrix* ToMatrix(void* p);

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

String^ getResultStr(String^ s);

void clearMap();
