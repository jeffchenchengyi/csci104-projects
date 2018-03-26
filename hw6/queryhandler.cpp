#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <set>
#include <map>
#include "webpage.h"
#include "queryhandler.h"
#include "setutility.h"
using namespace std;

QueryHandler::QueryHandler(
	ifstream& query,
	const set< WebPage* >& webpage_set, 
	map< string, set<WebPage*> >& word_map,
	ofstream& output
	) {
	/*------------- START QUERY HANDLING-------------*/
	string query_command;
	while(getline(query, query_command)) {
    	if(!query_command.empty()) {
    		analyzeQuery(query_command, webpage_set, word_map, output);
    	} else {
    		output << "Invalid query" << endl;
    	}
    }
	/*------------- END QUERY HANDLING-------------*/
}

QueryHandler::~QueryHandler() {
};

/*------------- START QUERY HANDLING FUNCTIONS -------------*/
bool QueryHandler::isCloseParen(string x) {
    return (x == ")") ? true : false;
}

bool QueryHandler::isOpenParen(string x) {
    return (x == "(") ? true : false;
}

//to identitfy what the command wants to be done
void QueryHandler::analyzeQuery(
	string query_command, 
	const set< WebPage* >& webpage_set, 
	map< string, set<WebPage*> >& word_map,
	ofstream& output
	) {
	//Split the query_command into the search command and the specified queries
	vector<string> command_vec;
	string command_token;
	istringstream iss(query_command);
	while(iss >> command_token) {
		command_vec.push_back(command_token);
	}

	//Execution of commands
	vector<string> weblink_vec;
	if(command_vec.size() > 0) {
		if(command_vec.size() > 1) {
			if(command_vec[0] == "PRINT") {
				//Must only have 1 argument after PRINT
				if(command_vec.size() != 2) {
					output << "Invalid query" << endl;
				} else {
					displayWebPage(command_vec[1], output);
				}
			} else {
				//Set of weblinks, bool to check if results was found
				pair< vector<string>, bool > results = make_pair(weblink_vec, false); 
				if(command_vec[0] == "AND") {
					results = intersectT(command_vec, word_map);
				} 
				else if(command_vec[0] == "OR") {
					results = unionT(command_vec, word_map);
				} 
				else if(command_vec[0] == "INCOMING") {
					//Must only have 1 argument after INCOMING
					if(command_vec.size() == 2) {
						results = getIncomingLinks(command_vec, webpage_set);
					}
				} 
				else if(command_vec[0] == "OUTGOING") {
					//Must only have 1 argument after OUTGOING
					if(command_vec.size() == 2) {
						results = getOutgoingLinks(command_vec, webpage_set);
					}
				} 
				else {
					//If the command was just word1 word2 without any AND, OR,...
				}
				//Output results of search if command was valid
				if(results.second) {
					outputResults(results.first, output);
				} else {
					output << "Invalid query" << endl;
				}
			}
		} else {
			weblink_vec = search(command_vec[0], word_map);
			outputResults(weblink_vec, output);
		}
	} else {
		//If query was just trailing whitespaces
		output << "Invalid query" << endl;
	} 
}

//For PRINT command
void QueryHandler::displayWebPage(string weblink, ofstream& output) {
	ifstream webpage_file(weblink.c_str());
	if(!webpage_file) {
    	output << "Invalid query" << endl;
        return;
    }
    output << weblink << endl;
    //prints char by char but leaves out anything in and incl. ()
    while(webpage_file.peek() != EOF) {
    	char curr_char;
    	webpage_file.get(curr_char);
    	if(isOpenParen(string(1, curr_char))) {
    		while(webpage_file.peek() != EOF) {
    			char inparen;
 				if(isCloseParen(string(1, webpage_file.peek()))) {
 					webpage_file.get(inparen);
 					break;
 				} else {
 					webpage_file.get(inparen);
 				}
    		}
    	} else {
    		output << curr_char;
    	}
    }
    output << endl;
}
/*------------- END QUERY HANDLING FUNCTIONS -------------*/