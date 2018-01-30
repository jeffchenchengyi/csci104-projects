struct Node {
    int value;
    Node *next;
};

Node* recInsertToSorted(Node* newNodePtr, Node* headPtr) {
    if(headPtr == nullptr) {
        headPtr = newNodePtr;
        return headPtr;
    } else {
        if(newNodePtr->value <= headPtr->value) {
            newNodePtr->next = headPtr;
            headPtr = newNodePtr;
            return headPtr;
        } else {
            headPtr->next = recInsertToSorted(newNodePtr, headPtr->next);
            return headPtr;
        }
    }
}

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
        delete in;
        return;
    }
}

Node* fullsort(Node* in) {
    Node* nodePtr = nullptr;
    Node* newHeadPtr = traverse(in, nodePtr);
    removeList(in);
    return newHeadPtr;
}