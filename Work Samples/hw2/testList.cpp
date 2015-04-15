#include "llistdbl.h"
#include <iostream>

using namespace std;

int main() {
	LListDbl* list = new LListDbl();

  // Check if the list is initially empty.
  if (list->empty()) {
    cout << "SUCCESS: List is empty initially." << endl;
  } else {
    cout << "FAIL: List is not empty initially when it should be." << endl;
  }	

  // Insert item at head
  list->insert(0, 2.5);

  // Check size of list
  if(list->size() == 1) {
  	cout << "SUCCESS: list has size 1 after one insertion" << endl;
  }
  else {
  	cout << "FAIL: list has size " << list->size() << " after one insertion" << endl; 
  }

  // Check if value is correct
  if(list->get(0) == 2.5) {
  	cout << "SUCCESS: 2.5 is at the 0th index of the list" << endl;
  }
  else {
  	cout << "FAIL: 2.5. is not at the 0th index of the list" << endl;
  }

 // -----------------------------------------------------------------------

  // Insert item at tail
  list->insert(1, 5.3);

  // Check size of list
  if(list->size() == 2) {
  	cout << "SUCCESS: list has size 2 after two insertions" << endl;
  }
  else {
  	cout << "FAIL: list has size " << list->size() << " after two insertions" << endl; 
  }

  // Check value of tail
  if(list->get(1) == 5.3) {
  	cout << "SUCCESS: 5.3 is at the 1th index of the list" << endl;
  }
  else {
  	cout << "FAIL: 5.3 is not at the 1th index of the list" << endl;
  }

// ------------------------------------------------------------------------

  // Insert at middle of list
  list->insert(1, 3.6);

  // Check size of list
  if(list->size() == 3) {
  	cout << "SUCCESS: list has size 3 after three insertions" << endl;
  }
  else {
  	cout << "FAIL: list has size " << list->size() << " after three insertions" << endl; 
  }

  // Check value of middle and tail if correct
  if(list->get(1) == 3.6) {
  	cout << "SUCCESS: 3.6 is at the 1th index of the list" << endl;
  }
  else {
  	cout << "FAIL: 3.6 is not at the 1th index of the list" << endl;
  }

  // Check value of tail
  if(list->get(2) == 5.3) {
  	cout << "SUCCESS: 5.3 is still tail after inserting 3.6" << endl;
  }
  else {
  	cout << "FAIL: 5.3 is not tail after inserting 3.6" << endl;
  }

// ----------------------------------------------------------------------

  // Remove from middle of list
  list->remove(1);

  // Check size of list
  if(list->size() == 2) {
  	cout << "SUCCESS: list has size 2 after one removal" << endl;
  }
  else {
  	cout << "FAIL: list has size " << list->size() << " after one removal" << endl;
  }

  // Check the new value of 1th index
  if(list->get(1) == 5.3) {
  	cout << "SUCCESS: 5.3 is at 1th index of the list" << endl;
  }
  else {
  	cout << "FAIL: 5.3 is not at 1th index of the list, " << list->get(1);
  	cout << " is instead" << endl;
  }

// ----------------------------------------------------------------------

  // Remove from tail
  list->remove(1);

  // Check size of list
  if(list->size() == 1) {
  	cout << "SUCCESS: list has size 1 after two removals" << endl;
  }
  else {
  	cout << "FAIL: list has size " << list->size() << " after two removals" << endl;
  }

  // Check value of only item left
  if(list->get(0) == 2.5) {
  	cout << "SUCCESS: only value left is 2.5" << endl;
  }
  else {
  	cout << "FAIL: only value left is not 2.5" << endl;
  }

// ----------------------------------------------------------------------

  // Remove from head and when only one item left
  list->remove(0);

  if(list->empty()) {
  	cout << "SUCCESS: list is empty" << endl;
  }
  else {
  	cout << "FAIL: list has size " << list->size() << endl;
  }

// -----------------------------------------------------------------------


  // Clean up memory
  delete list;

	return 0;
}