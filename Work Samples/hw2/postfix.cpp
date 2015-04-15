#include "stackdbl.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

double calculate(string& expr, bool& success) {
	// Stack
	StackDbl stack;

	// Stringstream
	stringstream ss(expr);

	string x;

	double result;

	while(ss >> x) {
		if(x == "+") {
			double num1;
			double num2;

			// check so we don't try to pop something that doesn't exist
			if(stack.empty()) {
				success = false;
				return -1;
			}

			num1 = stack.top();
			stack.pop();

			// Check again so we don't pop an empty stack
			if(stack.empty()) {
				success = false;
				return -1;
			}

			num2 = stack.top();
			stack.pop();

			double sum = num2 + num1;
			stack.push(sum);
		}
		else if(x == "-") {
			double num1;
			double num2;

			if(stack.empty()) {
				success = false;
				return -1;
			}

			num1 = stack.top();
			stack.pop();

			// Check again so we don't pop an empty stack
			if(stack.empty()) {
				success = false;
				return -1;
			}

			num2 = stack.top();
			stack.pop();

			double difference = num2 - num1;
			stack.push(difference);
		}
		else if(x == "*") {
			double num1;
			double num2;

			if(stack.empty()) {
				success = false;
				return -1;
			}

			num1 = stack.top();
			stack.pop();

			// Check again so we don't pop an empty stack
			if(stack.empty()) {
				success = false;
				return -1;
			}

			num2 = stack.top();
			stack.pop();

			double product = num2 * num1;
			stack.push(product);
		}
		else if(x == "/") {
			double num1;
			double num2;

			if(stack.empty()) {
				success = false;
				return -1;
			}

			num1 = stack.top();
			stack.pop();

			// Check again so we don't pop an empty stack
			if(stack.empty()) {
				success = false;
				return -1;
			}

			num2 = stack.top();
			stack.pop();

			double quotient = num2 / num1;
			stack.push(quotient);
		}
		else {
			double num;
			num = atof(x.c_str());
			stack.push(num);
		}
	}

	// Get the remaining number
	result = stack.top();
	// If stack is not empty, it means that operation failed
	stack.pop();
	if(!stack.empty()) {
		success = false;
		return -1;
	}
	else {
		success = true;
		return result;
	}

}

int main(int argc, char* argv[]) {

	// Check for necessary number of arguments
	if(argc < 3) {
		cout << "Please pass input file and output file" << endl;
		return 1;
	}

	// Open input file
	ifstream ifile(argv[1]);

	// Open output file
	ofstream ofile(argv[2]);

	// Temporary buffer for lines
	string myLine;

	while(getline(ifile, myLine)) {
		bool success = false;
		double result = calculate(myLine, success);

		if(success) {
			ofile << result << endl;
		}
		else {
			ofile << "invalid" << endl;
		}
	}

	ifile.close();
	ofile.close();

	return 0;
}