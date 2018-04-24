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
		Node<Key, Value>* it_findPredecessor(Node<Key, Value>* curr_node_ptr);
		Node<Key, Value>* it_getSubTreeMax(Node<Key, Value>* curr_node_ptr) const;
		Node<Key, Value>* it_firstLeftAncestor(Node<Key, Value>* curr_node_ptr);
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
		if(result.first != nullptr) // Case 2a: We are inserting a normal node into the splay tree
		{
			this->BinarySearchTree<Key, Value>::insert(keyValuePair);
			if(result.first->getRight() != nullptr
				&& result.first->getLeft() != nullptr) // Last visited node has two children
			{

				if(result.first->getRight()->getKey() == keyValuePair.first) // When key is last visited node's right child
				{
					splay(result.first->getRight());
				}
				else if(result.first->getLeft()->getKey() == keyValuePair.first) // When key is last visited node's left child
				{
					splay(result.first->getLeft());
				}
				else
				{

				}
			}
			else if(result.first->getRight() != nullptr
				&& result.first->getLeft() == nullptr) // Last visited node has right child only
			{
				if(result.first->getRight()->getKey() == keyValuePair.first) // When key is last visited node's right child
				{
					splay(result.first->getRight());
				}
				else
				{

				}
			}
			else if(result.first->getRight() == nullptr
				&& result.first->getLeft() != nullptr) // Last visited node has left child only
			{
				if(result.first->getLeft()->getKey() == keyValuePair.first) // When key is last visited node's left child
				{
					splay(result.first->getLeft());
				}
				else
				{

				}
			}
			else // THIS IS IMPOSSIBLE
			{

			}
		}
		else // Case 2b: We are inserting the root node
		{
			this->BinarySearchTree<Key, Value>::insert(keyValuePair);
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
		if(result.first->getLeft() != nullptr
			&& result.first->getRight() != nullptr) // Case 1a: Special case when we need to splay parent of predecessor after removal
		{
			Node<Key, Value>* pred_node_ptr = it_findPredecessor(result.first); // Get the predecessor
			Node<Key, Value>* parent_of_pred_parent_node_ptr = nullptr;
			if(pred_node_ptr != nullptr) // Get the predecessor's parent, because thats the node you gonna splay after deletion
			{
				if(pred_node_ptr->getParent() != nullptr) 
				{
					parent_of_pred_parent_node_ptr = pred_node_ptr->getParent()->getParent();
					if(parent_of_pred_parent_node_ptr != nullptr)
					{
						if(isRightChild(pred_node_ptr->getParent()))
						{
							if(parent_of_pred_parent_node_ptr != result.first)
							{
								this->BinarySearchTree<Key, Value>::remove(key);
								if(parent_of_pred_parent_node_ptr->getRight() != nullptr)
								{
									splay(parent_of_pred_parent_node_ptr->getRight()); // Splay parent of deleted node which was predecessor's new parent
								}
							}
							else
							// *THIS CASE IS IMPOSSIBLE I THINK*
							{
								std::cerr << "wtf i didnt know this case was even possible" << std::endl;
								this->BinarySearchTree<Key, Value>::remove(key);
								splay(pred_node_ptr->getRight());
							}
						}
						else
						{
							if(parent_of_pred_parent_node_ptr != result.first)
							{
								this->BinarySearchTree<Key, Value>::remove(key);
								if(parent_of_pred_parent_node_ptr->getLeft() != nullptr)
								{
									splay(parent_of_pred_parent_node_ptr->getLeft()); // Splay parent of deleted node which was predecessor's new parent
								}
							}
							else
							/** 
							* *CAUTION* VERY VERY SPECIAL CASE: Remove 7
							*			  :
							*			  :
							*			[07]	 [07] is both the parent of parent of node to be deleted and the node to be deleted
							*			/	\
							*		[03]	[09] [03] is the pred_node_ptr->getRight() after the removal
							*		/	\	
							*	[01]	[05]	 [05] is the position to delete 07 as it is the predecessor, [07]'s position will be overidded by [05]
							*			/
							*		[04]
							*/
							{
								this->BinarySearchTree<Key, Value>::remove(key);
								splay(pred_node_ptr->getLeft());
							}
						}
					}
					else // THIS WOULD MEAN PREDECESSOR'S PARENT IS ALREADY THE ROOT NODE, NO NEED FOR SPLAYING AFTER DELETION
					{
						this->BinarySearchTree<Key, Value>::remove(key);
					}
				}
				else // THIS WOULD MEAN THAT PREDECESSOR IS THE ROOT, WHICH IS IMPOSSIBLE IF NODE TO BE REMOVED HAS TWO CHILDREN, AS PREDECESSOR WOULD BE IN LEFT SUBTREE
				{

				}
			}
			else // THIS IS IMPOSSIBLE, IF A NODE HAS BOTH CHILDREN, IT MUST HAVE A PREDECESSOR
			{

			}
		}
		else // Case 1b: When only one child or no child exists for the node to be deleted
		{
			Node<Key, Value>* parent_ptr = result.first->getParent();
			this->BinarySearchTree<Key, Value>::remove(key);
			if(parent_ptr != nullptr) // Case 1ba: The tree is not empty
			{
				splay(parent_ptr);
			}
			else // Case 1bb: The tree is empty, no splaying
			{

			}
		}
	}
	else // Case 2: Key was not found
	{
		if(result.first != nullptr) // Case 2a: The tree is not empty
		{
			splay(result.first);
		}
		else // Case 2b: The tree is empty, no splaying
		{

		}
	}
}

/**
* An iterative method to find the predecessor of the given node
*/
template<typename Key, typename Value>
Node<Key, Value>* SplayTree<Key, Value>::it_findPredecessor(Node<Key, Value>* curr_node_ptr)
{
	if(curr_node_ptr != nullptr) // Check first that the node received is not empty
	{
		if(curr_node_ptr->getLeft() != nullptr) // Case 1: If left subtree exists, find the largest element in left subtree
		{
			return it_getSubTreeMax(curr_node_ptr->getLeft());
		}
		else // Case 2: Left subtree does not exist, recursively find the first left ancestor
		{
			return it_firstLeftAncestor(curr_node_ptr);
		}
	}
	else 
	{
		return nullptr;
	}
}

/**
* An iterative method to find largest element in subtree
*/
template<typename Key, typename Value>
Node<Key, Value>* SplayTree<Key, Value>::it_getSubTreeMax(Node<Key, Value>* curr_node_ptr) const
{
	while(curr_node_ptr != nullptr) // Check first that the node received is not empty
	{
		if(curr_node_ptr->getRight() != nullptr) // Case 1: We have not reached the right-most node
		{
			curr_node_ptr = curr_node_ptr->getRight();
		}
		else // Case 2: We have reached the right-most node, hence max is found
		{
			return curr_node_ptr;
		}
	}
	return nullptr;
}

/**
* An iterative method to find the predecessor that is the first left ancestor 
*/
template<typename Key, typename Value>
Node<Key, Value>* SplayTree<Key, Value>::it_firstLeftAncestor(Node<Key, Value>* curr_node_ptr)
{
	while(curr_node_ptr != nullptr && curr_node_ptr->getParent() != nullptr) // Check first that the node received is not empty 
		//and ensure parent is not empty as well, or else the node is the root node, with no predecessor
	{
		if(curr_node_ptr->getKey() < curr_node_ptr->getParent()->getKey()) // Case 1: When current node is the left child of parent, 
			//we have to recurse upwards until we have a current node that is the right child of a parent which will be case 2
		{
			curr_node_ptr = curr_node_ptr->getParent();
		}
		else // if(curr_node_ptr->getKey() > curr_node_ptr->getParent()->getKey()) // Case 2: When current node is the right child of parent
		{
			return curr_node_ptr->getParent();
		}
	}
	return nullptr;
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
		if(result.first != nullptr) // Case 2a: The tree is not empty
		{
			splay(result.first);
		}
		else // Case 2b: The tree is empty, no splaying
		{

		}
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
		else
		{
			break;
		}
	}
	// Case 2: We have reached the left-most node, hence min is found
	if(this->mRoot != nullptr) // Case 2a: Tree is not empty
	{
		splay(last_visited_node_ptr);
		typename SplayTree<Key, Value>::iterator it(this->mRoot);
		return it;
	}
	else // Case 2b: Tree is empty
	{
		return this->end();
	}
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
		else
		{
			break;
		}
	}
	// Case 2: We have reached the right-most node, hence max is found
	if(this->mRoot != nullptr) // Case 2a: Tree is not empty
	{
		splay(last_visited_node_ptr);
		typename SplayTree<Key, Value>::iterator it(this->mRoot);
		return it;
	}
	else // Case 2b: Tree is empty
	{
		return this->end();
	}
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
		else // Case 2: We have reached the left-most node, does it have children?
		{
			if(curr_node_ptr->getRight() != nullptr) // Case 2a: The current node has a right child, let's check if the right-child has children
			{
				curr_node_ptr = curr_node_ptr->getRight();
			}
			else // Case 2b: The current node has no children, therefore is the min leaf node
			{

			}
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
		else // Case 2: We have reached the right-most node, does it have children?
		{
			if(curr_node_ptr->getLeft() != nullptr) // Case 2a: The current node has a left child, let's check if the left-child has children
			{
				curr_node_ptr = curr_node_ptr->getLeft();
			}
			else // Case 2b: The current node has no children, therefore is the max leaf node
			{

			}
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
				*					[03] r
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
				*			[02] r
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
				*			[02] r
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
				*	[01] r
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
			*			[02] r
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
			*	[01] r
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