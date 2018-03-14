#include <iostream>
#include "Matrix.h"

using namespace std;

int main() {

	Matrix test(3, 3,
	{ 1,2,3,
	  4,5,6,
	  7,8,9 });
	cout << test.Cofactor(2, 2).ToString();
	getchar();
	return 0;
}