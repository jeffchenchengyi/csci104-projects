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
			const std::set< WebPage* >& webpage_set, 
			std::map< std::string, std::set<WebPage*> >& word_map,
			std::ofstream& output,
			double E, 
			int t);
	    virtual ~QueryHandler();
	    bool isCloseParen(std::string x);
        bool isOpenParen(std::string x);

 	private:
 		//Member variables
 		double RESTART_PROBABILITY;
		int STEP_NUMBER;
		//Comparator for key comparison of pagerank map
		struct PageRankComp {
			bool operator()(
				const std::pair<std::string, double>& lhs, 
				const std::pair<std::string, double>& rhs) { 
				return lhs.second > rhs.second; 
			}
		};

	    //Member functions
	    void analyzeQuery(
			std::string query_command, 
			const std::set< WebPage* >& webpage_set, 
			std::map< std::string, std::set<WebPage*> >& word_map,
			std::ofstream& output);
	    void displayWebPage(
	    	std::string weblink, 
	    	std::ofstream& output);
	    std::vector<std::string> addToCandidateSet(
			const std::vector<std::string>& results_vec, 
			const std::set< WebPage* >& webpage_set);
	    void calculatePageRank(
			std::vector<std::string>& results_vec, 
			std::map< std::string, std::pair<int, double> >& pagerank_map);
	    double calculateProbabilitySum(
			std::map< std::string, std::pair<int, double> >& pagerank_map);
};

#endif