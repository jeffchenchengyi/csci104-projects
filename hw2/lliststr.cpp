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
	Item* copyOfHeadPtr = head_;

	//Delete memory in reverse, from head_ to tail_ backwards
	recRemoveList(copyOfHeadPtr->next);
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
	if(head_ == NULL) {
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
			head_ = insertAtHeadOrTail(val);	 
		} 
		else if(pos == size_) {
			tail_ = insertAtHeadOrTail(val);
		}
		else {
			//Make movingPtr point to (pos - 1) item
			Item* movingPtr = traverseList(pos - 1);

			//Get new item's next to point at (pos - 1) Item's next
			//Get new item's prev to point at (pos - 1) Item
			Item* newItemPtr = createNewItem(val, movingPtr->next, movingPtr);

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
			Item* movingPtr = traverseList(pos - 1);

			//Store toBeDeletedPtr
			Item* toBeDeletedPtr = movingPtr->next;

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
		traverseList(pos)->val = this.val;
	}
	else {
		return;
	}
}

/**
 * Returns the value at the index given by pos.  If the index pos is invalid,
 * then you should return the empty string.
 */
LListStr::string get(int pos) const {
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
LListStr::Item* LListStr::traverseList(int pos) {
	Node* copyOfHeadPtr = head_;

	//Make copyOfHeadPtr point directly at pos item
	for(int i = 0; i < pos; i++) {
		copyOfHeadPtr = copyOfHeadPtr->next;
	}
	return copyOfHeadPtr;
}

//Returns pointer to the new item inserted between head and tail
LListStr::Item* LListStr::insertAtHeadOrTail(const string &val) {
	Node* newItemPtr = createNewItem(val, head_, tail_);
	tail_->next = newItemPtr;
	head_->prev = newItemPtr;
	return newItemPtr;
}

//Removes head_ or tail_ of the list
void LListStr::removeAtHeadOrTail(int pos) {
	if(pos == 0) {
		Item* toBeDeletedPtr = head_;
		tail_->next = tail_->next->next;
		tail_->next->prev = tail_;
		head_ = tail_->next;

		delete toBeDeletedPtr;
	} else {
		Item* toBeDeletedPtr = tail_;
		head_->prev = head_->prev->prev;
		head_->prev->next = head_;
		tail_ = head_->prev;

		delete toBeDeletedPtr;
	}
}

//Recursively deletes the entire list
void LListStr::recRemoveList(Item* currPtr) {
    if(currPtr == head_) {
    	delete currPtr;
        return;
    } else {
        recRemoveList(currPtr->next);
        delete currPtr;
        return;
    }
}

//Default function to return a new heap memory item
LListStr::Item* LListStr::createNewItem(const string &val) {
	return new Item(val, NULL, NULL);
}

//Returns a new heap memory item with next == nextPtr and prev == prevPtr
LListStr::Item* LListStr::createNewItem(const string &val, Item* nextPtr, Item* prevPtr) {
	return new Item(val, nextPtr, prevPtr);
}

//Check if the pos given is within bounds to insert the item
bool LListStr::withinInsertBounds(int pos) {
	((pos >= 0) && (pos <= size_)) ? return true : return false;
}

//Check if the pos given is within bounds to remove, get, set the item
bool LListStr::withinBounds(int pos) {
	((pos >= 0) && (pos < size_)) ? return true : return false;
}