#include "stackdbl.h"

StackDbl::StackDbl() {

}

StackDbl::~StackDbl() {
	list_.clear();
}

bool StackDbl::empty() const {
	return list_.empty();
}

void StackDbl::push(const double& val) {
	list_.insert(0, val);
}

double const & StackDbl::top() const {
	return list_.get(0);
}

void StackDbl::pop() {
	if(!list_.empty()) {
		list_.remove(0);
	}
}

