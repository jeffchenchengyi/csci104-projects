#ifndef SPLAYTREE_H
#define SPLAYTREE_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>
#include <vector>
#include "bst.h"
#include "rotateBST.h"

/**
* A templated splay tree.
*/
template <typename Key, typename Value>
class SplayTree: public rotateBST<Key, Value>
{
	public:
		SplayTree(); // TODO
		void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
		void remove(const Key& key); // TODO
		typename SplayTree<Key, Value>::iterator find(const Key& key); // TODO
		typename SplayTree<Key, Value>::iterator findMin(); // TODO
		typename SplayTree<Key, Value>::iterator findMax(); // TODO
		void deleteMinLeaf(); // TODO
		void deleteMaxLeaf(); // TODO
	protected:
		void splay(Node<Key, Value> *r); // TODO
	private:
		// Member functions:
		std::pair< Node<Key, Value>*, bool > findHelper(const Key& key);
		bool isRightChild(Node<Key, Value>* curr_node_ptr);
};

/*
	----------------------------------------------
	Begin implementations for the SplayTree class.
	----------------------------------------------
*/

/**
* A constructor
*/
template<typename Key, typename Value>
SplayTree<Key, Value>::SplayTree()
{
	// TODO
}

/**
* This function will insert a new node into the tree with the specified key and value. 
* The node that has just been inserted is splayed to the root. 
* If a node with this key already exists, don't insert anything, but splay the node to the root.
*/
template<typename Key, typename Value>
void SplayTree<Key, Value>::insert(const std::pair<const Key, Value>& keyValuePair)
{
	// TODO
	std::pair< Node<Key, Value>*, bool > result = findHelper(keyValuePair.first);
	if(result.second) // Case 1: Key was found
	{
		splay(result.first);
	}
	else // Case 2: Key was not found
	{
		BinarySearchTree<Key, Value>::insert(keyValuePair);
		if(result.first->getRight() != nullptr
			&& result.first->getRight()->getKey() == keyValuePair.first) // When key is last visited node's right child
		{
			splay(result.first->getRight());
		}
		else if(result.first->getLeft() != nullptr
			&& result.first->getLeft()->getKey() == keyValuePair.first) // When key is last visited node's right child
		{
			splay(result.first->getLeft());
		}
		else // THIS IS IMPOSSIBLE
		{

		}
	}
}

/**
* This function will first find a node with the specified key in the tree. 
* This function should call BST remove, and then splay the parent of the deleted node to root. 
* (This is different and less complicated than method given in Sandra's lecture, but works well given the inheritance hierarchy.) 
* If the key is not already in the tree, then don't remove anything, but splay the last node visited to the root.
*/
template<typename Key, typename Value>
void SplayTree<Key, Value>::remove(const Key& key)
{
	// TODO
	std::pair< Node<Key, Value>*, bool > result = findHelper(key);
	if(result.second) // Case 1: Key was found
	{
		Node<Key, Value>* parent_ptr = result.first->getParent();
		BinarySearchTree<Key, Value>::remove(key);
		splay(parent_ptr);
	}
	else // Case 2: Key was not found
	{
		splay(result.first);
	}
}

/**
* This function should splay the node with the specified key to the root, and return an iterator to that item. 
* If the key is not found, splay the last visited node to the root, and return the end iterator.
*/
template<typename Key, typename Value>
typename SplayTree<Key, Value>::iterator SplayTree<Key, Value>::find(const Key& key)
{
	// TODO
	std::pair< Node<Key, Value>*, bool > result = findHelper(key);
	if(result.second) // Case 1: Key was found
	{
		splay(result.first);
		typename SplayTree<Key, Value>::iterator it(this->mRoot);
		return it;
	}
	else // Case 2: Key not found, pointer to last visited item received
	{
		splay(result.first);
		return this->end();
	}
}

/**
* This function finds the key, if found, will return a pair with pointer to the item and true as second value,
* if not found, will return pointer to last visited item with a second value of false
*/
template<typename Key, typename Value>
std::pair< Node<Key, Value>*, bool > SplayTree<Key, Value>::findHelper(const Key& key)
{
	Node<Key, Value>* curr_node_ptr = this->mRoot;
	Node<Key, Value>* last_visited_node_ptr = nullptr;
	while(curr_node_ptr != nullptr) // Trying to find the key
	{
		last_visited_node_ptr = curr_node_ptr;
		if(key > curr_node_ptr->getKey()) // Case 2: The key is greater than the key of our current node
		{
			curr_node_ptr = curr_node_ptr->getRight(); 
		}
		else if(key < curr_node_ptr->getKey()) // Case 3: The key is lesser than the key of our current node
		{
			curr_node_ptr = curr_node_ptr->getLeft();
		}
		else // if(key == curr_node_ptr->getKey()) // Case 4: The key is equal to the key of our current node
		{
			return std::make_pair(curr_node_ptr, true);
		}
	}
	return std::make_pair(last_visited_node_ptr, false); // Case 1: The key does not exist, return pair of last visited node pointer and false value
}

/**
* This function finds the node with the minimum key value and splays it to the root. 
* Returns an iterator to the item with the minimum value key.
*/
template<typename Key, typename Value>
typename SplayTree<Key, Value>::iterator SplayTree<Key, Value>::findMin()
{
	// TODO
	Node<Key, Value>* curr_node_ptr = this->mRoot;
	Node<Key, Value>* last_visited_node_ptr = nullptr;
	while(curr_node_ptr != nullptr) // Check first that the node received is not empty
	{
		last_visited_node_ptr = curr_node_ptr;
		if(curr_node_ptr->getLeft() != nullptr) // Case 1: We have not reached the left-most node
		{
			curr_node_ptr = curr_node_ptr->getLeft();
		}
	}
	// Case 2: We have reached the left-most node, hence min is found
	typename SplayTree<Key, Value>::iterator it(last_visited_node_ptr);
	return it;
}

/**
* This function finds the node with the maximum key value and splays it to the root. 
* Returns an iterator to the item with the maximum value key.
*/
template<typename Key, typename Value>
typename SplayTree<Key, Value>::iterator SplayTree<Key, Value>::findMax()
{
	// TODO
	Node<Key, Value>* curr_node_ptr = this->mRoot;
	Node<Key, Value>* last_visited_node_ptr = nullptr;
	while(curr_node_ptr != nullptr) // Check first that the node received is not empty
	{
		last_visited_node_ptr = curr_node_ptr;
		if(curr_node_ptr->getRight() != nullptr) // Case 1: We have not reached the right-most node
		{
			curr_node_ptr = curr_node_ptr->getRight();
		}
	}
	// Case 2: We have reached the right-most node, hence max is found
	typename SplayTree<Key, Value>::iterator it(last_visited_node_ptr);
	return it;
}

/**
* This function deletes the leaf with minimum key value, exactly as if you had called the remove function.
*/
template<typename Key, typename Value>
void SplayTree<Key, Value>::deleteMinLeaf()
{
	// TODO
	Node<Key, Value>* curr_node_ptr = this->mRoot;
	Node<Key, Value>* to_be_removed_node_ptr = nullptr;
	while(curr_node_ptr != nullptr) // Check first that the node received is not empty
	{
		to_be_removed_node_ptr = curr_node_ptr;
		if(curr_node_ptr->getLeft() != nullptr) // Case 1: We have not reached the left-most node
		{
			curr_node_ptr = curr_node_ptr->getLeft();
		}
	}
	if(to_be_removed_node_ptr != nullptr)
	{
		Node<Key, Value>* to_be_removed_parent_node_ptr = to_be_removed_node_ptr->getParent(); // Remember the parent of node to be removed
		BinarySearchTree<Key, Value>::remove(to_be_removed_node_ptr->getKey());
		splay(to_be_removed_parent_node_ptr); // Splay the parent of the removed node
	}
	else // THIS IS IMPOSSIBLE
	{

	}
}

/**
* This function deletes the leaf with maximum key value, exactly as if you had called the remove function.
*/
template<typename Key, typename Value>
void SplayTree<Key, Value>::deleteMaxLeaf()
{
	// TODO
	Node<Key, Value>* curr_node_ptr = this->mRoot;
	Node<Key, Value>* to_be_removed_node_ptr = nullptr;
	while(curr_node_ptr != nullptr) // Check first that the node received is not empty
	{
		to_be_removed_node_ptr = curr_node_ptr;
		if(curr_node_ptr->getRight() != nullptr) // Case 1: We have not reached the right-most node
		{
			curr_node_ptr = curr_node_ptr->getRight();
		}
	}
	if(to_be_removed_node_ptr != nullptr)
	{
		Node<Key, Value>* to_be_removed_parent_node_ptr = to_be_removed_node_ptr->getParent(); // Remember the parent of node to be removed
		BinarySearchTree<Key, Value>::remove(to_be_removed_node_ptr->getKey());
		splay(to_be_removed_parent_node_ptr); // Splay the parent of the removed node
	}
	else // THIS IS IMPOSSIBLE
	{

	}
}

/**
* This function splays a given node to the root of the splayTree.
*/
template<typename Key, typename Value>
void SplayTree<Key, Value>::splay(Node<Key, Value> *r)
{
	// TODO
	if(r != nullptr) // Safety check that r is not a nullptr
	{
		Node<Key, Value>* parent_ptr = nullptr;
		Node<Key, Value>* grandparent_ptr = nullptr;
		parent_ptr = r->getParent();
		if(parent_ptr != nullptr) 
		{
			grandparent_ptr = parent_ptr->getParent();
		}
		if(parent_ptr != nullptr 
			&& grandparent_ptr != nullptr) // Case 1: Both parent and grandparent of current node exists
		{
			if(isRightChild(parent_ptr))
			{
				if(isRightChild(r)) 
				/** 
				* Case 1a: Zag-Zag pattern
				*			[01] grandparent_ptr
				*				\
				*				[02] parent_ptr
				*					\
				*					[03] curr_node_ptr
				*/
				{		
					this->leftRotate(grandparent_ptr);
					this->leftRotate(parent_ptr);
				}
				else
				/** 
				* Case 1b: Zag-Zig pattern
				*			[01] grandparent_ptr
				*				\
				*				[03] parent_ptr
				*				/
				*			[02] curr_node_ptr
				*/
				{
					this->rightRotate(parent_ptr);
					this->leftRotate(grandparent_ptr);
				}
			}
			else
			{
				if(isRightChild(r))
				/** 
				* Case 1c: Zig-Zag pattern
				*			[03] grandparent_ptr
				*			/
				*		[01] parent_ptr
				*			\
				*			[02] curr_node_ptr
				*/
				{
					this->leftRotate(parent_ptr);
					this->rightRotate(grandparent_ptr);
				}
				else
				/**
				* Case 1d: Zig-Zig pattern
				*			[03] grandparent_ptr
				*			/
				*		[02] parent_ptr
				*		/
				*	[01] curr_node_ptr
				*/
				{
					this->rightRotate(grandparent_ptr);
					this->rightRotate(parent_ptr);
				}
			}
			splay(r); // Recursively splay on the new ancestor chain
		}
		else if(parent_ptr != nullptr
			&& grandparent_ptr == nullptr) // Case 2: Parent is the root node
		{
			if(isRightChild(r))
			/**
			* Case 2a: Zag pattern
			*		mRoot
			*		  |
			*		  v	
			*		[01] parent_ptr
			*			\
			*			[02] curr_node_ptr
			*/
			{
				this->leftRotate(parent_ptr);
			}
			else
			/** 
			* Case 2b: Zig pattern
			*		mRoot
			*		  |
			*		  v	
			*		[02] parent_ptr
			*		/
			*	[01] curr_node_ptr
			*/
			{
				this->rightRotate(parent_ptr);
			}
		}
		else // Case 3: Current node is already the root node, do nothing
		{
			return;
		}
	}
}

/**
* This function returns true if the current node is a right child,
* false if it is a left child
*/
template<typename Key, typename Value>
bool SplayTree<Key, Value>::isRightChild(Node<Key, Value>* curr_node_ptr)
{
	if(curr_node_ptr != nullptr)
	{
		if(curr_node_ptr->getParent() != nullptr)
		{
			return (curr_node_ptr->getParent()->getKey() < curr_node_ptr->getKey());
		}
	}
	return false; // Default return bool, before calling this, we should ensure that curr_nod_ptr is not nullptr
}

/*
	----------------------------------------------
	End implementations for the SplayTree class.
	----------------------------------------------
*/

#endif