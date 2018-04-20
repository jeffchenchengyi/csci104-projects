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

int main(int argc, char* argv[]) {
	//To check if the starting node and permitted nodes file was included as a command line parameter
    string start_node;
    ifstream permitted_nodes_file;
    if(argc < 3) {
    	cerr << "*Please include the starting node and permitted nodes file.*" << endl;
        return -1;
    }
    start_node = argv[1];
    permitted_nodes_file.open(argv[2]);

    //If the permitted nodes file given could not be found or could not be open
    if(permitted_nodes_file.fail()) {
        cerr << "Permitted nodes file could not be open." << endl;
        return -1;
    }

    // Creates hypercube graph and prints the shortest path to goal node of all 1s
    HyperCubeGraph(start_node, permitted_nodes_file);

	return 0;
}