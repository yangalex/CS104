#ifndef MSORT_H
#define MSORT_H

#include <iostream>
#include <vector>
using namespace std;

// prototypes
template<typename T, typename Comparator>
void mergeSort(vector<T>& myArray, Comparator comp);

template<typename T, typename Comparator>
void msort(vector<T>& myArray, vector<T>& ouput, int start, int end, Comparator comp);

template<typename T, typename Comparator>
void merge(vector<T>& myArray, vector<T>& output, int s1, int e1, int s2, int e2, Comparator comp);


template<typename T, typename Comparator>
void mergeSort(vector<T>& myArray, Comparator comp) 
{
	vector<T> outputArray(myArray);
	msort<T, Comparator>(myArray, outputArray, 0, myArray.size()-1, comp);
}


template<typename T, typename Comparator>
void msort(vector<T>& myArray, vector<T>& output, int start, int end, Comparator comp)
{

	if(start >= end) {
		return;
	}
	else {
		int mid = (start+end)/2;
		msort<T, Comparator>(myArray, output, start, mid, comp);
		msort<T, Comparator>(myArray, output, mid+1, end, comp);

		merge<T, Comparator>(myArray, output, start, mid, mid+1, end, comp);
	}
}


template<typename T, typename Comparator>
void merge(vector<T>& myArray, vector<T>& output, int s1, int e1, int s2, int e2, Comparator comp)
{
	int numElements = e2 - s1 + 1;

	int tempPos = s1;

	while(s1 <= e1 && s2 <= e2) {
		// check to see if myArray[s1] < myArray[s2]
		if(comp(myArray[s1], myArray[s2])) {
			output[tempPos] = myArray[s1];
			s1++;
		}
		else {
			output[tempPos] = myArray[s2];
			s2++;
		}
		tempPos++;
	}

	while(s1 <= e1) {
		output[tempPos] = myArray[s1];
		s1++;
		tempPos++;
	}

	while(s2 <= e2) {
		output[tempPos] = myArray[s2];
		s2++;
		tempPos++;
	}

	// Copy sorted part of output to myArray
	for(int i=0; i <= numElements; i++) {
		myArray[e2] = output[e2];
		e2--;
	}
}



#endif
