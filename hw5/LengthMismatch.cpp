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
	//Deallocate memory from heap for any remaining items in list
	//Delete memory in reverse, from head_ to tail_ backwards
	if(head_ != NULL) {
		LListStr::Item* copyOfHeadPtr = head_;
		LListStr::recRemoveList(copyOfHeadPtr->next);
		head_ = NULL;
		tail_ = NULL;
	}
}

/**
 * Returns the current number of items in the list
 */
int LListStr::size() const {
	return size_;
}

/**
 * Returns true if the list is empty, false otherwise
 */
bool LListStr::empty() const {
	if(size_ == 0) {
		return true;
	} else {
		return false;
	}
}

/**
 * Inserts val so it appears at the index given as pos. If the
 * index pos is invalid, this function should return without
 * modifying the list.
 */
void LListStr::insert(int pos, const string &val) {
	if(withinInsertBounds(pos)) {
		if(pos == 0) {
			insertBetweenHeadAndTail(val, pos);	 
		} 
		else if(pos == size_) {
			insertBetweenHeadAndTail(val, pos);
		}
		else {
			//Make movingPtr point to (pos - 1) item
			LListStr::Item* movingPtr = traverseList(pos - 1);

			//Get new item's next to point at (pos - 1) Item's next
			//Get new item's prev to point at (pos - 1) Item
			LListStr::Item* newItemPtr = createNewItem(val, movingPtr->next, movingPtr);

			//Get next item's prev to point at new item
			//Get (pos - 1) item's next to point at new item
			movingPtr->next->prev = newItemPtr;
			movingPtr->next = newItemPtr;
		}
		//Increase size of list
		size_++;
	} 
	else {
		return;
	}
}

/**
 * Removes the value at the index given by pos. If the
 * index pos is invalid, this function should return without
 * modifying the list.
 */
void LListStr::remove(int pos) {
	if(withinBounds(pos)) {
		if((pos == 0) || (pos == size_ - 1)) {
			removeAtHeadOrTail(pos);
		}
		else {
			//Make movingPtr point to (pos - 1) item
			LListStr::Item* movingPtr = traverseList(pos - 1);

			//Store toBeDeletedPtr
			LListStr::Item* toBeDeletedPtr = movingPtr->next;

			//Connect (pos - 1) item's next to toBeDeletedPtr's next
			//Connect (pos - 1) item's new next's prev to (pos - 1) item
			movingPtr->next = movingPtr->next->next;
			movingPtr->next->prev = movingPtr;

			//Deallocate toBeDeletedPtr's item
			delete toBeDeletedPtr;
		}
		//Decrease size of list
		size_--;
	}
	else {
		return;
	}
}

/**
 * Overwrites the old value at the index given by pos with val. If the
 * index pos is invalid, this function should return without
 * modifying the list.
 */
void LListStr::set(int pos, const string &val) {
	if(withinBounds(pos)) {
		traverseList(pos)->val = val;
	}
	else {
		return;
	}
}

/**
 * Returns the value at the index given by pos.  If the index pos is invalid,
 * then you should return the empty string.
 */
string LListStr::get(int pos) const {
	if(withinBounds(pos)) {
		return traverseList(pos)->val;
	}
	else {
		return "";
	}
}

/**
 * Private functions
 */
//Returns a pointer to item at pos
LListStr::Item* LListStr::traverseList(int pos) const {
	Item* copyOfHeadPtr = head_;

	//Make copyOfHeadPtr point directly at pos item
	for(int i = 0; i < pos; i++) {
		copyOfHeadPtr = copyOfHeadPtr->next;
	}
	return copyOfHeadPtr;
}

//Returns pointer to the new item inserted between head and tail
void LListStr::insertBetweenHeadAndTail(const string &val, int pos) {
	if(size_ == 0) {
		LListStr::Item* newItemPtr = createNewItem(val);
		tail_ = newItemPtr;
		head_ = newItemPtr;
		newItemPtr->next = newItemPtr;
		newItemPtr->prev = newItemPtr;
	} else {
		LListStr::Item* newItemPtr = createNewItem(val);
		tail_->next = newItemPtr;
		head_->prev = newItemPtr;
		newItemPtr->next = head_;
		newItemPtr->prev = tail_;
		if(pos == 0) {
			head_ = newItemPtr;
		} else {
			tail_ = newItemPtr;
		}
	}
}

//Removes head_ or tail_ of the list
void LListStr::removeAtHeadOrTail(int pos) {
	//If removing only item in list
	if(size_ == 1) {
		delete head_;
		head_ = NULL;
		tail_ = NULL;
	} 
	//If removing head or tail in a list with other items
	else {
		if(pos == 0) {
			LListStr::Item* toBeDeletedPtr = head_;
			tail_->next = tail_->next->next;
			tail_->next->prev = tail_;
			head_ = tail_->next;

			delete toBeDeletedPtr;
		} else {
			LListStr::Item* toBeDeletedPtr = tail_;
			head_->prev = head_->prev->prev;
			head_->prev->next = head_;
			tail_ = head_->prev;

			delete toBeDeletedPtr;
		}
	}
}

//Recursively deletes the entire list
void LListStr::recRemoveList(LListStr::Item* currPtr) {
    if(currPtr == head_) {
    	delete currPtr;
    	size_--;
        return;
    } else {
        LListStr::recRemoveList(currPtr->next);
        delete currPtr;
        size_--;
        return;
    }
}

//Default function to return a new heap memory item
LListStr::Item* LListStr::createNewItem(const string &val) {
	return new LListStr::Item(val, NULL, NULL);
}

//Returns a new heap memory item with next == nextPtr and prev == prevPtr
LListStr::Item* LListStr::createNewItem(const string &val, LListStr::Item* nextPtr, LListStr::Item* prevPtr) {
	return new LListStr::Item(val, nextPtr, prevPtr);
}

//Check if the pos given is within bounds to insert the item
bool LListStr::withinInsertBounds(int pos) const {
	return ((pos >= 0) && (pos <= size_)) ? true : false;
}

//Check if the pos given is within bounds to remove, get, set the item
bool LListStr::withinBounds(int pos) const {
	return ((pos >= 0) && (pos < size_)) ? true : false;
}