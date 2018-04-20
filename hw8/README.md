# Instructions on how to execute hw7 programs:

## [Problem 1 (Splay Tree, 40%): ](splayTree.h)

### A templated splayTree class that inherits publicly from the rotateBST class from Assignment 7, and implements the following functions:

The class has the following **`public`** functions:
- **`SplayTree()`** 
	- A constructor.
- **`void insert(const std::pair<const Key, Value>& keyValuePair)`**
	- This function will insert a new node into the tree with the specified key and value. 
	- The node that has just been inserted is splayed to the root. 
	- If a node with this key already exists, don't insert anything, but splay the node to the root.
- **`void remove(const Key& key)`**
	- This function will first find a node with the specified key in the tree. 
	- This function should call BST remove, and then splay the parent of the deleted node to root. (This is different and less complicated than method given in Sandra's lecture, but works well given the inheritance hierarchy.) 
	- If the key is not already in the tree, then don't remove anything, but splay the last node visited to the root.
- **`iterator find(const Key& key) const`**
	- This function should splay the node with the specified key to the root, and return an iterator to that item. 
	- If the key is not found, splay the last visited node to the root, and return the end iterator.
- **`iterator findMin() const`**
	- This function finds the node with the minimum key value and splays it to the root. 
	- Returns an iterator to the item with the minimum value key.
- **`iterator findMax() const`**
	- This function finds the node with the maximum key value and splays it to the root. 
	- Returns an iterator to the item with the maximum value key.
- **`void deleteMinLeaf()`**
	- This function deletes the leaf with minimum key value, exactly as if you had called the remove function.
- **`void deleteMaxLeaf()`**
	- This function deletes the leaf with maximum key value, exactly as if you had called the remove function.
</br>
The class has the following **`protected`** functions:
- **`void splay(Node<Key, Value> *r)`**
	- This function splays a given node to the root of the splayTree.
---

## [Problem 2 (Hash Table Analysis, 25%): ](HW8analysis.pdf)

1. Start with a hash table of size 7. If you must resize, use a hash table of size 11.
2. Maintain a load factor of less than or equal to 1/2. If the load factor becomes greater than 1/2, resize your hash table.
3. Use the following hash function: **`h(k) = k % m`** where **`k`** is the key and **`m`** is the table size.
4. Draw what the hash table contents will be after the following sequences of operations. If you must resize the hash table, draw what the hash table contents are before and after resizing.
5. If you remove an element from a hash table, use the symbol "R" to indicate that the item is removed if necessary. Removed elements count towards the load factor.
6. For any find operations, please list the search sequence of locations and the result returned from the operation.

#### Part a
- Complete this exercise using quadratic probing for the following sequence of operations in this order:
	- Insert 15, 22, 36
	- Remove 22
	- Find 36
	- Insert 10

#### Part b
- For the same sequence of operations, use double-hashing (instead of quadratic probing). Let the second hash function be the following: **`h₂(k) = 3 - (k % 3)`**

#### Part c
	- You are given a Bloom Filter with three hash functions **`h₁`**, **`h₂`**, **`h₃`** and **`m`** indices.
	- Currently, exactly **`2m/3`** indices are set to **`true`**, while the remaining **`m/3`** are set to **`false`**.(You may assume that **`m`** is divisible by 3.)
	- Assume that the three hash functions are universal and independent, that is:
		- the probability that **`hᵢ(x) = p`** is exactly **`1/m`** for all indices **`p`** (and **`i = 1, 2, 3`**)
		- **`hᵢ(x)`** is independent of **`hⱼ(y)`** for all **`i`**, **`j`** ∈ {1, 2, 3} and **`x`**, **`y`** when **`i`** does not equal **`j`** and **`x`** does not equal **`y`**
<br/>
Answer the following and explain your answer: If you search for 27 items, none of which are inside the Bloom Filter, how many false positives will you get on average?
---

## [Problem 3 (LRU Cache Implementation, 35%): ](cacheLRU.h)

### A templated cacheLRU class that uses your splayTree class from Problem 1. The cache will store key/value pairs. If this were actually a memory cache, key would be the memory address and value would be the data to be placed at the address.

The class has the following **`public`** functions:

**`cacheLRU(int capacity)`**
	- A constructor that takes as an argument the capacity of the cache. 
	- You may assume that the capacity given is always an integer greater than or equal to 1.
**`~cacheLRU()`**
	- A destructor.
**`void put(const std::pair<const Key, Value>& keyValuePair)`** 
	- This function will insert the keyValuePair into the cache. 
	- If the cache has reached its capacity, then one of the least recently used elements (LRU) should be removed from the cache. 
	- For a splay tree implementation, this would normally be any leaf node. 
	- However, we are asking that you remove the leaf with the minimum value key. 
	- This operation should work in amortized O(log n) time where n is the number of elements in the cache.
**`std::pair<const Key, Value> get(const Key& key)`**
	- This function will first find a node with the specified key in the tree and return the key/value pair. 
	- If the key is not found, throw a logic_error exception. 
	- This operation should work in amortized O(log n) time where n is the number of elements in the cache. 
	- If the element with the key is the most recently used, this operation will take O(1) time.
<br/>
Analysis:
Run several tests on your cache with different input files, and analyze the results in **`HW8analysis.pdf`**. You will want to count the number of times you call leftRotate() and rightRotate() on each input file, which will give an approximate measure of how long each input file took to run. At minimum, you should run:

- A large test (the entire text of Hamlet is available online, and would serve as a good large test), where you insert each word into the cache in sequence (or get the word if it is still in the cache).
- 2 moderate-sized tests, one on uniformly random data, and another on an English text of approximately the same size.
<br/>
In your analysis, answer the following questions:

1. What test files did you use (describe them)?
2. What was the capacity of your cache for each test?
3. What was the total number of rotations for each file?
4. What was the size of each file?
5. What was the average number of rotations per item (that is, your answer to 2, divided by your answer to 3)?
6. How many items did you have to remove from the cache? This occurs when you bring a new item into the cache, which is referred to as a **`cache miss`**. Caches are designed in such a way as to minimize cache misses.
7. Was there a noticeable difference between the two moderate-sized tests? Explain why there was or was not a difference.
8. Include any other interesting analysis your test cases revealed.