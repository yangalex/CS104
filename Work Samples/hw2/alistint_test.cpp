#include "alistint.h"
#include <iostream>

using namespace std;

int main() {
	// Initialize with 5
	AListInt* list = new AListInt(3);

	// Check if empty
	if(list->empty()) {
		cout << "SUCCESS: list is empty when initialized" << endl;
	}
	else {
		cout << "FAIL: list has size " << list->size() << " when initialized" << endl;
	}

// ----------------------------------------------------------------------

	// Insert at 0
	list->insert(0, 3);

	// Check size
	if(list->size() == 1) {
		cout << "SUCCESS: list has size 1 after one insertion" << endl;
	}
	else {
		cout << "FAIL: list has size " << list->size() << " after one insertion" << endl;
	}

	// Check value
	if(list->get(0) == 3) {
		cout << "SUCCESS: 3 is at the 0th index of the list" << endl;
	}
	else {
	 	cout << "FAIL: 3 is not at the 0th index of the list, ";
	 	cout << list->get(0) << " is instead" << endl;
	}

// ---------------------------------------------------------------------

	// Insert at 1
	list->insert(1, 5);

	// Check size
	if(list->size() == 2) {
		cout << "SUCCESS: list has size 2 after two insertions" << endl;
	}
	else {
		cout << "FAIL: list has size " << list->size() << " after two insertions" << endl;
	}

	// Check value
	if(list->get(1) == 5) {
		cout << "SUCCESS: 5 is at the 1th index of the list" << endl;
	}
	else {
	 	cout << "FAIL: 5 is not at the 1th index of the list, ";
	 	cout << list->get(1) << " is instead" << endl;
	}

// --------------------------------------------------------------------

	// Insert at 1 (middle)
	list->insert(1, 8);

	// Check size
	if(list->size() == 3) {
		cout << "SUCCESS: list has size 3 after three insertions" << endl;
	}
	else {
		cout << "FAIL: list has size " << list->size() << " after three insertions" << endl;
	}

	// Check value
	if(list->get(1) == 8) {
		cout << "SUCCESS: 8 is at the 1th index of the list" << endl;
	}
	else {
	 	cout << "FAIL: 8 is not at the 1th index of the list, ";
	 	cout << list->get(1) << " is instead" << endl;
	}
	// Check value of 2th index
	if(list->get(2) == 5) {
		cout << "SUCCESS: 5 is at the 2th index of the list" << endl;
	}
	else {
		cout << "FAIL: 5 is not at the 2th index of the list, ";
		cout << list->get(2) << " is instead" << endl;
	}

// -----------------------------------------------------------------------

	// Insert when list is full (test resizing)
	list->insert(0, 9);

	// Check capacity
	if(list->capacity() == 6) {
		cout << "SUCCESS: list has capacity 6 after resizing" << endl;
	}
	else {
		cout << "FAIL: list has capacity " << list->capacity() << " after resizing" << endl;
	}
	

	// Check size
	if(list->size() == 4) {
		cout << "SUCCESS: list has size 4 after four insertions" << endl;
	}
	else {
		cout << "FAIL: list has size " << list->size() << " after four insertions" << endl;
	}

	// Check value
	if(list->get(0) == 9) {
		cout << "SUCCESS: 9 is at the 0th index of the list" << endl;
	}
	else {
	 	cout << "FAIL: 9 is not at the 0th index of the list, ";
	 	cout << list->get(0) << " is instead" << endl;
	}

// --------------------------------------------------------------------------

  // Remove from middle of list
  list->remove(2);

  // Check size of list
  if(list->size() == 3) {
  	cout << "SUCCESS: list has size 3 after one removal" << endl;
  }
  else {
  	cout << "FAIL: list has size " << list->size() << " after one removal" << endl;
  }

  // Check the new value of 2th index
  if(list->get(2) == 5) {
  	cout << "SUCCESS: 5 is at 2th index of the list" << endl;
  }
  else {
  	cout << "FAIL: 5 is not at 2th index of the list, " << list->get(2);
  	cout << " is instead" << endl;
  }

// --------------------------------------------------------------------------

  // Remove from back of list
  list->remove(2);

  // Check size of list
  if(list->size() == 2) {
  	cout << "SUCCESS: list has size 2 after two removals" << endl;
  }
  else {
  	cout << "FAIL: list has size " << list->size() << " after two removals" << endl;
  }

  // Check the value of 1th index
  if(list->get(1) == 3) {
  	cout << "SUCCESS: 3 is at 1th index of the list" << endl;
  }
  else {
  	cout << "FAIL: 3 is not at 1th index of the list, " << list->get(1);
  	cout << " is instead" << endl;
  }

// ------------------------------------------------------------------------

  // Remove from front of list
  list->remove(0);

  // Check size of list
  if(list->size() == 1) {
  	cout << "SUCCESS: list has size 1 after three removals" << endl;
  }
  else {
  	cout << "FAIL: list has size " << list->size() << " after three removals" << endl;
  }

  // Check the new value of 1th index
  if(list->get(0) == 3) {
  	cout << "SUCCESS: 3 is at 0th index of the list" << endl;
  }
  else {
  	cout << "FAIL: 3 is not at 0th index of the list, " << list->get(0);
  	cout << " is instead" << endl;
  }

// ------------------------------------------------------------------------
    // Remove last item
  list->remove(0);

  // Check size of list
  if(list->empty()) {
  	cout << "SUCCESS: list is empty after removing all items" << endl;
  }
  else {
  	cout << "FAIL: list has size " << list->size() << endl;
  }

 // -----------------------------------------------------------------------
	
	return 0;
}