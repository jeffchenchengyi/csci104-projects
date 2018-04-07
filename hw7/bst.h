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
		~BinarySearchTree(); //TODO
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
		bool isBalancedHelper(const Node<Key, Value>* curr_node_ptr) const;
		Node<Key, Value>* internalFindHelper(const Key& key, const Node<Key, Value>* curr_node_ptr) const; 
		void insertHelper(const std::pair<const Key, Value>& keyValuePair,
			Node<Key, Value>* curr_node_ptr,
			Node<Key, Value>* parent_ptr);
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
	// TODO
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree() 
{ 
	// TODO
	clear();
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

/**
* An method to return the height of the BST.
*/
template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::height()
{
	// TODO
	return mRoot->getHeight();	// Step 1. O(1)
}


/**
* An method to checks if the BST is balanced. This method returns true if and only if the BST is balanced.
*/
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced()
{
	// TODO
	return isBalancedHelper(mRoot);
}

/**
* A helper method to recursively checks if the BST is balanced. 
* This method returns true if and only if the BST is balanced.
*/
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalancedHelper(const Node<Key, Value>* curr_node_ptr) const
{
	if(curr_node_ptr == nullptr) // Case 1: When curr_node is null, tree is balanced (leaves and empty tree)
	{
		return true;
	} 
	else 
	{
		if(mRoot->getLeft() != nullptr 
			&& mRoot->getRight() != nullptr) // Case 2: When node has both children sub-trees
		{
			if(abs(mRoot->getLeft()->getHeight() 
				- mRoot->getRight()->getHeight()) <= 1) {
				return (isBalanced(mRoot->getLeft()) && isBalanced(mRoot->getRight()));
			} else {
				return false;
			}
		} 
		else if(mRoot->getLeft() == nullptr 
			&& mRoot->getRight() != nullptr) // Case 3: When node has right-child sub-tree
		{
			if(mRoot->getRight()->getHeight() == 1) {
				return true;
			} else {
				return false;
			}
		}
		else if(mRoot->getLeft() != nullptr 
			&& mRoot->getRight() == nullptr) // Case 4: When node has left-child sub-tree
		{
			if(mRoot->getLeft()->getHeight() == 1) {
				return true;
			} else {
				return false;
			}
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
		insertHelper(keyValuePair, mRoot, nullptr);
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
		curr_node_ptr = new Node(keyValuePair.first, keyValuePair.second, parent_ptr);
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
	removeHelper(key, internalFind(key));
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
			delete curr_node_ptr;
			curr_node_ptr = nullptr;
		}
		else if(curr_node_ptr->getLeft() != nullptr 
			&& curr_node_ptr->getRight() == nullptr) // Case 2: Only left child exists
		{
			Node<Key, Value>* temp_ptr = curr_node_ptr;
			curr_node_ptr = curr_node_ptr->getLeft(); // Make current node point to current node's left child
			curr_node_ptr->setParent(temp_ptr->getParent()); // Set current node's parent to prev current node's parent
			delete temp_ptr;
			temp_ptr = nullptr;
		}
		else if(curr_node_ptr->getLeft() == nullptr 
			&& curr_node_ptr->getRight() != nullptr) // Case 3: Only right child exists
		{
			Node<Key, Value>* temp_ptr = curr_node_ptr;
			curr_node_ptr = curr_node_ptr->getRight(); // Make current node point to current node's right child
			curr_node_ptr->setParent(temp_ptr->getParent()); // Set current node's parent to prev current node's parent
			delete temp_ptr;
			temp_ptr = nullptr;
		}
		else if(curr_node_ptr->getLeft() != nullptr 
			&& curr_node_ptr->getRight() != nullptr) // Case 4: Both children exist, we need to replace current node with its predecessor
		{
			Node<Key, Value>* pred_node_ptr = findPredecessor(curr_node_ptr);
			curr_node_ptr-> //TO BE COMPLETED
		}
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
}

/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::getSmallestNode() const
{
	// TODO
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
	return internalFindHelper(key, mRoot);
}

/**
* Recursive Helper of the Helper function to find a node with given key, k and 
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFindHelper(const Key& key, 
	const Node<Key, Value>* curr_node_ptr) const 
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
		else if(key == curr_node_ptr->getKey()) // Case 4: The key is equal to the key of our current node
		{
			return curr_node_ptr;
		}
	}
}

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
