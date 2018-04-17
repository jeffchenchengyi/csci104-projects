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
#include <cmath>

class HyperCubeGraph {
	public:
	    HyperCubeGraph(
	    	std::string start_node, 
			std::ifstream& permitted_nodes_file);
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
	 		std::map<std::string, Node*> neighbour_nodes_map;
	 		// g is the length of the path from the start node to the current node 
	 		int g_val;
	 		// h is the heuristic approximation of the distance from the current node to the goal node
	 		int h_val;
	 		// A* makes the move with smallest f-value: f = g + h
	 		int f_val() { return g_val + h_val; }
	 		// Predecessor of node
	 		std::pair<std::string, Node*> predecessor_pair;
	 		// Constructor for Node struct
	 		Node(std::string n_bit_str, int num_zeros, int num_diff_bits) 
	 			: 	node_coordinate(n_bit_str),
		 			h_val(num_zeros),
		 			g_val(num_diff_bits)
	 		{
	 		}
 		};
 		/**
		* A comparator to compare the nodes to see which one should be visited first
		*/
		struct NodeComp 
		{
			bool operator()(
				const std::pair<std::string, Node*>& lhs, 
				const std::pair<std::string, Node*>& rhs) 
			{ 
				// 1. Always make the move with smallest f-value.
				if((lhs.second)->f_val() < (rhs.second)->f_val())
				{
					return false;
				}
				else if((lhs.second)->f_val() > (rhs.second)->f_val())
				{
					return true;
				}
				else
				{
					// 2. If multiple words have the smallest f-value, choose the one with the smallest h-value.
					if((lhs.second)->h_val < (rhs.second)->h_val)
					{
						return false;
					}
					else if((lhs.second)->h_val > (rhs.second)->h_val)
					{
						return true;
					}
					else
					{
						// 3. If multiple words have the smallest f and h-value, 
						// choose the node that has the smallest value in binary, 
						// (where the first bit is the most significant bit).
						for(int i = 0; i < int(lhs.first.size()); i++)
						{
							if(lhs.first[i] == '1' 
								&& rhs.first[i] == '0')
							{
								return true;
							}
							else if(lhs.first[i] == '0' 
								&& rhs.first[i] == '1')
							{
								return false;
							}
							else
							{
								// Current significant bit is the same, we need 
								// to move to the next significant bit to break ties
							}
						}
					}
				}
			}
		};
 		/**
		* A map of all the n-bit string Node* 
		*/
		std::map<std::string, Node*> hypercube_map;
		std::string source;
		std::string goal;
		int expansions;

	    // Member functions
		void findAllNeighbours();
		void aStar();
		void printPath() const;
		void rec_printPredecessor(Node*) const;
};

#endif