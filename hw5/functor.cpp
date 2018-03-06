#include <iostream>
#include <stdlib.h>
#include "stackstr.h"
#include "lliststr.h"

using namespace std;

StackStr::StackStr() {
   /** 
	* Single data member of the Stack.
    * We use composition to implement this Stack 
    */
}

StackStr::~StackStr() {
}

/**
 * Returns true if the stack is empty, false otherwise
 */
bool StackStr::empty() const {
	return list_.empty();
}

/**
 * Returns the number of elements in the stack.
 */
int StackStr::size() const {
	return list_.size();
}

/**
 * Pushes a new value, str, onto the top of the stack
  */
void StackStr::push(const string &str) {
	list_.insert(0, str);
}

/**
 * Returns the top value on the stack.
 * If the stack is empty, return the empty string.
 */
string StackStr::top() const {
	if(list_.size() == 0) {
		return "";
	} else {
		return list_.get(0);
	}
}

/**
 * Removes the top element on the stack.
 * Should do nothing if the stack is empty.
 */
void StackStr::pop() {
	if(!list_.empty()) {
		list_.remove(0);
	}
}