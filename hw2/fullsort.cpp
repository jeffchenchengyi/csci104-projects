#include <iostream>
#include <stdlib.h>

using namespace std;

struct Node {
    int value;
    Node *next;
};

void print(Node* head) {
    if(head == NULL) {
        return;
    }
    cout << head->value << endl;
    print(head->next);
}

//Insert new Node at the beginning of the linked list
void insertAtStart(Node* &head, int val) {
    
    //Create a pointer to Node from stack
    //Create a new Node in heap memory
    Node* nodePtr = new Node;
    
    //Make data member "Node* next" in new 
    //node point to the same Node that head
    //is pointing to, AKA, connecting new node
    //to the first Node element of list
    nodePtr->next = head;
    
    //Change new node's "value"
    nodePtr->value = val;
    
    //Get head to point to the new node by 
    //making it the same pointer as nodePtr
    head = nodePtr;
}

//Iteratively insert new Node at the end of the linked list
void itInsertAtEnd(Node* &head, int val) {
    
    //Create a pointer to Node from stack
    //Create a new Node in heap memory
    Node* nodePtr = new Node;
    nodePtr->next = NULL;
    nodePtr->value = val;
    
    //Check if my head is pointing to NULL,
    //AKA, an empty list, then make my head
    //point to the new Node 
    if(head == NULL) {
        head = nodePtr;
    } else {
        
        //Create new pointer that points to same
        //Node element as head
        Node* copyOfHead = head;
    
        //Go to the end of the list, will know
        //we reached when "Node* next" is pointing 
        //to NULL
        while(copyOfHead->next != NULL) {
            copyOfHead = copyOfHead->next;
        }
        
        //Making last Node element point to the 
        //new Node
        copyOfHead->next = nodePtr;
    }
}

//Recursively insert new Node at the end of the linked list
void recInsertAtEnd(Node* &head, int val) {
    
    //Base Case: When my head is pointing to NULL,
    //AKA, head is the same as the "Node* next" in
    //the last Node element and get head to point 
    //to a new Node in heap memory and initliase 
    //"value" and "Node* next = NULL" 
    if(head == NULL) {
        head = new Node;
        head->value = val;
        head->next = NULL;
    } 
    //Recursive case: Pass the "Node* next" of the
    //Node element that head is pointing to to the 
    //function, making it seem like head is pointing 
    //to the next Node element of the list until it 
    //reaches the end of the list in the base case
    else {
        recInsertAtEnd(head->next, val);
    }
}

Node* recInsertToSorted(Node* newNodePtr, Node* headPtr) {
    if(headPtr == NULL) {
        headPtr = newNodePtr;
        return headPtr;
    } else {
        if(newNodePtr->value <= headPtr->value) {
            newNodePtr->next = headPtr;
            headPtr = newNodePtr;
            return headPtr;
        } else {
            headPtr->next = recInsertToSorted(headPtr->next, newNodePtr);
            return headPtr;
        }
    }
}
/*
Node* removeOutlierNode(Node* headPtr, Node* currentPtr) {
    if(currentPtr->next == NULL) {
        return nullptr; 
    } else {
        if(currentPtr->value <= currentPtr->next->value) {
            return removeOutlierNode(headPtr, currentPtr->next);
        } else {
            Node* nextPtr = currentPtr->next;
            currentPtr->next = currentPtr->next->next;
            nextPtr->next = NULL;
            Node* newHeadPtr = removeOutlierNode(headPtr, currentPtr);
            if(newHeadPtr == nullptr) {
                return recInsertToSorted(headPtr, nextPtr);
            }
        }
    }
}
*/
/*
Node* newSortedList(Node* in, Node* newHeadPtr) {
    if(in == NULL) {
        return NULL;
    } else {
        Node* modifiedHeadPtr = recInsertToSorted(in, newHeadPtr);
        Node* lastNodePtr = newSortedList(in->next, modifiedHeadPtr);
        if(lastNodePtr == NULL) {
            return modifiedHeadPtr;
        } else {
            return lastNodePtr;
        }
    }
}
*/
void traverse(Node* in, Node* &newHeadPtr) {
    if(in == NULL) {
        return;
    } else {
        Node* copyOfNode = in;
        newHeadPtr = recInsertToSorted(copyOfNode, newHeadPtr);
        traverse(copyOfNode->next, newHeadPtr);
    }
}

Node* fullsort(Node* in) {
    Node* newHeadPtr = NULL;
    traverse(in, newHeadPtr);
    return newHeadPtr;
}

int main (int argc, char* argv[])
{
	if(argc < 2){
    cerr << "Please provide a list of integers separated by whitespace." << endl;
    return 1;
	}
	
    Node* head = NULL;
    
	for(int i = 1; i < argc; i++) {
	    recInsertAtEnd(head, atoi(argv[i]));
	}
	
	cout << "Mostly sorted list:" << endl;
	print(head);
	Node* newHead = fullsort(head);
	
	cout << "Sorted list:" << endl;
	print(newHead);
	
	return 0;
}