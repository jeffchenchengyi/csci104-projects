#include <iostream>
#include <stdlib.h>

using namespace std;

struct Node {
    int value;
    Node *next;
};

Node* traverse(Node* in, Node* newHeadPtr) {
    if(in == NULL) {
        return newHeadPtr;
    } else {
        Node* copyOfNode = new Node;
        copyOfNode->next = NULL;
        copyOfNode->value = in->value;
        newHeadPtr = recInsertToSorted(copyOfNode, newHeadPtr);
        return traverse(in->next, newHeadPtr);
    }
}

void removeList(Node* in) {
    if(in == NULL) {
        return;
    } else {
        removeList(in->next);
        delete in;
        return;
    }
}

Node* fullsort(Node* in) {
    Node* nodePtr = NULL;
    Node* newHeadPtr = traverse(in, nodePtr);
    removeList(in);
    return newHeadPtr;
}