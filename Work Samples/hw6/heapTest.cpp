#include <iostream>
#include "heap.h"
#include <functional>

using namespace std;

template<typename T, typename Comparator>
void testHelper(int m, Comparator c, int size, int type) {
	Comparator comp;
	Heap<T, Comparator> testHeap(m, comp);

	for(int i=1; i <= size; i++) {
		testHeap.push(i);
	}

	bool heapWorks = true;

	if(type == 0){
		for(int i=1; i <= size; i++) {
			if(testHeap.top() != i) {
				heapWorks = false;
			}
			cout << testHeap.top() << " ";
			testHeap.pop();
		}
		cout << endl;
	}

	if(type == 1) {
		for(int i=size; i > 0; i--) {
			if(testHeap.top() != i) {
				heapWorks = false;
			}
			cout << testHeap.top() << " ";
			testHeap.pop();
		}
		cout << endl;
	}

	if(heapWorks) {
		cout << "SUCCESS" << endl;
	}
	else {
		cout << "FAIL" << endl;
	}
}

int main(int argc, char* argv[]) {
	less<int> comp1;
	greater<int> comp2;

	// type(0 = minHeap; 1 = maxHeap)
	// test binary with minHeap
	testHelper<int, less<int> >(2, comp1, 15, 0);

	cout << endl;

	// test binary with maxHeap
	testHelper<int, greater<int> >(2,  comp2, 15, 1);

	cout << endl;

	// test 3-nary with minHeap
	testHelper<int, less<int> >(3, comp1, 20, 0);

	cout << endl;

	// test 3-nary with maxHeap
	testHelper<int, greater<int> >(3, comp2, 20, 1);

	cout << endl;

	// test 4-nary with minHeap
	testHelper<int, less<int> >(4, comp1, 20, 0);

	cout << endl;

	// test 4-nary with maxHeap
	testHelper<int, greater<int> >(4, comp2, 20, 1);

	cout << endl;

	// test 5-nary with minHeap
	testHelper<int, less<int> >(5, comp1, 20, 0);

	cout << endl;

	// test 5-nary with maxHeap
	testHelper<int, greater<int> >(5, comp2, 20, 1);

	return 0;
}