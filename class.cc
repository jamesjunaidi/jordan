#include <iostream>
#include <vector>

using namespace std;

class Example {
 public:
 	// These are the fields
	int field1;
	int field2;
	int field3;

	// this is the constructor for the class
	Example(int a, int b, int c) {
		field1 = a;
		field2 = b;
		field3 = c;
	}

	// this function prints out the fields
	void printClass() {
		cout << "Field1: " << field1 << endl;
		cout << "Field2: " << field2 << endl;
		cout << "Field3: " << field3 << endl;
	}
};


int main(void) {
	// this is a vector of classes
	vector<Example> v;

	// here pushing 19 items into the vector
	for (unsigned int i = 0; i < 20; ++i) {
		Example *a = new Example(i,i,i);
		v.push_back(*a);
	}

	int count = 1;
	// printing out the contents of each class
	for (Example &a : v) {
		cout << "Class # " << count++ << endl;
		a.printClass();
		cout << endl;
	}

	return 0;
}