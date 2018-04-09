#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

/**
* A templated class for a Node in a search tree. The getters for parent/left/right are virtual so that they
* can be overridden for future kinds of search trees, such as Red Black trees, Splay trees, and AVL trees.
*/
template <typename Key, typename Value>
class Node 
{
public:
	Node(const Key& key, const Value& value, Node<Key, Value>* parent);
	virtual ~Node();

	const std::pair<const Key, Value>& getItem() const;
	std::pair<const Key, Value>& getItem();
	const Key& getKey() const;
	const Value& getValue() const;
	Value& getValue();

	virtual Node<Key, Value>* getParent() const;
	virtual Node<Key, Value>* getLeft() const;
	virtual Node<Key, Value>* getRight() const;
	int getHeight() const;

	void setParent(Node<Key, Value>* parent);
	void setLeft(Node<Key, Value>* left);
	void setRight(Node<Key, Value>* right);
	void setValue(const Value &value);
	void setHeight(int height);

protected:
	std::pair<const Key, Value> mItem;
	Node<Key, Value>* mParent;
	Node<Key, Value>* mLeft;
	Node<Key, Value>* mRight;
	int mHeight;
};

/*
	-----------------------------------------
	Begin implementations for the Node class.
	-----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) 
	: mItem(key, value)
	, mParent(parent)
	, mLeft(NULL)
	, mRight(NULL)
	, mHeight(1)
{ 

} 

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed within the deleteAll() helper method in the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node() 
{ 

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const 
{ 
	return mItem; 
}

/**
* A non-const getter for the item. 
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem() 
{ 
	return mItem; 
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const 
{ 
	return mItem.first; 
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const 
{ 
	return mItem.second; 
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
	return mItem.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const 
{ 
	return mParent; 
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const 
{ 
	return mLeft; 
}

/**
* An implementation of the virtual function for retreiving the right child. 
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const 
{ 
	return mRight; 
}

/**
* A const getter for the height.
*/
template<typename Key, typename Value>
int Node<Key, Value>::getHeight() const
{
	return mHeight;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent) 
{ 
	mParent = parent; 
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left) 
{ 
	mLeft = left; 
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right) 
{ 
	mRight = right; 
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value) 
{ 
	mItem.second = value; 
}

/**
* A setter for the height of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setHeight(int height) 
{ 
	mHeight = height;
}

/*
	---------------------------------------
	End implementations for the Node class.
	---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree 
{
	public:
		BinarySearchTree(); //TODO
		virtual ~BinarySearchTree(); //TODO
		int height(); //TODO 
		bool isBalanced(); //TODO 
		virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
		virtual void remove(const Key& key); //TODO
		void clear(); //TODO
		void print() const;

	public:
		/**
		* An internal iterator class for traversing the contents of the BST.
		*/
		class iterator 
		{
			public:
				iterator(Node<Key,Value>* ptr);
				iterator();

				std::pair<const Key, Value>& operator*();
				std::pair<const Key, Value>* operator->();

				bool operator==(const iterator& rhs) const;
				bool operator!=(const iterator& rhs) const;
				iterator& operator=(const iterator& rhs);

				iterator& operator++();

			protected:
				Node<Key, Value>* mCurrent;
		};

	public:
		iterator begin();
		iterator end();
		iterator find(const Key& key) const;

	protected:
		Node<Key, Value>* internalFind(const Key& key) const; //TODO
		Node<Key, Value>* getSmallestNode() const; //TODO
		void printRoot (Node<Key, Value>* root) const;

	protected:
		Node<Key, Value>* mRoot;

	private:
		bool isBalancedHelper(Node<Key, Value>* curr_node_ptr) const;
		void updateAncestorChainHeights(Node<Key, Value>* curr_node_ptr);
		void insertHelper(const std::pair<const Key, Value>& keyValuePair,
			Node<Key, Value>* curr_node_ptr,
			Node<Key, Value>* parent_ptr);
		void removeHelper(const Key& key, Node<Key, Value>* curr_node_ptr);
		void changeChild(Node<Key, Value>* curr_node_ptr, Node<Key, Value>* new_child_ptr);
		Node<Key, Value>* findPredecessor(Node<Key, Value>* curr_node_ptr);
		Node<Key, Value>* getSubTreeMax(Node<Key, Value>* curr_node_ptr) const;
		Node<Key, Value>* firstLeftAncestor(Node<Key, Value>* curr_node_ptr);
		void postOrderRemoval(Node<Key, Value>* curr_node_ptr);
		Node<Key, Value>* getSubTreeMin(Node<Key, Value>* curr_node_ptr) const;
		Node<Key, Value>* internalFindHelper(const Key& key, 
			Node<Key, Value>* curr_node_ptr) const; 
};

/*
	---------------------------------------------------------------
	Begin implementations for the BinarySearchTree::iterator class.
	---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<typename Key, typename Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value>* ptr)
	: mCurrent(ptr)
{ 

}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<typename Key, typename Value>
BinarySearchTree<Key, Value>::iterator::iterator()
	: mCurrent(NULL)
{ 

}

/**
* Provides access to the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& BinarySearchTree<Key, Value>::iterator::operator*() 
{ 
	return mCurrent->getItem();
}

/**
* Provides access to the address of the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>* BinarySearchTree<Key, Value>::iterator::operator->() 
{ 
	return &(mCurrent->getItem()); 
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::iterator::operator==(const BinarySearchTree<Key, Value>::iterator& rhs) const
{
	return this->mCurrent == rhs.mCurrent;
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::iterator::operator!=(const BinarySearchTree<Key, Value>::iterator& rhs) const
{
	return this->mCurrent != rhs.mCurrent;
}

/**
* Sets one iterator equal to another iterator.
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator &BinarySearchTree<Key, Value>::iterator::operator=(const BinarySearchTree<Key, Value>::iterator& rhs)
{
	this->mCurrent = rhs.mCurrent;
	return *this;
}

/**
* Advances the iterator's location using an in-order traversal.
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator& BinarySearchTree<Key, Value>::iterator::operator++()
{
	if(mCurrent->getRight() != NULL)
	{
		mCurrent = mCurrent->getRight();
		while(mCurrent->getLeft() != NULL)
		{
			mCurrent = mCurrent->getLeft();
		}
	}
	else if(mCurrent->getRight() == NULL)
	{
		Node<Key, Value>* parent = mCurrent->getParent();
		while(parent != NULL && mCurrent == parent->getRight())
		{
			mCurrent = parent;
			parent = parent->getParent();
		}
		mCurrent = parent;
	}
	return *this;
}

/*
	-------------------------------------------------------------
	End implementations for the BinarySearchTree::iterator class.
	-------------------------------------------------------------
*/

/*
	-----------------------------------------------------
	Begin implementations for the BinarySearchTree class.
	-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<typename Key, typename Value>
BinarySearchTree<Key, Value>::BinarySearchTree() 
	: mRoot(nullptr)
{ 
	// TODO // Step 8a. Constructor, member initialization, set mRoot to nullptr
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree() 
{ 
	// TODO
	clear(); // Step 8b. Destructor, just call clear
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{ 
	printRoot(mRoot);
	std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::begin()
{
	BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
	return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::end()
{
	BinarySearchTree<Key, Value>::iterator end(NULL);
	return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::find(const Key& key) const 
{
	Node<Key, Value>* curr = internalFind(key);
	BinarySearchTree<Key, Value>::iterator it(curr);
	return it;
}

/*
	-------------------------------------------------------------------------------------------
	Begin implementations for the BinarySearchTree class Height and Balance checking functions.
	-------------------------------------------------------------------------------------------
*/

/**
* An method to return the height of the BST.
*/
template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::height()
{
	// TODO
	if(mRoot != nullptr) 
	{
		return mRoot->getHeight();	// Step 1. O(1)
	} 
	else 
	{
		return 0;
	}
}


/**
* An method to checks if the BST is balanced. This method returns true if and only if the BST is balanced.
*/
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced()
{
	// TODO
	return isBalancedHelper(mRoot); // Step 2. O(n), worst case check all the node heights because of recursion
}

/**
* A helper method to recursively checks if the BST is balanced. 
* This method returns true if and only if the BST is balanced.
*/
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalancedHelper(Node<Key, Value>* curr_node_ptr) const
{
	if(curr_node_ptr == nullptr) // Case 1: When curr_node is null, tree is balanced (leaves and empty tree)
	{
		return true;
	} 
	else 
	{
		if(curr_node_ptr->getLeft() != nullptr 
			&& curr_node_ptr->getRight() != nullptr) // Case 2: When node has both children sub-trees
		{
			if(abs(curr_node_ptr->getLeft()->getHeight() 
				- curr_node_ptr->getRight()->getHeight()) <= 1) {
				return (isBalancedHelper(curr_node_ptr->getLeft()) && isBalancedHelper(curr_node_ptr->getRight()));
			} else {
				return false;
			}
		} 
		else if(curr_node_ptr->getLeft() == nullptr 
			&& curr_node_ptr->getRight() != nullptr) // Case 3: When node has right-child sub-tree
		{
			if(curr_node_ptr->getRight()->getHeight() == 1) {
				return true;
			} else {
				return false;
			}
		}
		else if(curr_node_ptr->getLeft() != nullptr 
			&& curr_node_ptr->getRight() == nullptr) // Case 4: When node has left-child sub-tree
		{
			if(curr_node_ptr->getLeft()->getHeight() == 1) {
				return true;
			} else {
				return false;
			}
		}
		else 
		{
			return true; // Case 5: When node has no children
		}
	}
}

/*
	-------------------------------------------------------------------------------------------
	End implementations for the BinarySearchTree class Height and Balance checking functions.
	-------------------------------------------------------------------------------------------
*/

/*
	-------------------------------------------------------------------------------------
	Begin implementations for the BinarySearchTree class Insertion and Removal functions.
	-------------------------------------------------------------------------------------
*/

/**
* A method to recursively checks if the heights need to be adjusted after insertion and removal
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::updateAncestorChainHeights(Node<Key, Value>* curr_node_ptr)
{
	if(curr_node_ptr != nullptr) // Ensure current node exist
	{
		if(curr_node_ptr->getLeft() != nullptr 
			&& curr_node_ptr->getRight() != nullptr) // Case 1: When node has both children sub-trees
		{
			if(curr_node_ptr->getLeft()->getHeight() 
				> curr_node_ptr->getRight()->getHeight()) // Left subtree has greater height
			{
				curr_node_ptr->setHeight(curr_node_ptr->getLeft()->getHeight() + 1);
			} 
			else  // Right subtree has greater or equal height
			{
				curr_node_ptr->setHeight(curr_node_ptr->getRight()->getHeight() + 1);
			}
		} 
		else if(curr_node_ptr->getLeft() == nullptr 
			&& curr_node_ptr->getRight() != nullptr) // Case 2: When node has right-child sub-tree
		{
			curr_node_ptr->setHeight(curr_node_ptr->getRight()->getHeight() + 1);
		}
		else if(curr_node_ptr->getLeft() != nullptr 
			&& curr_node_ptr->getRight() == nullptr) // Case 3: When node has left-child sub-tree
		{
			curr_node_ptr->setHeight(curr_node_ptr->getLeft()->getHeight() + 1);
		}

		if(curr_node_ptr->getParent() != nullptr) // THIS IS THE ROOT NODE
		{
			updateAncestorChainHeights(curr_node_ptr->getParent()); // Recursive call upwards to parent
		} 
		else 
		{
			return;
		}
	}
}

/**
* An insert method to insert into a Binary Search Tree. The tree will not remain balanced when 
* inserting.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value>& keyValuePair)
{
	// TODO
	if(internalFind(keyValuePair.first) == nullptr) // Check if the key already exists in the BST
	{
		insertHelper(keyValuePair, mRoot, nullptr); // Step 3. O(h), traversing down half a subtree at a time, 
			//at most visit log2(n) OR h nodes, then updating ancestor heights in insertHelper also worst case O(h)
	}
}

/**
* An insert method to insert into a Binary Search Tree. 
* The tree will not remain balanced when inserting.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::insertHelper(const std::pair<const Key, Value>& keyValuePair,
	Node<Key, Value>* curr_node_ptr,
	Node<Key, Value>* parent_ptr)
{
	if(curr_node_ptr == nullptr) // If the node we are at is empty, we can insert the new node
	{
		curr_node_ptr = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, parent_ptr);
		if(parent_ptr == nullptr) // THIS IS THE ROOT NODE
		{
			mRoot = curr_node_ptr;
		} 
		else 
		{
			changeChild(curr_node_ptr, curr_node_ptr);
		}
		updateAncestorChainHeights(curr_node_ptr); // Updates all the heights in the ancestor chain
	}
	else 
	{
		if(keyValuePair.first > curr_node_ptr->getKey()) // Case 1: key is greater than current node key
		{
			insertHelper(keyValuePair, curr_node_ptr->getRight(), curr_node_ptr);
		}
		else if(keyValuePair.first < curr_node_ptr->getKey()) // Case 2: key is lesser than current node key
		{
			insertHelper(keyValuePair, curr_node_ptr->getLeft(), curr_node_ptr);
		}
	}
}

/**
* An remove method to remove a specific key from a Binary Search Tree. The tree may not remain balanced after
* removal.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
	// TODO
	removeHelper(key, internalFind(key)); // Step 4. O(h), internalFind takes O(h) worst case, 
		// finding predecessor takes O(h) worst case too, other operations constant time, and 
		// updating the ancestor heights also O(h)
}

/**
* An remove Helper method to remove a specific key from a Binary Search Tree. 
* The tree may not remain balanced after
* removal.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::removeHelper(const Key& key, Node<Key, Value>* curr_node_ptr)
{
	if(curr_node_ptr != nullptr) 
	{
		if(curr_node_ptr->getLeft() == nullptr 
			&& curr_node_ptr->getRight() == nullptr) // Case 1: Both left and right children are null, hence leaf node or single root node
		{
			if(curr_node_ptr->getParent() == nullptr) // THIS IS THE ROOT NODE
			{
				delete mRoot;
				mRoot = nullptr;
			}
			else
			{
				changeChild(curr_node_ptr, nullptr); // Updates the child for the parent of current node
				updateAncestorChainHeights(curr_node_ptr); // Updates all the heights in the ancestor chain
				delete curr_node_ptr;
			}
			curr_node_ptr = nullptr;
		}
		else if(curr_node_ptr->getLeft() != nullptr 
			&& curr_node_ptr->getRight() == nullptr) // Case 2: Only left child exists
		{
			Node<Key, Value>* temp_ptr = curr_node_ptr; // Keep copy of node ptr for deleting
			curr_node_ptr = curr_node_ptr->getLeft(); // Make current node point to current node's left child
			if(temp_ptr->getParent() == nullptr) // THIS IS THE ROOT NODE
			{
				mRoot = curr_node_ptr;
				mRoot->setParent(temp_ptr->getParent()); // Set current node's parent to prev current node's parent
				updateAncestorChainHeights(mRoot); // Updates all the heights in the ancestor chain
			} 
			else 
			{
				curr_node_ptr->setParent(temp_ptr->getParent()); // Set current node's parent to prev current node's parent
				changeChild(temp_ptr, curr_node_ptr); // Updates the child for the parent of current node
				updateAncestorChainHeights(curr_node_ptr); // Updates all the heights in the ancestor chain
			}
			delete temp_ptr;
			temp_ptr = nullptr;
		}
		else if(curr_node_ptr->getLeft() == nullptr 
			&& curr_node_ptr->getRight() != nullptr) // Case 3: Only right child exists
		{
			Node<Key, Value>* temp_ptr = curr_node_ptr; // Keep copy of node ptr for deleting
			curr_node_ptr = curr_node_ptr->getRight(); // Make current node point to current node's right child
			if(temp_ptr->getParent() == nullptr) // THIS IS THE ROOT NODE
			{
				mRoot = curr_node_ptr;
				mRoot->setParent(temp_ptr->getParent()); // Set current node's parent to prev current node's parent
				updateAncestorChainHeights(mRoot); // Updates all the heights in the ancestor chain
			} 
			else 
			{
				curr_node_ptr->setParent(temp_ptr->getParent()); // Set current node's parent to prev current node's parent
				changeChild(temp_ptr, curr_node_ptr); // Updates the child for the parent of current node
				updateAncestorChainHeights(curr_node_ptr); // Updates all the heights in the ancestor chain
			}
			delete temp_ptr;
			temp_ptr = nullptr;
		}
		else if(curr_node_ptr->getLeft() != nullptr 
			&& curr_node_ptr->getRight() != nullptr) // Complex Case 4: Both children exist, we need to replace current node with its predecessor
		{
			Node<Key, Value>* pred_node_ptr = findPredecessor(curr_node_ptr); // Get the predecessor of the node
			if(pred_node_ptr != nullptr) // pred_node_ptr == nullptr IS IMPOSSIBLE, BUT LETS JUST LEAVE IT
			{
				Node<Key, Value>* temp_ptr = curr_node_ptr; // Keep copy of node ptr for deleting
				changeChild(pred_node_ptr, nullptr); // Update the parent node that the child will be deleted
				pred_node_ptr->setParent(nullptr); // Clear parent of the predecessor
				if(temp_ptr->getParent() == nullptr) // THIS IS THE ROOT NODE
				{
					mRoot = pred_node_ptr; // Make mRoot point to the predecessor which is the current node
					// UPDATE CURRENT NODE
					mRoot->setLeft(temp_ptr->getLeft());
					mRoot->setRight(temp_ptr->getRight());
					// UPDATE SURROUNDING NODES OF CURRENT NODE
					if(mRoot->getLeft() != nullptr) mRoot->getLeft()->setParent(mRoot); // Updates deleted node's left child's parent to the predecessor
					if(mRoot->getRight() != nullptr) mRoot->getRight()->setParent(mRoot); // Updates deleted node's right child's parent to the predecessor
					updateAncestorChainHeights(mRoot); // Updates all the heights in the ancestor chain
				} 
				else 
				{
					// UPDATE CURRENT NODE
					pred_node_ptr->setParent(temp_ptr->getParent());
					pred_node_ptr->setLeft(temp_ptr->getLeft());
					pred_node_ptr->setRight(temp_ptr->getRight());
					// UPDATE SURROUNDING NODES OF CURRENT NODE
					if(temp_ptr->getLeft() != nullptr) temp_ptr->getLeft()->setParent(pred_node_ptr); // Updates current node's left child's parent to the predecessor
					if(temp_ptr->getRight() != nullptr) temp_ptr->getRight()->setParent(pred_node_ptr); // Updates current node's right child's parent to the predecessor
					updateAncestorChainHeights(pred_node_ptr); // Updates all the heights in the ancestor chain
				}
				delete temp_ptr;
				temp_ptr = nullptr;
			}
		}
	}
}

/**
* A method to change current node's Parent's child to the new child after removal of current node
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::changeChild(Node<Key, Value>* curr_node_ptr, Node<Key, Value>* new_child_ptr)
{
	if(curr_node_ptr != nullptr && curr_node_ptr->getParent() != nullptr) // Check first that the node received is not empty 
		//and ensure parent is not empty as well, or else the node is the root node
	{
		if(curr_node_ptr->getKey() < curr_node_ptr->getParent()->getKey()) // Case 1: When current node is the left child of parent
		{
			curr_node_ptr->getParent()->setLeft(new_child_ptr);
		}
		else if(curr_node_ptr->getKey() > curr_node_ptr->getParent()->getKey()) // Case 2: When current node is the right child of parent
		{
			curr_node_ptr->getParent()->setRight(new_child_ptr);
		}
	}
}

/**
* An iterative method to find the predecessor of the given node
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::findPredecessor(Node<Key, Value>* curr_node_ptr)
{
	if(curr_node_ptr != nullptr) // Check first that the node received is not empty
	{
		if(curr_node_ptr->getLeft() != nullptr) // Case 1: If left subtree exists, find the largest element in left subtree
		{
			return getSubTreeMax(curr_node_ptr->getLeft());
		}
		else // Case 2: Left subtree does not exist, recursively find the first left ancestor
		{
			return firstLeftAncestor(curr_node_ptr);
		}
	}
	else 
	{
		return nullptr;
	}
}

/**
* A recursive method to find largest element in subtree
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::getSubTreeMax(Node<Key, Value>* curr_node_ptr) const
{
	if(curr_node_ptr != nullptr) // Check first that the node received is not empty
	{
		if(curr_node_ptr->getRight() != nullptr) // Case 1: We have not reached the right-most node
		{
			return getSubTreeMax(curr_node_ptr->getRight());
		}
		else // Case 2: We have reached the right-most node, hence max is found
		{
			return curr_node_ptr;
		}
	}
	else 
	{
		return nullptr;
	}
}

/**
* A recursive method to find largest element in subtree
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::firstLeftAncestor(Node<Key, Value>* curr_node_ptr)
{
	if(curr_node_ptr != nullptr && curr_node_ptr->getParent() != nullptr) // Check first that the node received is not empty 
		//and ensure parent is not empty as well, or else the node is the root node, with no predecessor
	{
		if(curr_node_ptr->getKey() < curr_node_ptr->getParent()->getKey()) // Case 1: When current node is the left child of parent, 
			//we have to recurse upwards until we have a current node that is the right child of a parent which will be case 2
		{
			return firstLeftAncestor(curr_node_ptr->getParent());
		}
		else // if(curr_node_ptr->getKey() > curr_node_ptr->getParent()->getKey()) // Case 2: When current node is the right child of parent
		{
			return curr_node_ptr->getParent();
		}
	}
	else 
	{
		return nullptr;
	}
}

/**
* A method to remove all contents of the tree and reset the values in the tree 
* for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
	// TODO
	// Post-order traversal to remove all nodes from the tree
	postOrderRemoval(mRoot); // Step 5. O(n), deletes each of n nodes
}

/**
* A method to remove all contents via post order traversal
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::postOrderRemoval(Node<Key, Value>* curr_node_ptr)
{
	if(curr_node_ptr != nullptr) {
		postOrderRemoval(curr_node_ptr->getLeft()); // Recurse on the left subtree
		postOrderRemoval(curr_node_ptr->getRight()); // Recurse on the right subtree
		delete curr_node_ptr; // Delete the node after both the left subtree and right subtree have been deleted
		curr_node_ptr = nullptr;
	} else {
		return;
	}
}

/*
	-------------------------------------------------------------------------------------
	End implementations for the BinarySearchTree class Insertion and Removal functions.
	-------------------------------------------------------------------------------------
*/

/*
	--------------------------------------------------------------------
	Begin implementations for the BinarySearchTree class Find functions.
	--------------------------------------------------------------------
*/

/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::getSmallestNode() const
{
	// TODO
	return getSubTreeMin(mRoot); // Step 7. O(h), recursively go depth of the left subtree to find left most node
}

/**
* A recursive method to find smallest element in subtree
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::getSubTreeMin(Node<Key, Value>* curr_node_ptr) const
{
	if(curr_node_ptr != nullptr) // Check first that the node received is not empty
	{
		if(curr_node_ptr->getLeft() != nullptr) // Case 1: We have not reached the left-most node
		{
			return getSubTreeMin(curr_node_ptr->getLeft());
		}
		else // Case 2: We have reached the left-most node, hence min is found
		{
			return curr_node_ptr;
		}
	}
	else 
	{
		return nullptr;
	}
}

/**
* Helper function to find a node with given key, k and 
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const 
{
	// TODO
	return internalFindHelper(key, mRoot); // Step 6. O(h), traverse half a subtree at any time
}

/**
* Recursive Helper of the Helper function to find a node with given key, k and 
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFindHelper(const Key& key, 
	Node<Key, Value>* curr_node_ptr) const 
{
	if(curr_node_ptr == nullptr) // Case 1: The key does not exist in the BST, return nullptr
	{
		return nullptr;
	}
	else
	{
		if(key > curr_node_ptr->getKey()) // Case 2: The key is greater than the key of our current node
		{
			return internalFindHelper(key, curr_node_ptr->getRight()); 
		}
		else if(key < curr_node_ptr->getKey()) // Case 3: The key is lesser than the key of our current node
		{
			return internalFindHelper(key, curr_node_ptr->getLeft());
		}
		else // if(key == curr_node_ptr->getKey()) // Case 4: The key is equal to the key of our current node
		{
			return curr_node_ptr;
		}
	}
}

/*
	------------------------------------------------------------------
	End implementations for the BinarySearchTree class Find functions.
	------------------------------------------------------------------
*/

/**
* Helper function to print the tree's contents
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::printRoot (Node<Key, Value>* root) const
{
	if (root != NULL)
	{
		std::cout << "[";
		printRoot (root->getLeft());
		std::cout << " (" << root->getKey() << ", " << root->getValue() << ") ";
		printRoot (root->getRight());
		std::cout << "]";
	}
}

/*
	---------------------------------------------------
	End implementations for the BinarySearchTree class.
	---------------------------------------------------
*/

#endif
