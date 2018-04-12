#ifndef ROTATEBST_H
#define ROTATEBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>
#include <vector>
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
	private:
		bool rec_inOrderTraversal(
			Node<Key, Value>* curr_node_ptr, 
			int& pos_intree,
			std::vector<Key>& checking_vec,
			bool(*func)(std::vector<Key>&, Key, int));
		bool addKey(std::vector<Key>& checking_vec, Key the_key, int pos);
		bool checkKey(std::vector<Key>& checking_vec, Key the_key, int pos);
		void changeChild(Node<Key, Value>* curr_node_ptr, Node<Key, Value>* new_child_ptr);
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
	Node<Key, Value>* grandparent_ptr = r->getParent();
	Node<Key, Value>* rightchild_ptr = r->getRight();
	if(rightchild_ptr != nullptr)
	{
		// Step 1. Adjust child
		changeChild(rightchild_ptr, rightchild_ptr->getLeft());

		// Step 2. Adjust grandparent
		if(grandparent_ptr != nullptr) // r is not the root node
		{
			changeChild(r, rightchild_ptr);
			rightchild_ptr->setParent(grandparent_ptr);

			// Step 3. Adjust parent / r
			rightchild_ptr->setLeft(r);
			r->setParent(rightchild_ptr);
		}
		else
		{
			this->mRoot = rightchild_ptr;
			this->mRoot->setParent(nullptr);

			// Step 3. Adjust parent / r
			this->mRoot->setLeft(r);
			r->setParent(this->mRoot);
		}
	}
}

/**
* A method to perform a right rotation at the parameter node. 
* If r has no left child, this function should do nothing. 
* O(1)
*/
template<typename Key, typename Value>
void rotateBST<Key, Value>::rightRotate(Node<Key, Value>* r) // r is the parent
{
	// TODO
	Node<Key, Value>* grandparent_ptr = r->getParent();
	Node<Key, Value>* leftchild_ptr = r->getLeft();
	if(leftchild_ptr != nullptr)
	{
		// Step 1. Adjust child
		changeChild(leftchild_ptr, leftchild_ptr->getRight());

		// Step 2. Adjust grandparent
		if(grandparent_ptr != nullptr) // r is not the root node
		{
			changeChild(r, leftchild_ptr);
			leftchild_ptr->setParent(grandparent_ptr);

			// Step 3. Adjust parent / r
			leftchild_ptr->setRight(r);
			r->setParent(leftchild_ptr);
		}
		else
		{
			this->mRoot = leftchild_ptr;
			this->mRoot->setParent(nullptr);

			// Step 3. Adjust parent / r
			this->mRoot->setRight(r);
			r->setParent(this->mRoot);
		}
	}
}

/**
* A method given another BST, checks that the set of keys in both trees are identical. 
* This should run in O(n) time, where n is the number of nodes in the tree.
*/
template<typename Key, typename Value>
bool rotateBST<Key, Value>::sameKeys(const rotateBST& t2) const
{
	// TODO
	std::vector<Key> checking_vec;
	rec_inOrderTraversal(this->mRoot, 0, checking_vec, addKey);
	return rec_inOrderTraversal(t2.mRoot, 0, checking_vec, checkKey);
}

/**
* A method that uses post-order traversal to carry out a function on each node visited
*/
template<typename Key, typename Value>
bool rotateBST<Key, Value>::rec_inOrderTraversal(
	Node<Key, Value>* curr_node_ptr, 
	int& pos_intree,
	std::vector<Key>& checking_vec,
	bool(*func)(std::vector<Key>&, Key, int))
{
	if(curr_node_ptr != nullptr) 
	{
		rec_inOrderTraversal(curr_node_ptr->getLeft(), pos_intree, checking_vec, (*func)); // Recurse on the left subtree
		pos_intree++;
		return (*func)(checking_vec, curr_node_ptr->getKey(), pos_intree) ? true : false;
		rec_inOrderTraversal(curr_node_ptr->getRight(), pos_intree, checking_vec, (*func)); // Recurse on the right subtree
	} 
	else 
	{
		return true;
	}
}

/**
* A method to add a key into the checking vector
*/
template<typename Key, typename Value>
bool rotateBST<Key, Value>::addKey(std::vector<Key>& checking_vec, Key the_key, int pos)
{
	checking_vec.push_back(the_key);
	return true;
}

/**
* A method to check if the key given equals to the same key in the position specified by pos in checking_vec
*/
template<typename Key, typename Value>
bool rotateBST<Key, Value>::checkKey(std::vector<Key>& checking_vec, Key the_key, int pos)
{
	return (checking_vec[pos] == the_key) ? true : false;
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

/**
* A method to change current node's Parent's child to the new child after removal of current node
*/
template<typename Key, typename Value>
void rotateBST<Key, Value>::changeChild(Node<Key, Value>* curr_node_ptr, Node<Key, Value>* new_child_ptr)
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

/*
	----------------------------------------------
	End implementations for the rotateBST class.
	----------------------------------------------
*/

#endif