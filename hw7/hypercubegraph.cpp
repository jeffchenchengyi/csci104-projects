#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include "hypercubegraph.h"
using namespace std;

/*
	-----------------------------------------------------
	Begin implementations for the HyperCubeGraph class.
	-----------------------------------------------------
*/

/**
* Default constructor for a HyperCubeGraph, which first dynamically allocates all the nodes in the graph.
*/
HyperCubeGraph::HyperCubeGraph(
	string start_node, 
	ifstream& permitted_nodes_file)
{
	// Create start and goal node
	int num_zeros = 0; string goal_node;
	for(int j = 0; j < int(start_node.size()); j++)
	{
		if(start_node[j] == '0') 
		{
			num_zeros++;
		}
		goal_node.append(string(1, '1'));
	}

	// Start node
	source = start_node;
	hypercube_map.insert(make_pair(start_node, new Node(start_node, num_zeros, 0)));

	// Goal node
	goal = goal_node;
	hypercube_map.insert(make_pair(goal_node, new Node(goal_node, 0, 0)));

	// Create rest of the permitted nodes
	string num_rows;
	getline(permitted_nodes_file, num_rows); // The first row contains a number r indicating the number of nodes in the file.
	for(int i = 0; i < atoi(num_rows.c_str()); i++) // The remaining r rows in the file will contain a valid n-hypercube node.
	{
		string n_bit_str = "";
		getline(permitted_nodes_file, n_bit_str);
		if(!n_bit_str.empty() && hypercube_map.find(n_bit_str) == hypercube_map.end())
		{
			num_zeros = 0;
			for(int k = 0; k < int(n_bit_str.size()); k++)
			{
				if(n_bit_str[k] == '0') 
				{
					num_zeros++;
				}
			}
			hypercube_map.insert(make_pair(n_bit_str, new Node(n_bit_str, num_zeros, 0)));
		}
	}

	// Initialize expansions to 0
	expansions = 0;

	// Start finding all the neighbours
	findAllNeighbours();

	// Carry out A* algorithm
	aStar();

	// Print results
	printPath();
}

/**
* Default destructor for a HyperCubeGraph, deallocates all the dynamic memory for Nodes.
*/
HyperCubeGraph::~HyperCubeGraph() 
{
	map<string, Node*>::iterator map_itr;
	for(map_itr = hypercube_map.begin();
		map_itr != hypercube_map.end();
		map_itr++)
	{
		delete map_itr->second;
		map_itr->second = NULL;
	}
}

/**
* A method to find all the neighbours for each node in the graph and stores neighbours inside
* their node structs
*/
void HyperCubeGraph::findAllNeighbours() 
{
	map<string, Node*>::iterator map_itr;
	for(map_itr = hypercube_map.begin();
		map_itr != hypercube_map.end();
		map_itr++)
	{
		string neighbour_str;
		for(int i = 0; i < int((map_itr->first).size()); i++)
		{
			neighbour_str = map_itr->first;
			neighbour_str[i] == '0' ? neighbour_str[i] = '1' : neighbour_str[i] = '0';
			map<string, Node*>::iterator neighbour_in_map_itr = hypercube_map.find(neighbour_str);
			if(neighbour_in_map_itr != hypercube_map.end())
			{
				map_itr->second->neighbour_nodes_map
					.insert(
						make_pair(
							neighbour_in_map_itr->first, 
							neighbour_in_map_itr->second
						)
					);
			}
		}
	}
}

/**
* The A* algorithm used to find the single source shortest path
*/
void HyperCubeGraph::aStar() 
{
	// Priority queue used for A*
	priority_queue< pair<string, Node*>, vector< pair<string, Node*> >, NodeComp> visiting_PQ;
	// Set that includes all the explored nodes
	set<string> explored_set;
	// Make start node's predecessor null
	Node* source_node_ptr = (hypercube_map.find(source))->second;
	source_node_ptr->predecessor_pair.first = " ";
	source_node_ptr->predecessor_pair.second = NULL;
	visiting_PQ.push(make_pair(source, source_node_ptr));
	map<string, Node*>::iterator map_itr;
	for(map_itr = hypercube_map.begin();
		map_itr != hypercube_map.end();
		map_itr++)
	{
		if(map_itr->first != source)
		{
			(map_itr->second)->g_val = int(source.size()) * 2;
		}
	}
	while(!visiting_PQ.empty())
	{	
		// Whenever you remove a node from the std::priority_queue, 
		// check to see if you have already explored the node. 
		// If you have, discard the node without re-exploring it, 
		// and do not incrementing your expansions.
		pair<string, Node*> curr_node = visiting_PQ.top();
		visiting_PQ.pop();
		if(explored_set.find(curr_node.first) == explored_set.end())
		{
			expansions++; // Increment expansions only if node is unexplored
			map<string, Node*>::iterator neighbour_map_itr;
			for(neighbour_map_itr = (curr_node.second)->neighbour_nodes_map.begin();
				neighbour_map_itr != (curr_node.second)->neighbour_nodes_map.end();
				neighbour_map_itr++)
			{
				int dist_from_source_of_curr_node = (curr_node.second)->g_val;
				if(dist_from_source_of_curr_node + 1 
					< (neighbour_map_itr->second)->g_val) // If current node's g value + 1 is less than neighbour's g value which denotes distance from source
				{
					// Change the neighbour's predecessor to current node
					(neighbour_map_itr->second)->predecessor_pair.first = curr_node.first;
					(neighbour_map_itr->second)->predecessor_pair.second = curr_node.second;

					// Change the neighbour's g value to current node's g value + 1
					(neighbour_map_itr->second)->g_val
						= dist_from_source_of_curr_node + 1; 

					// Whenever you find a new path to an unexplored bit string, 
					// add the bit string with the new priority to the std::priority_queue. 
					// This means you may have multiple elements in your std::priority_queue 
					// referencing the same bit string.
					if(explored_set.find(neighbour_map_itr->first) == explored_set.end())
					{
						visiting_PQ.push(*neighbour_map_itr);
					}

					// If we found the goal node, start popping everything as the algorithm is completed
					if(neighbour_map_itr->first == goal)
					{
						while(!visiting_PQ.empty())
						{
							visiting_PQ.pop();
						}
					}
				}
			}
			explored_set.insert(curr_node.first); // After exploring all the neighbors, we will mark this node as explored
		}
	}
}

/**
* To print the results of A*
*/
void HyperCubeGraph::printPath() const
{
	Node* goal_node = (hypercube_map.find(goal))->second;
	Node* curr_node = goal_node;
	bool pathExist = false;
	while(curr_node != NULL) 
	{
		if(curr_node->node_coordinate == source)
		{
			rec_printPredecessor(goal_node);
			cout << "expansions = " << expansions << endl;
			pathExist = true;
			break;
		}
		else
		{
			curr_node = (curr_node->predecessor_pair).second;
		}
	}
	if(!pathExist)
	{
		cout << "No transformation" << endl;
		cout << "expansions = " << expansions << endl;
	}
}

/**
* To print the predecessors in order from the goal node to the source node with expansions at the end
*/
void HyperCubeGraph::rec_printPredecessor(Node* curr_node_ptr) const
{
	if(curr_node_ptr != NULL)
	{
		rec_printPredecessor((curr_node_ptr->predecessor_pair).second);
		cout << curr_node_ptr->node_coordinate << endl;
	}
}

/*
	-----------------------------------------------------
	End implementations for the BinarySearchTree class.
	-----------------------------------------------------
*/