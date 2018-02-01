struct Node {
    int value;
    Node *next;
};

//Inserts a new node to a sorted list
Node* recInsertToSorted(Node* newNodePtr, Node* headPtr) {
    if(headPtr == nullptr) {
        headPtr = newNodePtr;
        return headPtr;
    } else {
    	//inserts the new node before current pointer, AKA headptr
        if(newNodePtr->value <= headPtr->value) {
            newNodePtr->next = headPtr;
            headPtr = newNodePtr;
            return headPtr;
        } else {
        	//moves current pointer to next and compares values again
            headPtr->next = recInsertToSorted(newNodePtr, headPtr->next);
            return headPtr;
        }
    }
}

//Traversing original list and simultaneously inserting the elements
//into a newly sorted list
Node* traverse(Node* in, Node* newHeadPtr) {
    if(in == nullptr) {
        return newHeadPtr;
    } else {
        Node* copyOfNode = new Node;
        copyOfNode->next = nullptr;
        copyOfNode->value = in->value;
        newHeadPtr = recInsertToSorted(copyOfNode, newHeadPtr);
        return traverse(in->next, newHeadPtr);
    }
}

void removeList(Node* in) {
    if(in == nullptr) {
        return;
    } else {
        removeList(in->next);

        //Delete in is after the recursive call so that
        //the nodes are deleted from the end of the list
        delete in;
        return;
    }
}

Node* fullsort(Node* in) {
    Node* nodePtr = nullptr;

    //Returns a pointer to the head of the new list
    Node* newHeadPtr = traverse(in, nodePtr);

    //Removes the original list
    removeList(in);
    return newHeadPtr;
}