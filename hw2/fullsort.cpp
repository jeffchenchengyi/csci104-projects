#include <iostream>
#include <stdlib.h>

using namespace std;

struct Node {
    int value;
    Node *next;
};

Node* head = NULL;

void insert(int x) {
	Node* temp = new Node;
	temp->value = x;
	temp->next = head;
	head = temp;
}

void traverse(Node* h) {
	Node* temp = h;
	while(temp != NULL) {
		cout << temp->value;
		temp = temp->next;
	}
	cout << endl;
}

//Node* fullsort (Node*);

int main (int argc, char* argv[])
{
	if(argc < 2){
    cerr << "Please provide a list of integers separated by whitespace." << endl;
    return 1;
	}

	for(int i = 1; i < argc; i++) {
		Node* curr = new Node;
		curr->value = atoi(argv[i]);
		temp->next = curr;
	}

	while(head != NULL) {
		head
	}

	//Node* fullsort (Node* in);
	return 0;
}
/*
Node* fullsort(Node* in) {

}*/