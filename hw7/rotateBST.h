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
		// Member functions:
		void rec_inOrderAddKey(Node<Key, Value>* curr_node_ptr, std::vector<Key>& checking_vec) const;
		bool rec_inOrderCheckKey(
			Node<Key, Value>* curr_node_ptr, 
			int& pos_intree,
			std::vector<Key>& checking_vec) const;
		void rec_transformToLL(
			rotateBST& t2,
			Node<Key, Value>* curr_node_ptr) const;
		void rec_transformRoot(
			rotateBST& t2,
			Node<Key, Value>* curr_node_ptr, 
			Node<Key, Value>* model_node_ptr) const;
		void rec_transformSubTree(
			rotateBST& t2,
			Node<Key, Value>* curr_node_ptr, 
			Node<Key, Value>* model_node_ptr) const;
		void rec_postOrderUpdateHeights(
			Node<Key, Value>* curr_node_ptr) const;
		void updateParentHeight(
			Node<Key, Value>* curr_node_ptr) const;
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
	if(rightchild_ptr != nullptr 
		&& grandparent_ptr != nullptr)
	{
		// Step 1. Adjust child
		changeChild(rightchild_ptr, rightchild_ptr->getLeft());
		if(r->getRight() != nullptr)
		{
			r->getRight()->setParent(r);
		}

		// Step 2. Adjust grandparent
		changeChild(r, rightchild_ptr);
		rightchild_ptr->setParent(grandparent_ptr);

		// Step 3. Adjust parent / r
		rightchild_ptr->setLeft(r);
		r->setParent(rightchild_ptr);
	}
	else if(rightchild_ptr == nullptr 
		&& grandparent_ptr != nullptr) // r is not the root node and has no right child
	{
		// Do not do anything
	}
	else if(rightchild_ptr != nullptr 
		&& grandparent_ptr == nullptr) // r is the root node and has right child
	{
		// Step 1. Adjust child
		r->setRight(rightchild_ptr->getLeft());
		if(r->getRight() != nullptr)
		{
			r->getRight()->setParent(r);
		}

		this->mRoot = rightchild_ptr;
		this->mRoot->setParent(nullptr);

		// Step 3. Adjust parent / r
		this->mRoot->setLeft(r);
		this->mRoot->getLeft()->setParent(this->mRoot);
	}
	else // r is the root node and has not right child
	{
		// Do not do anything
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
	if(leftchild_ptr != nullptr 
		&& grandparent_ptr != nullptr)
	{
		// Step 1. Adjust child
		changeChild(leftchild_ptr, leftchild_ptr->getRight());
		if(r->getLeft() != nullptr)
		{
			r->getLeft()->setParent(r);
		}

		// Step 2. Adjust grandparent
		changeChild(r, leftchild_ptr);
		leftchild_ptr->setParent(grandparent_ptr);

		// Step 3. Adjust parent / r
		leftchild_ptr->setRight(r);
		r->setParent(leftchild_ptr);
	}
	else if(leftchild_ptr == nullptr 
		&& grandparent_ptr != nullptr) // r is not the root node and has no left child
	{
		// Do not do anything
	}
	else if(leftchild_ptr != nullptr 
		&& grandparent_ptr == nullptr) // r is the root node and has left child
	{
		// Step 1. Adjust child
		r->setLeft(leftchild_ptr->getRight());
		if(r->getLeft() != nullptr)
		{
			r->getLeft()->setParent(r);
		}

		this->mRoot = leftchild_ptr;
		this->mRoot->setParent(nullptr);

		// Step 3. Adjust parent / r
		this->mRoot->setRight(r);
		this->mRoot->getRight()->setParent(this->mRoot);
	}
	else // r is the root node and has not left child
	{
		// Do not do anything
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
	int pos_intree = 0;
	std::vector<Key> checking_vec;
	rec_inOrderAddKey(this->mRoot, checking_vec); // O(n)
	return rec_inOrderCheckKey(t2.mRoot, pos_intree, checking_vec); // O(n)
}

/**
* A method that uses recursive in-order traversal to add each key in tree to checking_vec
*/
template<typename Key, typename Value>
void rotateBST<Key, Value>::rec_inOrderAddKey(
	Node<Key, Value>* curr_node_ptr, 
	std::vector<Key>& checking_vec) const
{
	if(curr_node_ptr != nullptr) 
	{
		rec_inOrderAddKey(curr_node_ptr->getLeft(), checking_vec); // Recurse on the left subtree
		checking_vec.push_back(curr_node_ptr->getKey());
		rec_inOrderAddKey(curr_node_ptr->getRight(), checking_vec); // Recurse on the right subtree
	}
}

/**
* A method that uses recursive in-order traversal to check each key in tree to checking_vec
*/
template<typename Key, typename Value>
bool rotateBST<Key, Value>::rec_inOrderCheckKey(
	Node<Key, Value>* curr_node_ptr, 
	int& pos_intree,
	std::vector<Key>& checking_vec) const
{
	if(curr_node_ptr != nullptr) 
	{
		if(rec_inOrderCheckKey(curr_node_ptr->getLeft(), pos_intree, checking_vec)) // Recurse on the left subtree
		{
			if(checking_vec[pos_intree] != curr_node_ptr->getKey()) 
			{
				return false;
			}
			else
			{
				pos_intree++;
				if(rec_inOrderCheckKey(curr_node_ptr->getRight(), pos_intree, checking_vec)) // Recurse on the right subtree
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		}
		else
		{
			return false;
		}
	}
	else
	{
		return true;
	}
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
	if(this->sameKeys(t2) == true)
	{
		// 3. This should produce a tree which is effectively a linked list.
		// 1. Perform right rotations on the root node of t2 until it has no left child.
		while(t2.mRoot->getLeft() != nullptr)
		{
			t2.rightRotate(t2.mRoot);
		}
		rec_transformToLL(t2, t2.mRoot->getRight());

		// 6. This should produce the specified tree using only rotations.
		rec_transformRoot(t2, t2.mRoot, this->mRoot);

		// 5. Recursively do rotations on the left child and the right child until they match the node at that position of this.
		rec_transformSubTree(t2, t2.mRoot->getLeft(), this->mRoot->getLeft());
		rec_transformSubTree(t2, t2.mRoot->getRight(), this->mRoot->getRight());

		// Update all the height values 
		rec_postOrderUpdateHeights(t2.mRoot);
	}
}

/**
* A method that recursively transforms a binary tree to a linked list
*/
template<typename Key, typename Value>
void rotateBST<Key, Value>::rec_transformToLL(
	rotateBST& t2,
	Node<Key, Value>* curr_node_ptr) const
{
	if(curr_node_ptr != nullptr)
	{
		Node<Key, Value>* parent_ptr = curr_node_ptr->getParent();
		while(parent_ptr->getRight()->getLeft() != nullptr)
		{
			t2.rightRotate(parent_ptr->getRight());
		}
		// 2. Recursively move to the right child and repeat the above operation.
		rec_transformToLL(t2, parent_ptr->getRight()->getRight());
	} 
	else
	{
		return;
	}
}

/**
* A method that recursively transforms a linked list to the tree given by model_node_ptr which represents root node
* of model tree
*/
template<typename Key, typename Value>
void rotateBST<Key, Value>::rec_transformRoot(
	rotateBST& t2,
	Node<Key, Value>* curr_node_ptr, 
	Node<Key, Value>* model_node_ptr) const
{
	if(curr_node_ptr != nullptr && model_node_ptr != nullptr)
	{
		// 4. Now perform left rotations on the root node of t2, until the root of t2 is the same as the root of this.
		while(curr_node_ptr->getKey() != model_node_ptr->getKey())
		{
			t2.leftRotate(curr_node_ptr);
			curr_node_ptr = curr_node_ptr->getParent();
		}
	}
}

template<typename Key, typename Value>
void rotateBST<Key, Value>::rec_transformSubTree(
	rotateBST& t2,
	Node<Key, Value>* curr_node_ptr, 
	Node<Key, Value>* model_node_ptr) const
{
	if(curr_node_ptr != nullptr && model_node_ptr != nullptr)
	{
		// 4. Now perform left rotations on the root node of t2, until the root of t2 is the same as the root of this.
		while(curr_node_ptr->getKey() != model_node_ptr->getKey())
		{
			if(curr_node_ptr->getKey() > model_node_ptr->getKey())
			{
				t2.rightRotate(curr_node_ptr);
				curr_node_ptr = curr_node_ptr->getParent();
			}
			else
			{
				t2.leftRotate(curr_node_ptr);
				curr_node_ptr = curr_node_ptr->getParent();
			}
		}
		// 5. Recursively do rotations on the left child and the right child until they match the node at that position of this.
		rec_transformSubTree(t2, curr_node_ptr->getLeft(), model_node_ptr->getLeft());
		rec_transformSubTree(t2, curr_node_ptr->getRight(), model_node_ptr->getRight());
	}
}

/**
* A method that uses recursive post-order traversal to update heights of the tree
*/
template<typename Key, typename Value>
void rotateBST<Key, Value>::rec_postOrderUpdateHeights(
	Node<Key, Value>* curr_node_ptr) const
{
	if(curr_node_ptr != nullptr) 
	{
		rec_postOrderUpdateHeights(curr_node_ptr->getLeft()); // Recurse on the left subtree
		rec_postOrderUpdateHeights(curr_node_ptr->getRight()); // Recurse on the right subtree
		updateParentHeight(curr_node_ptr);
	}
	else
	{
		return;
	}
}

/**
* A method to check if the parent's heights need to be adjusted
*/
template<typename Key, typename Value>
void rotateBST<Key, Value>::updateParentHeight(
	Node<Key, Value>* curr_node_ptr) const
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
	else // Case 4: When node is a leaf node or root node with no children
	{
		curr_node_ptr->setHeight(1);
	}
}

/**
* A method to change current node's Parent's child to the new child after removal of current node
*/
template<typename Key, typename Value>
void rotateBST<Key, Value>::changeChild(
	Node<Key, Value>* curr_node_ptr, 
	Node<Key, Value>* new_child_ptr)
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