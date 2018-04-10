#include "Interpreter.h"

#include <fstream>
#include <algorithm>
using std::ifstream;

map<string, Var> vars;
int vCounter = 0, mCounter = 0;

string convShitTostring(String^ s) {
	const char* chars = (const char*)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(s)).ToPointer();
	string dest = chars;
	return dest;
}

int getPiority(char op) {
	switch (op)
	{
	case '=':
		return 1;
	case '+':
		return 2;
	case '-':
		return 3;
	case '*':
		return 4;
	case '|':
		return 5;
	default:
		return -1;
	}
}

String^ getResultStr(String^ s) {
	string f = convShitTostring(s);
	Var result = ExecFormula(dealFormula(f));
	if (result.type == "Vector")
		return gcnew String(((Vector *)result.data)->ToString().c_str())+"\n";
	else if (result.type == "Matrix") {
		//other situation

		return gcnew String(((Matrix *)result.data)->ToString().c_str()) + "\n";
		
	}

	// error
	return gcnew String(((string *)result.data)->c_str());
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

	// check OpCMD is follow by (


	// check () is all right 

	return NoError;
}

string rmUseless(string f) {
	
	for (int i = 0; i < useless.size(); ++i)
	{
		
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

	f = rmUseless(f);
	// is var
	for (auto it = vars.begin(); it != vars.end(); ++it) {
		if (it->first == f)
			return it->second;
	}
	
	// is value

	return Var{ "Num",new NumType(atof(f.c_str())) };

}

Var regularCale(Var a, Var b, char op) {
	Var result;
	switch (op)
	{
	case '+':
		if (a.type != b.type)
			break;
		if (a.type == "Vector") {
			result.data = new Vector();
			result.type = "Vector";
			try {
				*((Vector*)result.data) = *((Vector*)a.data) + *((Vector*)b.data);
			}
			catch (const string e) {
				delete result.data;
				result.type = "Error";
				result.data = new string(e);
			}
			
		}
		else if (a.type == "Matrix") {
			result.data = new Matrix();
			result.type = "Matrix";
			try {
				*((Matrix*)result.data) = *((Matrix*)a.data) + *((Matrix*)b.data);
			}
			catch (const string e) {
				delete result.data;
				result.type = "Error";
				result.data = new string(e);
			}
		}
		break;
	case '-':
		if (a.type != b.type)
			break;
		if (a.type == "Vector") {
			result.data = new Vector();
			result.type = "Vector";
			try {
				*((Vector*)result.data) = *((Vector*)a.data) - *((Vector*)b.data);
			}
			catch (const string e) {
				delete result.data;
				result.type = "Error";
				result.data = new string(e);
			}

		}
		else if (a.type == "Matrix") {
			result.data = new Matrix();
			result.type = "Matrix";
			try {
				*((Matrix*)result.data) = *((Matrix*)a.data) - *((Matrix*)b.data);
			}
			catch (const string e) {
				delete result.data;
				result.type = "Error";
				result.data = new string(e);
			}
		}
		break;
	case '*':
		if (a.type != b.type)
			break;
		if (a.type == "Vector") {
			result.type = "Error";
			result.data = new string("Vector don't have * try use cross or dot");
		}
		else if (a.type == "Matrix") {
			result.data = new Matrix();
			result.type = "Matrix";
			try {
				*((Matrix*)result.data) = *((Matrix*)a.data) * *((Matrix*)b.data);
			}
			catch (const string e) {
				delete result.data;
				result.type = "Error";
				result.data = new string(e);
			}
		}
		break;
	// etc
	default:
		result.type = "Error";
		result.data = new string("operator is not define");
		break;
	}
	return result;
}

Var funcCale(string cmd, string argument) {
	vector<Var> args;
	cmd = rmUseless(cmd);
	argument = trimUseless(argument);
	// deal right side
	Var result;
	size_t commaPosi = argument.find(","), lastPosi = 0;

	while(commaPosi != string::npos){
		args.push_back(ExecFormula(argument.substr(lastPosi, commaPosi)));
		lastPosi = commaPosi + 1;
		commaPosi = argument.find(",",lastPosi);
	}


	// cale
	if (cmd == "Dot") {
		// check arguments
		if (args.size() != 2 || args[0].type != "Vector" || args[1].type != "Vector")
			return Var{ "Error",new string("Dot fail") };
		// dot it
		result.type = "Vector";
		result.data = new Vector();
		*((Vector *)result.data) = *((Vector *)args[0].data) + *((Vector *)args[1].data);
		return result;
	}
	else if (cmd == "") {

	}
	return Var{ "Error",new string("CMD is wrong") };
}


Var ExecFormula(string f) {
	int is_error = checkFormula(f);
	if (is_error != NoError)
		return Var{ "Error", new int(is_error) };
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
		if (f[minLoc] == '|') {
			return funcCale(f.substr(0, minLoc), f.substr(minLoc + 1, f.length() - minLoc));
		}
		else if (f[minLoc] == '=') {
			Var result = ExecFormula(f.substr(minLoc + 1, f.length() - minLoc));
			
			// set value to var map

			vars[rmUseless(f.substr(0, minLoc))] = result;
			

			return result;

			
		}
		else {
			return regularCale(ExecFormula(f.substr(0, minLoc)), ExecFormula(f.substr(minLoc + 1, f.length() - minLoc)), f[minLoc]);
			
		}
	}
}
