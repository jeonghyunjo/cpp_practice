#include <iostream>
#define PI 3.141592

namespace myspace {
	int add(int x, int y) {
		return x * y;
	}
}
using namespace std;

int add(int x, int y) {
	return x + y;
}

int main() {
	int x(0);
	cout << &x << endl;
	int y(100);
	int z(200);

	cout << add(y, z) << "\n" << myspace::add(y, z) << endl;
	return 0;
}