#include "Interpreter.h"

#include <fstream>
using std::ifstream;

map<string, Var> vars;
int vCounter = 0, mCounter = 0;



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

Var ExecFormula(string f) {

}
