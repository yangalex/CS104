#include "setint.h"
#include <iostream>

using namespace std;

void checkSize(const SetInt& mySet, int targetSize) 
{
	if(mySet.size() == targetSize) {
		cout << "SUCCESS: set has size " << targetSize << endl; 
	}
	else {
		cout << "FAIL: set does not have size " << targetSize << endl;
	}
}

void checkInsertedNumber(const SetInt& mySet, const int& val)
{
	if(mySet.exists(val)) {
		cout << "SUCCESS: set contains number " << val << endl;
	}
	else {
		cout << "FAIL: set does not contain " << val << endl;
	}
}

void checkRemovedNumber(const SetInt& mySet, const int& val)
{
	if(!mySet.exists(val)) {
		cout << "SUCCESS: set does not contain number " << val << endl;
	}
	else {
		cout << "FAIL: set does contain " << val << endl;
	}
}

void displaySet(const SetInt& mySet)
{
	SetInt testSet = mySet;
	cout << "Set is: ";
	const int* it;
	it = testSet.first();

	while(it != NULL) {
		cout << *it << " ";
		it = testSet.next();
	}

	cout << endl;
}

int main() {
	SetInt firstSet;

	checkSize(firstSet, 0);

	firstSet.insert(1);
	checkSize(firstSet, 1);
	checkInsertedNumber(firstSet, 1);

	firstSet.insert(2);
	checkSize(firstSet, 2);
	checkInsertedNumber(firstSet, 2);

	firstSet.insert(3);
	checkSize(firstSet, 3);
	checkInsertedNumber(firstSet, 3);

	firstSet.insert(4);
	checkSize(firstSet, 4);
	checkInsertedNumber(firstSet, 4);

	displaySet(firstSet);

	firstSet.remove(1);
	checkSize(firstSet, 3);
	checkRemovedNumber(firstSet, 1);

	displaySet(firstSet);

	SetInt secondSet;
	secondSet.insert(5);
	secondSet.insert(6);
	secondSet.insert(7);
	secondSet.insert(8);

	cout << endl;
	cout << "Second set: " << endl;
	displaySet(secondSet);
	cout << endl;

	SetInt thirdSet = firstSet.setUnion(secondSet);
	cout << "After setUnion" << endl;
	displaySet(thirdSet);
	cout << endl;

	thirdSet = firstSet.setIntersection(secondSet);
	cout << "Set Intersection before insertions: " << endl;
	displaySet(thirdSet);
	cout << endl;

	firstSet.insert(10);
	firstSet.insert(12);
	firstSet.insert(14);

	secondSet.insert(10);
	secondSet.insert(12);
	secondSet.insert(14);

	thirdSet = firstSet.setIntersection(secondSet);
	cout << "Set intersection after insertions: " << endl;
	displaySet(thirdSet);
	cout << endl;

	thirdSet = firstSet | secondSet;
	cout << "Set Union using operator" << endl;
	displaySet(thirdSet);
	cout << endl;

	thirdSet = firstSet & secondSet;
	cout << "Set Intersection using operator" << endl;
	displaySet(thirdSet);
	cout << endl;

	return 0;
}