#ifndef HYPERCUBEGRAPH_H
#define HYPERCUBEGRAPH_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <set>
#include <map>

class HyperCubeGraph {
	public:
	    HyperCubeGraph(
	    	std::string start_node, 
			ifstream& permitted_nodes_file);
	    virtual ~HyperCubeGraph();

 	private:
 		// Member variables
 		/**
		* An internal Node struct to represent the n-bit strings
		*/
 		struct Node
 		{
 			// n-bit representation of the hypercube node coordinate
 			std::string node_coordinate;
	 		// Set of possible nodes from current node
	 		map<std::string, Node*> neighbour_nodes_map;
	 		// g is the length of the path from the start node to the current node 
	 		int g_val;
	 		// h is the heuristic approximation of the distance from the current node to the goal node
	 		int h_val;
	 		// A* makes the move with smallest f-value: f = g + h
	 		int f_val = g_val + h_val;
	 		// Constructor for Node struct
	 		Node(std::string n-bit_str) 
	 		{
	 			node_coordinate = n-bit_str;
	 		}
 		}
 		/**
		* A map of all the n-bit string Node* 
		*/
		map<std::string, Node*> hypercube_map;

	    // Member functions
		void findAllNeighbours();
};

#endif