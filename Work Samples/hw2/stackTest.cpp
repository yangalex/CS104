#include "stackdbl.h"
#include <iostream>

using namespace std;

int main() {
	
	StackDbl stack;

	if(stack.empty()) {
		cout << "SUCCESS: stack is empty when initialized" << endl;
	}
	else {
		cout << "FAIL: stack is not empty when initialized" << endl;
	}

	stack.push(3.5);

	if(stack.top() == 3.5) {
		cout << "SUCCESS: 3.5 is at the top of the stack" << endl;
	}
	else {
		cout << "FAIL: 3.5 is not at the top of the stack" << endl;
	}

	stack.push(7.6);

	if(stack.top() == 7.6) {
		cout << "SUCCESS: 7.6 is at the top of the stack" << endl;
	}
	else {
		cout << "FAIL: 7.6 is not at the top of the stack" << endl;
	}

	stack.push(2.1);

	if(stack.top() == 2.1) {
		cout << "SUCCESS: 2.1 is at the top of the stack" << endl;
	}
	else {
		cout << "FAIL: 2.1 is not at the top of the stack" << endl;
	}

	stack.pop();
	if(stack.top() == 7.6) {
		cout << "SUCCESS: 7.6 is at the top of the stack after pop" << endl;
	}
	else {
		cout << "FAIL: 7.6 is not at the top of the stack after pop" << endl;
	}

	stack.pop();
	if(stack.top() == 3.5) {
		cout << "SUCCESS: 3.5 is at the top of the stack after pop" << endl;
	}
	else {
		cout << "FAIL: 3.5 is not at the top of the stack after pop" << endl;
	}

	stack.pop();

	if(stack.empty()) {
		cout << "SUCCESS: stack is empty again" << endl;
	}
	else {
		cout << "FAIL: stack is not empty" << endl;
	}



	return 0;
}
