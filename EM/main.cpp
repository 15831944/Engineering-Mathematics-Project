#include <iostream>
#include "Matrix.h"

using namespace std;

int main() {

	Matrix A(8, 8, { 4,4,0,0,2,3,1,2,3,2,0,2,1,0,2,0,3,0,4,3,2,4,1,3,3,0,0,3,2,3,2,3,1,2,3,4,1,1,2,4,4,0,3,0,2,1,3,2,3,4,1,2,2,0,3,1,2,1,1,3,2,1,1,1 }); 
	cout << A.Det();
	getchar();
	return 0;
}