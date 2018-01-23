#include <iostream>
#include <stdlib.h>

#include "lliststr.h"

//Code for each prototyped method in lliststr.h
using namespace std;

LListStr::LListStr() {
	head_ = NULL;
	tail_ = NULL;
	size_ = 0;
}

LListStr::~LListStr() {
	//Deallocate memory from heap if need be
}

/**
 * Returns the current number of items in the list
 */
int LListStr::size() const;

/**
 * Returns true if the list is empty, false otherwise
 */
bool LListStr::empty() const;

/**
 * Inserts val so it appears at the index given as pos. If the
 * index pos is invalid, this function should return without
 * modifying the list.
 */
void LListStr::insert(int pos, const string &val);

/**
 * Removes the value at the index given by pos. If the
 * index pos is invalid, this function should return without
 * modifying the list.
 */
void LListStr::remove(int pos);

/**
 * Overwrites the old value at the index given by pos with val. If the
 * index pos is invalid, this function should return without
 * modifying the list.
 */
void LListStr::set(int pos, const string &val);

/**
 * Returns the value at the index given by pos.  If the index pos is invalid,
 * then you should return the empty string.
 */
LListStr::string get(int pos) const;