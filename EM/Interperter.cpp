#include "Interpreter.h"

#include <fstream>
#include <algorithm>
using std::ifstream;

map<string, Var> vars;
int vCounter = 0, mCounter = 0;

int getPiority(char op) {
	switch (op)
	{
	case '+':
		return 1;
	case '-':
		return 1;
	case '*':
		return 2;
	case '|':
		return 3;
	default:
		return -1;
	}
}


void loadVars(string path) {
	ifstream fin(path);
	int total;
	char type;
	fin >> total;
	string name;
	for (int i = 0; i < total; ++i) {
		fin >> type;
		Var var;
		int size;
		switch (type){
		case 'V':
			int dim;
			fin >> dim;
			var.type = "Vector";
			var.data = new Vector(dim);
			// var name
			name = "$v"+ std::to_string(vCounter++);
			// input
			for (int j = 0; j < dim; j++)
				fin >> ((Vector*)var.data)->data_[j];
			// add to map
			vars[name] = var;
			break;
		case 'M':
			int shape[2];
			fin >> shape[0] >> shape[1];
			var.type = "Matrix";
			var.data = new Matrix(shape[0], shape[1]);
			name = "$m" + std::to_string(mCounter++);
			size = shape[0] * shape[1];
			for (int j = 0; j < size; ++j)
				fin >> ((Matrix*)var.data)->data_[j];
			vars[name] = var;
			break;
		default:
			break;
		}
	}
	fin.close();
}

string dealFormula(string f) {
	for (int i = 0; i < OpCMD.size(); ++i) {
		std::size_t find = f.find(OpCMD[i] + "(");
		while (find != string::npos) {
			f.replace(find, OpCMD[i].length(), OpCMD[i] + '|');
			find = f.find(OpCMD[i] + "(");
		}
	}
	return f;
}

int checkFormula(string f) {
	int status = NoError;
	// check if variable exist

	// check OpCMD have ()

	// check () is all right 

	return NoError;
}

string rmUseless(string f) {
	
	for (int i = 0; i < useless.size(); ++i)
	{
		// you need include <algorithm> to use general algorithms like std::remove()
		f.erase(std::remove(f.begin(), f.end(), useless[i]), f.end());
	}
	return f;
}

string trimUseless(string f) {

	bool flag = true;
	for (int i = 0; i < f.size() && flag; ++i)
	{
		flag = false;
		for (int j = 0; j < useless.size(); ++j) {
			if (f[i] == useless[j]) {
				flag = true;
				f[i] = '@';
			}
		}
	}
	flag = true;
	for (int i = f.size()-1; i >= 0 && flag; --i)
	{
		flag = false;
		for (int j = 0; j < useless.size(); ++j) {
			if (f[i] == useless[j]) {
				flag = true;
				f[i] = '@';
			}
		}
	}
	f.erase(std::remove(f.begin(), f.end(), '@'), f.end());
	return f;
}

Var getVal(string f) {
	// is var
	for (auto it = vars.begin(); it != vars.end(); ++it) {
		if (it->first == f)
			return it->second;
	}

	// is const
	
	// is value

	return Var{ "Num",new NumType(atof(f.c_str())) };

}

Var regularCale(Var a, Var b, char op) {
	Var result;
	switch (op)
	{
	case '+':
		break;
	// etc
	default:
		break;
	}
	return result;
}

Var funcCale(string cmd, string argument) {
	vector<Var> args;
	cmd = rmUseless(cmd);
	argument = trimUseless(argument);
	// deal right side
	
	size_t commaPosi = argument.find(","), lastPosi = 0;

	while(commaPosi != string::npos){
		args.push_back(ExecFormula(argument.substr(lastPosi, commaPosi)));
		lastPosi = commaPosi + 1;
		commaPosi = argument.find(",",lastPosi);
	}


	// cale
	if (cmd == "Dot") {
		// dot it
	}
	return Var{ "Error",new string("CMD is wrong") };
}


Var ExecFormula(string f) {
	int is_error = checkFormula(f);
	if (is_error != NoError)
		return Var{ "Error", new int(is_error) };
	f = dealFormula(f);
	int baseVal = 0, opCount = 0, minLoc = -1, minVal = INF, pio;

	for (int i = 0; i<f.length(); ++i) {
		if (f[i] == '(') {
			baseVal += 6;
		}
		else if (f[i] == ')') {
			baseVal -= 6;
		}
		else {
			pio = getPiority(f[i]);
			if (pio != -1) {
				++opCount;
				if (pio + baseVal <= minVal) {
					minLoc = i;
					minVal = pio + baseVal;
				}
			}
		}
	}
	if (!opCount) {
		return getVal(f);
	}
	else {
		if (f[minLoc] != '|') {
			return regularCale(ExecFormula(f.substr(0, minLoc)), ExecFormula(f.substr(minLoc + 1, f.length() - minLoc)),f[minLoc]);
		}
		else {
			return funcCale(f.substr(0, minLoc),f.substr(minLoc + 1, f.length() - minLoc));
		}
	}
}
