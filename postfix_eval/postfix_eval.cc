#include "stack.h"
#include <string>
#include <iostream>
#include <sstream>
#include <cmath>

using namespace std;
int main(void) {
	Stack<double> postfix; 
	string equation, input;
	while (getline(cin, input)) {
		if (input.size() == 0) {
			cout << "Bye!" << endl;
			break;
		}
		istringstream str(input);
		double solution = 0;
		bool valid = true;
		while (str) {
			string buf;
			//double num;
			str >> buf;
			if (buf == "+") {
				//cout << postfix.Size() << endl;
				solution = postfix.Top();
				postfix.Pop();
				solution = postfix.Top() + solution;
				postfix.Pop();
				//cout << " R" << endl;
				postfix.Push(solution);
			}
			else if (buf == "-") {
				solution = postfix.Top();
				postfix.Pop();
				solution = postfix.Top() - solution;
				postfix.Pop();
				postfix.Push(solution);
			}
			else if (buf == "*") {
				solution = postfix.Top();
				postfix.Pop();
				solution = postfix.Top() * solution;
				postfix.Pop();
				postfix.Push(solution);
			}
			else if (buf == "/") {
				solution = postfix.Top();
				postfix.Pop();
				solution = postfix.Top() / solution;
				postfix.Pop();
				postfix.Push(solution);
			}
			else {
				//cout << buf << endl;
				try {
					postfix.Push(stod(buf));
				} catch (exception &e) {
					// dw
					if (buf != "") {
						cerr << "Error: unknown symbol '" << buf << "'" << endl;
						valid = false;
						break;
				}
			
				}
			}
		}

		if (postfix.Size() != 1 && valid) {
			cerr << "Error: invalid expression" << endl;
			while (!postfix.isEmpty()) {
				postfix.Pop();
			}
		}
		else if (valid) {
			cout << solution << endl;
			postfix.Pop();
		}

	}
}
