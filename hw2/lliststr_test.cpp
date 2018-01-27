#include "lliststr.h"
#include <iostream>
#include <string>

using namespace std;

void checkEmpty(LListStr *list, bool expEmpty) {
	if (list->empty() == expEmpty) {
		cout << "SUCCESS: List is ";
		if (!expEmpty) cout << "not ";
		cout << "empty" << endl;
	}
	else {
		cout << "FAIL: List is ";
		if (expEmpty) cout << "not ";
		cout << "empty" << endl;
	}
}

void checkSize(LListStr *list, int expSize) {
	int size = list->size();
	if (size == expSize) {
		cout << "SUCCESS: List has size " << size << endl;
	}
	else {
		cout << "FAIL: List has size " << size;
		cout << " but expected " << expSize << endl;
	}
}

void checkGet(LListStr *list, int pos, const string &expStr) {
	string str = list->get(pos);
	if (str == expStr) {
		cout << "SUCCESS: String at index " << pos << " is \'" << expStr << "\'" << endl;
	} 
	else {
		cout << "FAIL: String at index " << pos << " is \'" << str << "\'";
		cout << " but expected \'" << expStr << "\'" << endl;
	}
}

/*
 *My helper functions for test cases
 */
void setGetRemoveItem(LListStr *list, int pos, const string &expStr);
void insertSetGetItem(LListStr *list, int pos, const string &expStr);
void printList(LListStr *list);

int main() {
	LListStr* list = new LListStr();

	cout << "-----START of CS104's default tests-----" << endl;
	cout << endl;

	// Check if the list is initially empty.
	checkEmpty(list, true);
	checkSize(list, 0);

	// Insert an item at the head.
	list->insert(0, "CSCI104");

	// Verify the list is not empty
	checkEmpty(list, false);
	checkSize(list, 1);

	// Check if the value is correct.
	checkGet(list, 0, "CSCI104");
	cout << endl;

	cout << "-----END of CS104's default tests-----" << endl;

	// TODO: Continue adding tests for your program, or start your own file with your
	// own tests. Remember to submit a file that is named correctly!

	// My Tests
	cout << endl;
	cout << "-----START of Chengyi (Jeff) Chen's tests-----" << endl;
	cout << endl;

	// Check if I can remove from pos == 0
	cout << "[REMOVE TEST 1]: Set, get, then remove the ONLY item in the list" << endl;
	setGetRemoveItem(list, 0, "I am the ONLY item :>");

	// Check if I can insert in pos == 0
	cout << "[INSERT TEST 1]: Insert, set, get 0th item" << endl;
	insertSetGetItem(list, 0, "I am the 0th item :~)");

	// Check if I can insert 5 items in list
	cout << "[INSERT TEST 2]: Insert 5 items in list" << endl;
	for(int i = 0; i < 5; i++) {
		insertSetGetItem(list, i + 1, "I am an item :~)");
	}

	// Check if I can insert a first item to the list
	cout << "[INSERT TEST 3]: Insert an item to the front" << endl;
	insertSetGetItem(list, 0, "I am an item :~)");

	// Check if I can insert a last item to the list
	cout << "[INSERT TEST 3]: Insert an item to the back" << endl;
	insertSetGetItem(list, list->size(), "I am an item :~)");

	// Check if I can insert an item to an out of bounds position
	cout << "[INSERT TEST 4]: Insert an item out of bounds" << endl;
	insertSetGetItem(list, 20, "I am out of bounds :<");

	// Check if I can remove from pos == 0 in a full list
	cout << "[REMOVE TEST 2]: Set, get, then remove the FIRST item in the list" << endl;
	setGetRemoveItem(list, 0, "I am the 0th item :)");

	// Check if I can remove from pos 3
	cout << "[REMOVE TEST 3]: Set, get, then remove AN item in the list" << endl;
	setGetRemoveItem(list, 3, "I am the 3rd item :|");

	// Check if I can remove from pos == size()
	cout << "[REMOVE TEST 4]: Set, get, then remove an item in out of bounds position" << endl;
	setGetRemoveItem(list, 20, "I am out of bounds :<");

	// Check if I can remove from pos == size()
	cout << "[REMOVE TEST 5]: Set, get, then remove the LAST item in the list" << endl;
	setGetRemoveItem(list, list->size() - 1, "I am the LAST item :(");

	// Traverse and print out whole list
	cout << "Current List:" << endl;
	printList(list);

	cout << endl;
	cout << "-----END of Chengyi (Jeff) Chen's tests-----" << endl;	

	// Clean up memory.
	delete list;
}

/*
 *My helper functions for test cases
 */
void setGetRemoveItem(LListStr *list, int pos, const string &expStr) {
	cout << "1. Setting value at position " << pos << " to \"" << expStr << "\"... " << endl; 
	list->set(pos, expStr);
	cout << endl;

	cout << "2. New value at position " << pos << " : \n--> \"" << list->get(pos) << "\"" << endl; 
	cout << "--- Current Size of List: " << list->size() << " ---"<< endl;
	cout << endl;

	cout << "3. Removing item at position " << pos << " ... " << endl;
	list->remove(pos);

	//Try to get item at deletion
	cout << "Current value at position: \n--> " << list->get(pos) << endl;
	cout << "--- Current Size of List: " << list->size() << " ---"<< endl;
	cout << endl;
	cout << endl;
}

void insertSetGetItem(LListStr *list, int pos, const string &expStr) {
	cout << "1. Inserting item at position " << pos << " ... " << endl;
	list->insert(pos, expStr);
	cout << endl;

	cout << "Current value at position: \n--> " << list->get(pos) << endl;
	cout << "--- Current Size of List: " << list->size() << " ---"<< endl;
	cout << endl;

	cout << "2. Setting value at position " << pos << " to \"I HAVE REPLACED THE ORIGINAL HAHA :~|\"... " << endl; 
	list->set(pos, "I HAVE REPLACED THE ORIGINAL HAHA :~|");
	cout << endl;

	cout << "3. New value at position " << pos << " : \n--> \"" << list->get(pos) << "\"" << endl; 
	cout << "--- Current Size of List: " << list->size() << " ---"<< endl;
	cout << endl;
	cout << endl;
}

void printList(LListStr *list) {
	for(int i = 0; i < list->size(); i++) {
		cout << i << ". " << list->get(i) << endl;
	}
}