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
}

/**
* This function should splay the node with the specified key to the root, and return an iterator to that item. 
* If the key is not found, splay the last visited node to the root, and return the end iterator.
*/
template<typename Key, typename Value>
typename SplayTree<Key, Value>::iterator find(const Key& key)
{
	// TODO
}

/**
* This function finds the node with the minimum key value and splays it to the root. 
* Returns an iterator to the item with the minimum value key.
*/
template<typename Key, typename Value>
typename SplayTree<Key, Value>::iterator findMin()
{
	// TODO
}

/**
* This function finds the node with the maximum key value and splays it to the root. 
* Returns an iterator to the item with the maximum value key.
*/
template<typename Key, typename Value>
typename SplayTree<Key, Value>::iterator findMax()
{
	// TODO
}

/**
* This function deletes the leaf with minimum key value, exactly as if you had called the remove function.
*/
template<typename Key, typename Value>
void SplayTree<Key, Value>::deleteMinLeaf()
{
	// TODO
}

/**
* This function deletes the leaf with maximum key value, exactly as if you had called the remove function.
*/
template<typename Key, typename Value>
void SplayTree<Key, Value>::void deleteMaxLeaf()
{
	// TODO
}

/**
* This function splays a given node to the root of the splayTree.
*/
template<typename Key, typename Value>
void SplayTree<Key, Value>::splay(Node<Key, Value> *r)
{
	// TODO
}

/*
	----------------------------------------------
	End implementations for the SplayTree class.
	----------------------------------------------
*/

#endif