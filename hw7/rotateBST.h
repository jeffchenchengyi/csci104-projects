#ifndef ROTATEBST_H
#define ROTATEBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>
#include "bst.h"

/**
* A templated rotatable binary search tree.
*/
template <typename Key, typename Value>
class rotateBST: public BinarySearchTree<Key, Value>
{
	protected:
		void leftRotate(Node<Key, Value>* r); // TODO
		void rightRotate(Node<Key, Value>* r); // TODO
	public:
		bool sameKeys(const rotateBST& t2) const; // TODO
		void transform(rotateBST& t2) const; // TODO
};

/*
	----------------------------------------------
	Begin implementations for the rotateBST class.
	----------------------------------------------
*/

/**
* A method to perform a left rotation at the parameter node. 
* If r has no right child, this function should do nothing. 
* O(1)
*/
template<typename Key, typename Value>
void rotateBST<Key, Value>::leftRotate(Node<Key, Value>* r)
{
	// TODO
	
}

/**
* A method to perform a right rotation at the parameter node. 
* If r has no left child, this function should do nothing. 
* O(1)
*/
template<typename Key, typename Value>
void rotateBST<Key, Value>::rightRotate(Node<Key, Value>* r)
{
	// TODO
	
}

/**
* A method given another BST, checks that the set of keys in both trees are identical. 
* This should run in O(n) time, where n is the number of nodes in the tree.
*/
template<typename Key, typename Value>
bool rotateBST<Key, Value>::sameKeys(const rotateBST& t2) const
{
	// TODO
	return true;
}

/**
* A method given another BST t2, if t2 contains the same keys as the one for this, 
* transform the BST t2 into the one for this using only rotations. 
* If the BST t2 does not have the same keys as this, this function should 
* do nothing and neither BST should be modified.
*/
template<typename Key, typename Value>
void rotateBST<Key, Value>::transform(rotateBST& t2) const
{
	// TODO
	
}

/*
	----------------------------------------------
	End implementations for the rotateBST class.
	----------------------------------------------
*/

#endif