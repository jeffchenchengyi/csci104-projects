#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <set>
#include <map>
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
	string num_rows;
	getline(permitted_nodes_file, num_rows); // The first row contains a number r indicating the number of nodes in the file.
	for(int i = 0; i < stoi(num_rows); i++) // The remaining r rows in the file will contain a valid n-hypercube node.
	{
		string n-bit_str;
		getline(permitted_nodes_file, n-bit_str);
		if(!n-bit_str.empty())
		{
			Node* newNode_ptr = new Node(n-bit_str);
			hypercube_map.insert(make_pair(n-bit_str, newNode_ptr));
		}
	}
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
	}
}

/**
* A method to find all the neighbours for each node in the graph
*/
HyperCubeGraph::findAllNeighbours() 
{
	map<string, Node*>::iterator map_itr;
	for(map_itr = hypercube_map.begin();
		map_itr != hypercube_map.end();
		map_itr++)
	{
		
	}
}

/*
	-----------------------------------------------------
	End implementations for the BinarySearchTree class.
	-----------------------------------------------------
*/