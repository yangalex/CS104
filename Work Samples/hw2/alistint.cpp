#include "alistint.h"
#include <cstdlib>

AListInt::AListInt() {
	data = new int[10];
	size_ = 0;
	capacity_ = 10;
}

AListInt::AListInt(int cap) {
	data = new int[cap];
	size_ = 0;
	capacity_ = cap;
}

AListInt::~AListInt() {
	delete[] data;
}

int AListInt::size() const {
	return size_;
}

int AListInt::capacity() const {
	return capacity_;
}

bool AListInt::empty() const {
	if(size_ == 0) {
		return true;
	}
	else {
		return false;
	}
}

void AListInt::insert(int pos, const int& val) {
	
	// If array is empty
	if(empty()) {
		data[0] = val;
		size_++;
	}
	else {
		// If inserting at back
		if(pos == size_) {
			if(size_ == capacity_) {
				resize();
			}

			data[pos] = val;
			size_++;
		}
		// If inserting anywhere else except back
		else if(pos >= 0 && pos < size_) {
			if(size_ == capacity_) {
				resize();
			}

			for(int i=size_-1; i >= pos; i--) {
				data[i+1] = data[i];
			}

			data[pos] = val;
			size_++;
		}
	}
}

void AListInt::remove(int pos) {
	if(empty()) {
		return;
	}

	if(pos == size_-1) {
		data[pos] = 0;
		size_--;
		return;
	}

	else if(pos >= 0 && pos < size_-1){
		for(int i=pos+1; i < size_; i++) {
			data[i-1] = data[i];
		}
		size_--;
	}
}

void AListInt::set(int position, const int& val) {
	data[position] = val;
}

int& AListInt::get(int position) {
	return data[position];
}

int const & AListInt::get(int position) const {
	return data[position];
}

void AListInt::resize() {
	int* temp = data;
	data = new int[capacity_*2];
	capacity_ = capacity_*2;
	for(int i=0; i < size_; i++) {
		data[i] = temp[i];
	}

	delete[] temp;
}