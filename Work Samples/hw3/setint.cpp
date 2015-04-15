#include "setint.h"
#include <iostream>

SetInt::SetInt()
{

}

SetInt::~SetInt()
{
	list_.clear();
}

SetInt::SetInt(const SetInt& other)
{
	this->list_ = other.list_;
}

SetInt& SetInt::operator=(const SetInt& other)
{
	this->list_ = other.list_;
	return *this;
}

int SetInt::size() const
{
	return list_.size();
}

bool SetInt::empty() const
{
	return list_.empty();
}

void SetInt::insert(const int& val)
{
	if(exists(val)) {
		return;
	}

	list_.push_back(val);
	return;
}

void SetInt::remove(const int& val)
{
	if(!exists(val)) {
		return;
	}

	int steps = 0;

	for(int i=0; i < list_.size(); i++) {
		if(list_.get(i) == val) {
			list_.remove(steps);
			return;
		}
		else {
			steps++;
		}
	}	
}

bool SetInt::exists(const int& val) const
{
	bool exist = false;
	for(int i=0; i < list_.size(); i++) {
		if(list_.get(i) == val) {
			exist = true;
		}
	}

	return exist;
}

int const* SetInt::first() 
{
	if(empty()) {
		return NULL;
	}

	it_ = 0;
	return &(list_.get(0));
}

int const* SetInt::next()
{
	it_++;
	if(it_ >= list_.size()) {
		return NULL;
	}
	else {
		return &(list_.get(it_));
	}
}

SetInt SetInt::setUnion(const SetInt& other) const
{
	// Initialize new set
	SetInt newSet;
	// Initialize iterator
	const int* it;

	// Copy this to get over const
	SetInt lhs = *this;
	// Iterate over first set
	it = lhs.first();
	while(it != NULL) {
		newSet.insert(*it);
		it = lhs.next();
	}

	// copy set first to get around const 
	SetInt rhs = other;
	// Iterate over second set
	it = rhs.first();
	while(it != NULL) {
		newSet.insert(*it);
		it = rhs.next();
	}

	return newSet;

}

SetInt SetInt::setIntersection(const SetInt& other) const
{
	// Initialize new set
	SetInt newSet;
	// Initialize iterator
	const int* it;

	// copy this to get around const problem
	SetInt lhs = *this;
	// Check intersections based on this
	it = lhs.first();
	while(it != NULL) {
		// Check if number matches 
		if(other.exists(*it)) {
			newSet.insert(*it);
		}
		// keep going
		it = lhs.next();
	}

	return newSet;
}

SetInt SetInt::operator|(const SetInt& other) const
{
	// simply reuse setUnion function
	return this->setUnion(other);
}

SetInt SetInt::operator&(const SetInt& other) const 
{
	// simply reuse setIntersection function
	return this->setIntersection(other);
}