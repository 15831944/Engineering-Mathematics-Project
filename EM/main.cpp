#include <iostream>
#include "Vector.h"

using namespace std;

int main() {

	Vector test({ 1.0,2.0,3.0 });
	cout << test.ToString() << endl;

	getchar();
	return 0;
}