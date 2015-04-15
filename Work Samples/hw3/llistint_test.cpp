#include "llistint.h"
#include <iostream>

using namespace std;

int main() {
	LListInt* list = new LListInt();

	// Check if list is initially empty
	if(list->empty()) {
		cout << "SUCCESS: List is empty initially." << endl;
	}
	else {
		cout << "FAIL: List is not empty initially when it should be." << endl;
	}

	// ----------------------------------------------------------------
	// Push back item
	list->push_back(5);

	// Check size of list
	if(list->size() == 1) {
		cout << "SUCCESS: list has size 1 after one insertion" << endl;
	}
	else {
		cout << "FAIL: list has size " << list->size() << " after one insertion" << endl; 
	}

	// Check if value is correct
	if(list->get(0) == 5) {
		cout << "SUCCESS: 5 is at the 0th index of the list" << endl;
	}
	else {
		cout << "FAIL: 5 is not at the 0th index of the list" << endl;
	}

	//------------------------------------------------------------

	// Push back item
	list->push_back(3);

	// Check size of list
	if(list->size() == 2) {
		cout << "SUCCESS: list has size 2 after two insertion" << endl;
	}
	else {
		cout << "FAIL: list has size " << list->size() << " after two insertion" << endl; 
	}

	// Check if value is correct
	if(list->get(1) == 3) {
		cout << "SUCCESS: 3 is at the 1th index of the list" << endl;
	}
	else {
		cout << "FAIL: 3 is not at the 1th index of the list" << endl;
	}

	//------------------------------------------------------------

	// Push back item
	list->push_back(8);

	// Check size of list
	if(list->size() == 3) {
		cout << "SUCCESS: list has size 3 after three insertion" << endl;
	}
	else {
		cout << "FAIL: list has size " << list->size() << " after three insertion" << endl; 
	}

	// Check if value is correct
	if(list->get(2) == 8) {
		cout << "SUCCESS: 8 is at the 2th index of the list" << endl;
	}
	else {
		cout << "FAIL: 8 is not at the 2th index of the list" << endl;
	}

	// ------------------------------------------------------------

	// copy list
	LListInt list2(*list);

	cout << "After copy constructor: " << endl;
	// Print out values of each list
	cout << "List 1 has elements: ";
	for(int i = 0; i < list->size(); i++) {
		cout << list->get(i) << " ";
	}
	cout << endl;
	cout << "List 2 has elements: ";
	for(int i = 0; i < list2.size(); i++) {
		cout << list2.get(i) << " ";
	}
	cout << endl;

	// ----------------------------------------------------------
	
	// push items to list2
	list2.push_back(9);
	list2.push_back(7);
	list2.push_back(1);
	list2.push_back(4);

	// assign list2 to list
	(*list) = list2;

	// Print out values of each list again
	cout << "After assignment operator: " << endl;
	cout << "List 1 has elements: ";
	for(int i = 0; i < list->size(); i++) {
		cout << list->get(i) << " ";
	}
	cout << endl;
	cout << "List 2 has elements: ";
	for(int i = 0; i < list2.size(); i++) {
		cout << list2.get(i) << " ";
	}

	cout << endl;

	list->clear();
	list2.clear();
	delete list;

	return 0;
}
