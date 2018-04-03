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
	float E, 
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

	/*--------- Start Expanding candidate set ---------*/
	//Traverse results_vec and for each weblink string get 
	//its incoming and outgoing links through WebPage*, storing
	//them in a results_set to be used for calculation of pagerank
	set<string> results_set;
	vector<string>::const_iterator results_vec_itr;
	for(results_vec_itr = results_vec.begin();
		results_vec_itr != results_vec.end();
		results_vec_itr++) {
		map<string, WebPage*>::const_iterator webpage_map_itr = webpage_map.find(*results_vec_itr);
		if(webpage_map_itr != webpage_map.end()) {
			vector<string> outgoinglinks_vec = (webpage_map_itr->second)->getOutgoingLinkVec();
			vector<string> incominglinks_vec = (webpage_map_itr->second)->getIncomingLinkVec();
			//Store the candidate set of a specific webpage in the results_set
			storeInSet(results_set, results_vec);
			storeInSet(results_set, outgoinglinks_vec);
			storeInSet(results_set, incominglinks_vec);
		} else {
			cerr << *results_vec_itr << " is not in the network of webpages..." << endl;
		}
	}
	/*--------- End Expanding candidate set ---------*/

	/*--------- Start Dynamically allocating memory for PageRankData structs ---------*/
	//Map that stores the key: weblink, 
	//value: pointer to PageRankData struct / vertices in search results graph
	map<string, PageRankData*> pagerank_map;
	//# of vertices in webpages graph
	float n = float(results_set.size());

	//Creates all the PageRankData structs for the search result candidate set
	set<string>::iterator results_set_itr;
	for(results_set_itr = results_set.begin();
		results_set_itr != results_set.end();
		results_set_itr++) {
		PageRankData* webpage_ptr = new PageRankData;
		webpage_ptr->weblink = *results_set_itr;
		webpage_ptr->oldpagerank = 1 / n;
		webpage_ptr->newpagerank = 1 / n;
		//Add 1 to num_outgoingWebPages to account for a self-loop
		webpage_ptr->num_outgoingWebPages 
			= int((((webpage_map.find(*results_set_itr))->second)->getOutgoingLinkVec()).size()) + 1;
		search_result_webpages.insert(make_pair(*results_set_itr, webpage_ptr));
	}

	//Inserts all the incoming edges to the PageRankData structs, creates Webpages digraph
	map<string, PageRankData*>::iterator search_result_webpages_itr;
	for(search_result_webpages_itr = search_result_webpages.begin();
		search_result_webpages_itr != search_result_webpages.end();
		search_result_webpages_itr++) {
		vector<string> incominglinks_vec
			= (((webpage_map.find(search_result_webpages_itr->first))->second)->getIncomingLinkVec());
		vector<string>::iterator incominglinks_vec_itr;
		for(incominglinks_vec_itr = incominglinks_vec.begin();
			incominglinks_vec_itr != incominglinks_vec.end();
			incominglinks_vec_itr++) {
			map<string, PageRankData*>::iterator search_result_map_itr 
				= search_result_webpages.find(*incominglinks_vec_itr);
			if(search_result_map_itr != search_result_webpages.end()) {
				((search_result_webpages_itr->second)->incomingWebPages)
					.insert(search_result_map_itr->second);
			} else {
				cerr << *incominglinks_vec_itr << " is not a weblink in the search result candidate set digraph..." << endl;
			}
		}
	}
	/*--------- End Dynamically allocating memory for PageRankData structs ---------*/

	//Calculates pagerank
	vector<string> final_vec;
	calculatePageRank(final_vec);

	/*--------- Start Dynamically allocating memory for PageRankData structs ---------*/
	for(search_result_webpages_itr = search_result_webpages.begin();
		search_result_webpages_itr != search_result_webpages.end();
		search_result_webpages_itr++) {
		delete search_result_webpages_itr->second;
	}
	/*--------- End Dynamically allocating memory for PageRankData structs ---------*/

	return final_vec;
}

void QueryHandler::storeInSet(
	set<string>& results_set,
	const vector<string>& vec_tobestored) {
	vector<string>::const_iterator vec_itr;
	for(vec_itr = vec_tobestored.begin();
		vec_itr != vec_tobestored.end();
		vec_itr++) {
		results_set.insert(*vec_itr);
	}
}

//Step 5. Calculates page rank and sorts the results_vec accordingly
void QueryHandler::calculatePageRank(vector<string>& final_vec) {

	//Iterates through step number to calculate new page rank
	map<string, PageRankData*>::iterator search_result_webpages_itr;
	for(int i = 0; i < STEP_NUMBER; i++) {
		for(search_result_webpages_itr = search_result_webpages.begin();
			search_result_webpages_itr != search_result_webpages.end();
			search_result_webpages_itr++) {
			float probability_sum = calculateProbabilitySum(search_result_webpages_itr->second);
			float currpagerank = ((1 - RESTART_PROBABILITY) * probability_sum) + (RESTART_PROBABILITY / int(search_result_webpages.size()));
			//Update the old_rank with new_rank for each 
			(search_result_webpages_itr->second)->newpagerank = currpagerank;
		}
		//After calculating all the pageranks after an iteration, we update the oldpagerank with the new ones for all
		for(search_result_webpages_itr = search_result_webpages.begin();
			search_result_webpages_itr != search_result_webpages.end();
			search_result_webpages_itr++) {
			(search_result_webpages_itr->second)->oldpagerank = (search_result_webpages_itr->second)->newpagerank;
		}
	}

	//Creates new set that is sorted by new rank
	set< pair<string, float>, PageRankComp > result_pagerank_set;
	for(search_result_webpages_itr = search_result_webpages.begin();
		search_result_webpages_itr != search_result_webpages.end();
		search_result_webpages_itr++) {
		result_pagerank_set.insert(
			make_pair(
				search_result_webpages_itr->first, 
				(search_result_webpages_itr->second)->newpagerank
			)
		);
	}

	//Iterate over the sorted set and push back each weblink into the result_vec
	set< pair<string, float>, PageRankComp >::iterator set_itr;
	for(set_itr = result_pagerank_set.begin();
		set_itr != result_pagerank_set.end();
		set_itr++) {
		final_vec.push_back(set_itr->first);
	}
}

//Calculates the sum of probabilities of each webpage / # of incoming links
float QueryHandler::calculateProbabilitySum(PageRankData* curr_webpage_ptr) {
	float probability_sum = 0.00;
	//Traverses map and sums all the (old webpage rank / # of incoming vertices)
	set<PageRankData*>::iterator pagerankdata_ptr_set_itr;
	for(pagerankdata_ptr_set_itr = (curr_webpage_ptr->incomingWebPages).begin();
		pagerankdata_ptr_set_itr != (curr_webpage_ptr->incomingWebPages).end();
		pagerankdata_ptr_set_itr++) {
		probability_sum += ((*pagerankdata_ptr_set_itr)->oldpagerank) / ((*pagerankdata_ptr_set_itr)->num_outgoingWebPages);
	}
	//To account for the self-loop
	probability_sum += (curr_webpage_ptr->oldpagerank) / (curr_webpage_ptr->num_outgoingWebPages);
	return probability_sum;
}
/*------------- END QUERY HANDLING FUNCTIONS -------------*/