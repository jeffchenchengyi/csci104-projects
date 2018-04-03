#ifndef QUERYHANDLER_H
#define QUERYHANDLER_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <set>
#include <map>
#include "webpage.h"
#include "setutility.h"

class QueryHandler {
	public:
	    QueryHandler(
	    	std::ifstream& query,
			const std::map< std::string, WebPage* >& webpage_map, 
			std::map< std::string, std::set<WebPage*> >& word_map,
			std::ofstream& output,
			float E, 
			int t);
	    virtual ~QueryHandler();
	    bool isCloseParen(std::string x);
        bool isOpenParen(std::string x);

 	private:
 		//Member variables
 		float RESTART_PROBABILITY;
		int STEP_NUMBER;
		//Comparator for key comparison of pagerank map
		struct PageRankComp {
			bool operator()(
				const std::pair<std::string, float>& lhs, 
				const std::pair<std::string, float>& rhs) { 
				return lhs.second >= rhs.second; 
			}
		};
		//Struct to store data for Page rank algorithm
		struct PageRankData {
			std::string weblink;
			float oldpagerank;
			float newpagerank;
			int num_outgoingWebPages; //|deg+(v)|
			std::set<PageRankData*> incomingWebPages; //deg-(v)
		};
		//Map to store all the candidate set details
		std::map<std::string, PageRankData*> search_result_webpages;

	    //Member functions
	    void analyzeQuery(
			std::string query_command, 
			const std::map< std::string, WebPage* >& webpage_map, 
			std::map< std::string, std::set<WebPage*> >& word_map,
			std::ofstream& output);
	    void displayWebPage(
	    	std::string weblink, 
	    	std::ofstream& output);
	    std::vector<std::string> addToCandidateSet(
			const std::vector<std::string>& results_vec, 
			const std::map< std::string, WebPage* >& webpage_map);
	    void storeInSet(
			std::set<std::string>& results_set,
			const std::vector<std::string>& vec_tobestored);
	    void calculatePageRank(std::vector<std::string>& final_vec);
	    float calculateProbabilitySum(PageRankData*);
};

#endif