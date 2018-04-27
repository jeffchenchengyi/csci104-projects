#ifndef CACHELRU_H
#define CACHELRU_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>
#include <vector>
#include "bst.h"
#include "rotateBST.h"
#include "splayTree.h"

/**
* A templated cacheLRU class that uses the SplayTree class from Problem 1
*/
template <typename Key, typename Value>
class cacheLRU : private SplayTree<Key, Value>
{
	public:
		cacheLRU(int capacity); // TODO
		~cacheLRU(); //TODO
		void put(const std::pair<const Key, Value>& keyValuePair); // TODO
		std::pair<const Key, Value> get(const Key& key); // TODO
		int getLeftRotates();
		int getRightRotates();
		int getCacheMiss();
	private:
		// Member variables:
		int mMax_cap, mCurr_used, cache_miss;
		// Member functions:
};

/*
	----------------------------------------------
	Begin implementations for the cacheLRU class.
	----------------------------------------------
*/

/**
* A constructor that takes as an argument the capacity of the cache. 
* Assume that the capacity given is always an integer greater than or equal to 1.
*/
template<typename Key, typename Value>
cacheLRU<Key, Value>::cacheLRU(int capacity)
	: mMax_cap(capacity), mCurr_used(0), cache_miss(0)
{
	// TODO
}

/**
* A destructor.
*/
template<typename Key, typename Value>
cacheLRU<Key, Value>::~cacheLRU()
{
	// TODO
}

/**
* This function will insert the keyValuePair into the cache. 
* If the cache has reached its capacity, then one of the least recently used elements (LRU) should be removed from the cache. 
* For a splay tree implementation, this would normally be any leaf node. 
* However, we are asking that you remove the leaf with the minimum value key. 
* This operation should work in amortized O(log n) time where n is the number of elements in the cache.
*/
template<typename Key, typename Value>
void cacheLRU<Key, Value>::put(const std::pair<const Key, Value>& keyValuePair)
{
	// TODO
	if(this->SplayTree<Key, Value>::find(keyValuePair.first) == this->end()) // Check if item already exists in the cache
	{
		if(mCurr_used < mMax_cap) // Case 1: The splay tree is still not at max capacity
		{
			this->SplayTree<Key, Value>::insert(keyValuePair);
			mCurr_used++;
		}
		else // Case 2: The splay tree is at full capacity, remove min leaf
		{
			this->SplayTree<Key, Value>::deleteMinLeaf(); cache_miss++;
			this->SplayTree<Key, Value>::insert(keyValuePair);
		}
	}
}

/**
* This function will first find a node with the specified key in the tree and return the key/value pair. 
* If the key is not found, throw a logic_error exception. 
* This operation should work in amortized O(log n) time where n is the number of elements in the cache. 
* If the element with the key is the most recently used, this operation will take O(1) time.
*/
template<typename Key, typename Value>
std::pair<const Key, Value> cacheLRU<Key, Value>::get(const Key& key)
{
	// TODO
	typename cacheLRU<Key, Value>::iterator itr = this->SplayTree<Key, Value>::find(key);
	if(itr != this->SplayTree<Key, Value>::end()) // Case 1: Key is found
	{
		return *itr;
	}
	else // Case 2: Key not found
	{
		throw std::logic_error("Key: " + key + " was not found in cacheLRU.");
	}
}

/**
* Returns number of left rotations done
*/
template<typename Key, typename Value>
int cacheLRU<Key, Value>::getLeftRotates()
{
	// TODO
	return this->getNumLeftRotations();
}

/**
* Returns number of left rotations done
*/
template<typename Key, typename Value>
int cacheLRU<Key, Value>::getRightRotates()
{
	// TODO
	return this->getNumRightRotations();
}

/**
* Returns number of cache misses
*/
template<typename Key, typename Value>
int cacheLRU<Key, Value>::getCacheMiss()
{
	// TODO
	return cache_miss;
}

/*
	----------------------------------------------
	End implementations for the cacheLRU class.
	----------------------------------------------
*/

#endif