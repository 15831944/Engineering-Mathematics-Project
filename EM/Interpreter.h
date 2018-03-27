#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <map>
using System::String;
using System::Windows::Forms::ListViewItem;
using std::vector;
using std::string;
using std::ifstream;
using std::map;

struct VAR {
	bool type; // 0 = vector 1 = matrix
	void* data;
};

class Interpreter {
public:
	static map<string, VAR> vars;
	vector<ListViewItem^> LoadVars(string path);
};