# Instructions on how to execute hw7 programs:

## [Problem 1 (Binary Search Trees, 35%): ](bst.h)

### Implemented functions below:
- **`int height()`** 
	- This function will return the current height of the tree. This should run in constant time. Height of a leaf node should be 1.
- **`bool isBalanced()`**
	- This function will return true if an only if the tree is balanced. 
	- A tree is balanced if and only if for all subtrees with root v |height(left_subtree_v) - height(right_subtree_v)| <= 1. 
	- Runtime is O(n).
- **`void insert(const std::pair<const Key, Value>& keyValuePair)`**
	- This function will insert a new node into the tree with the specified key and value. 
	- There is no guarantee the tree is balanced before or after the insertion. 
	- If key is already in the tree, this function will do nothing. Runtime is O(h).
- **`void remove(const Key& key)`**
	- This function will remove the node with the specified key from the tree. 
	- There is no guarantee the tree is balanced before or after the removal. 
	- If the key is not already in the tree, this function will do nothing. 
	- If the node to be removed has two children use its predecessor (not its successor) in the BST removal algorithm. 
	- If the node to be removed has exactly one child, it either promote the child.
	- Runtime is O(h). 
- **`void clear()`**
	- Deletes all nodes inside the tree, resetting it to the empty tree. 
	- Runtime is O(n).
- **`Node* internalFind(const Key& key)`**
	- Returns a pointer to the node with the specified key. 
	- Runtime is O(h).
- **`Node* getSmallestNode()`**
	- Returns a pointer to the node with the smallest key. 
	- This function is used by the iterator. 
	- Runtime is O(h).
- **`Constructor and destructor`**
	- The destructor calls the clear function. 
	- The constructor should take constant time.



## [Problem 2 (The Power of Rotations 25%): ](rotateBST.h)

### Implemented functions below:
- **`protected`** functions:
	- **`void leftRotate(Node<Key, Value>* r)`** 
		- Performs a left rotation at the parameter node. 
		- If r has no right child, this function does nothing. 
		- This runs in constant time.
	- **`void rightRotate(Node<Key, Value>* r)`**
		- Performs a right rotation at the parameter node. 
		- If r has no left child, this function does nothing. 
		- This runs in constant time.
- **`public`** functions:
	- **`bool sameKeys(const rotateBST& t2) const`**
		- Given another BST, checks that the set of keys in both trees are identical. 
		- This runs in O(n) time, where n is the number of nodes in the tree.
	- **`void transform(rotateBST& t2) const`**
		- Given another BST t2, if t2 contains the same keys as the one for this, 
		transform the BST t2 into the one for this using only rotations. 
		- If the BST t2 does not have the same keys as this, this function should do nothing and neither BST should be modified.


## [Problem 3 (Restricted N-Hypercube Exploration, 40%): ](hypercube.cpp)
### [Header file for HyperCubeGraph class](hypercubegraph.h)

- Input: 
	1. Starting node - E.g. **`00100`**
	2. Permitted nodes file 
- Output:
	- Implements A* algorithm to find the shortest path from start node to goal node in a restricted hyoercube
	- If path from start node to goal node found:
		- **`start_node`** <br/>
		- **`node_1`** <br/>
		- **`node_2`** <br/>
		- **`... `** <br/>
		- **`goal_node`** <br/>
		- **`expansions = X`**<br/>
	- If path from start node to goal node not found:
		- **`No transformation`** <br/>
		- **`expansions = X`** <br/>
- Use [Makefile](Makefile) to compile crawler to executable by running **`make hypercube`**
- Run by **`./hypercube 00100 permitted.txt`**