#include <iostream>
#include "Matrix.h"

using namespace std;

int main() {

	Matrix test(3, 3,
	{
		-1,3,2,
		0,-2,1,
		1, 0,-2
	}
	);
	cout << test.Inv().ToString();
	getchar();
	return 0;
}