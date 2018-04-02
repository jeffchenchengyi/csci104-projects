#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include "webpage.h"
#include "queryhandler.h"
#include "setutility.h"
using namespace std;

QueryHandler::QueryHandler(
	ifstream& query,
	const map< string, WebPage* >& webpage_map, 
	map< string, set<WebPage*> >& word_map,
	ofstream& output,
	double E, 
	int t) : RESTART_PROBABILITY(E), STEP_NUMBER(t) {
	/*------------- START QUERY HANDLING-------------*/
	string query_command;
	while(getline(query, query_command)) {
    	if(!query_command.empty()) {
    		analyzeQuery(query_command, webpage_map, word_map, output);
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
	const map< string, WebPage* >& webpage_map, 
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
					if(results.first.size() > 0) {
						results.first = addToCandidateSet(results.first, webpage_map);
					}
				} 
				else if(command_vec[0] == "OR") {
					results = unionT(command_vec, word_map);
					if(results.first.size() > 0) {
						results.first = addToCandidateSet(results.first, webpage_map);
					}
				} 
				else if(command_vec[0] == "INCOMING") {
					//Must only have 1 argument after INCOMING
					if(command_vec.size() == 2) {
						results = getIncomingLinks(command_vec, webpage_map);
					}
				} 
				else if(command_vec[0] == "OUTGOING") {
					//Must only have 1 argument after OUTGOING
					if(command_vec.size() == 2) {
						results = getOutgoingLinks(command_vec, webpage_map);
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
			if(weblink_vec.size() > 0) {
				weblink_vec = addToCandidateSet(weblink_vec, webpage_map);
			}
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

//Step 4. Expands candidate set and calls calculatePageRank
vector<string> QueryHandler::addToCandidateSet(
	const vector<string>& results_vec, 
	const map<string, WebPage*>& webpage_map) {

	//Traverse results vector and for each weblink string get 
	//its incoming and outgoing links through WebPage*
	vector<string> results_vec_copy;
	vector<string>::const_iterator results_vec_itr;
	for(results_vec_itr = results_vec.begin();
		results_vec_itr != results_vec.end();
		results_vec_itr++) {
		set< WebPage* >::iterator webpage_set_itr;
		if((*webpage_set_itr)->getWebLink() == *results_vec_itr) {
			vector<string> outgoinglinks_vec = (*webpage_set_itr)->getOutgoingLinkVec();
			vector<string> incominglinks_vec = (*webpage_set_itr)->getIncomingLinkVec();
		}
	}

	//Remove duplicates from results_vec_copy, store everything in set
	set<string> results_set;
	vector<string>::iterator results_vec_copy_itr;
	for(results_vec_copy_itr = results_vec_copy.begin();
		results_vec_copy_itr != results_vec_copy.end();
		results_vec_copy_itr++) {
		results_set.insert(*results_vec_copy_itr);
	}

	//Map that stores the key: weblink value: pair< vector<string>&, vector<string>& >
	map< string, pair<int, double> > pagerank_map;
	//# of vertices in webpages graph
	double n = double(results_set.size());

	//Create the pagerank map 
	set< WebPage* >::iterator webpage_set_itr;
	for(webpage_set_itr = webpage_set.begin();
		webpage_set_itr != webpage_set.end();
		webpage_set_itr++) {
		if(results_set.find((*webpage_set_itr)->getWebLink()) != results_set.end()) {
			double rank = 1 / n;
			//cout << (*webpage_set_itr)->getWebLink() <<((*webpage_set_itr)->getIncomingLinkVec()).size() << endl;
			pagerank_map.insert(
				make_pair(
					(*webpage_set_itr)->getWebLink(), 
					make_pair(
						int(((*webpage_set_itr)->getIncomingLinkVec()).size()),
						rank
					)
				)
			);
		}
	}

	//Calculates pagerank
	vector<string> final_vec;
	//calculatePageRank(final_vec, pagerank_map);
	return final_vec;
}

//Step 5. Calculates page rank and sorts the results_vec accordingly
void QueryHandler::calculatePageRank(
	vector<string>& results_vec,
	map< string, pair<int, double> >& pagerank_map) {
	map< string, pair<int, double> >::iterator pagerank_map_itr;
	for(int i = 0; i < STEP_NUMBER; i++) {
		for(pagerank_map_itr = pagerank_map.begin();
			pagerank_map_itr != pagerank_map.end();
			pagerank_map_itr++) {
			double probability_sum = 0.0;// = calculateProbabilitySum(pagerank_map_itr);
			double pagerank = ((1 - RESTART_PROBABILITY) * probability_sum) + (RESTART_PROBABILITY / int(pagerank_map.size()));
			//Update the old_rank with new_rank for each
			(pagerank_map_itr->second).second = pagerank;
		}
	}
	//Creates new set that is sorted by new rank
	set< pair<string, double>, PageRankComp > result_pagerank_set;
	for(pagerank_map_itr = pagerank_map.begin();
		pagerank_map_itr != pagerank_map.end();
		pagerank_map_itr++) {
		result_pagerank_set.insert(make_pair(pagerank_map_itr->first, (pagerank_map_itr->second).second));
	}

	//Iterate over the sorted set and push back each weblink into the result_vec
	set< pair<string, double>, PageRankComp >::iterator set_itr;
	for(set_itr = result_pagerank_set.begin();
		set_itr != result_pagerank_set.end();
		set_itr++) {
		results_vec.push_back(set_itr->first);
	}
}

//Calculates the sum of probabilities of each webpage / # of incoming links
double QueryHandler::calculateProbabilitySum(
	map< string, pair<int, double> >& pagerank_map) {
	double probability_sum = 0.00;
	map< string, pair<int, double> >::iterator pagerank_map_itr;
	//Traverses map and sums all the (old webpage rank / # of incoming vertices)
	for(pagerank_map_itr = pagerank_map.begin();
		pagerank_map_itr != pagerank_map.end();
		pagerank_map_itr++) {
		probability_sum += ((pagerank_map_itr->second).second) / ((pagerank_map_itr->second).first);
		cout << pagerank_map_itr->first << ": ";
		cout << ((pagerank_map_itr->second).second) << " / " << ((pagerank_map_itr->second).first) << endl;
	}
	return probability_sum;
}
/*------------- END QUERY HANDLING FUNCTIONS -------------*/