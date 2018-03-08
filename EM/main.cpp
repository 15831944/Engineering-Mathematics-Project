#include <iostream>
#include "Vector.h"

using namespace std;

int main() {

	Vector test = { 1.0,2.0,3.0 };
	Vector r = test;
	cout << (test + r).ToString() << endl;
	getchar();
	return 0;
}