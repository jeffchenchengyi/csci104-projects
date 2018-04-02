#ifndef SETUTILITY_H
#define SETUTILITY_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <set>
#include <map>
#include "webpage.h"

/*------------- START QUERY HANDLING FUNCTIONS -------------*/	
//For AND command
template <class T1, class T2>
const typename std::pair< std::vector<T1>, bool > intersectT(
	std::vector<T1>& command_vec, 
	std::map< T1, std::set<T2> >& T1_map
	) {
	typename std::map<T1, int> query_map;
	typename std::map<T1, int>::iterator query_map_itr; 
	typename std::vector<T1> result_vec;
	//Traverse each word in command vec
	for(int i = 1; i < int(command_vec.size()); i++) {
		//Find word in word_map O(logn)
		typename std::map< T1, std::set<T2> >::iterator T1_map_itr = T1_map.find(command_vec[i]);
		if(T1_map_itr != T1_map.end()) {
			typename std::set<T2> T2_set = T1_map_itr->second;
			typename std::set<T2>::iterator T2_set_itr;
			//Check if the same weblink exists for each word O(m) 
			//where m is the number of weblinks in my result set
			for(T2_set_itr = T2_set.begin(); 
				T2_set_itr != T2_set.end(); 
				T2_set_itr++
				) {
				query_map_itr = query_map.find((*T2_set_itr)->getWebLink());
				//If query_map already has the weblink as a key, increment its count
				//else create a new key: weblink, value: count pair
				if(query_map_itr != query_map.end()) {
					(query_map_itr->second)++;
				} else {
					query_map.insert(make_pair((*T2_set_itr)->getWebLink(), 1));
				}
			}
		} else {
			break;
		}
	}
	//Any weblinks that have command_vec - 1 # of counts means it contains
	//all required query keywords in AND
	for(query_map_itr = query_map.begin(); 
		query_map_itr != query_map.end(); 
		query_map_itr++
		) {
		if(query_map_itr->second == (int(command_vec.size()) - 1)) {
			result_vec.push_back(query_map_itr->first);
		}
	}
	return make_pair(result_vec, true);
}

//For AND command (OVERLOADED FUNCTION FOR STRING)
template<class T2>
const typename std::pair< std::vector<std::string>, bool > intersectT(
	std::vector<std::string>& command_vec, 
	std::map< std::string, std::set<T2> >& T1_map
	) {
	typename std::map<std::string, int> query_map;
	typename std::map<std::string, int>::iterator query_map_itr; 
	typename std::vector<std::string> result_vec;
	//Traverse each word in command vec
	for(int i = 1; i < int(command_vec.size()); i++) {
		//convert all chars to lowercase
		for(int j = 0; j < int(command_vec[i].size()); j++) {
			command_vec[i][j] = tolower(command_vec[i][j]);
		}
		//Find word in word_map O(logn)
		typename std::map< std::string, std::set<T2> >::iterator T1_map_itr = T1_map.find(command_vec[i]);
		if(T1_map_itr != T1_map.end()) {
			typename std::set<T2> T2_set = T1_map_itr->second;
			typename std::set<T2>::iterator T2_set_itr;
			//Check if the same weblink exists for each word O(m) 
			//where m is the number of weblinks in my result set
			for(T2_set_itr = T2_set.begin(); 
				T2_set_itr != T2_set.end(); 
				T2_set_itr++
				) {
				query_map_itr = query_map.find((*T2_set_itr)->getWebLink());
				//If query_map already has the weblink as a key, increment its count
				//else create a new key: weblink, value: count pair
				if(query_map_itr != query_map.end()) {
					(query_map_itr->second)++;
				} else {
					query_map.insert(make_pair((*T2_set_itr)->getWebLink(), 1));
				}
			}
		} else {
			break;
		}
	}
	//Any weblinks that have command_vec - 1 # of counts means it contains
	//all required query keywords in AND
	for(query_map_itr = query_map.begin(); 
		query_map_itr != query_map.end(); 
		query_map_itr++
		) {
		if(query_map_itr->second == (int(command_vec.size()) - 1)) {
			result_vec.push_back(query_map_itr->first);
		}
	}
	return make_pair(result_vec, true);
}

//For OR command
template <class T1, class T2>
const typename std::pair< std::vector<T1>, bool > unionT(
	std::vector<T1>& command_vec, 
	std::map< T1, std::set<T2> >& T1_map
	) {
	typename std::vector<T1> result_vec;
	typename std::set<T1> temp_set;
	for(int i = 1; i < int(command_vec.size()); i++) {
		//iterator to the word in word_map
		typename std::map< T1, std::set<T2> >::iterator T1_map_itr = T1_map.find(command_vec[i]);
		if(T1_map_itr != T1_map.end()) {
			typename std::set<T2> T2_set = T1_map_itr->second; //Set of all weblinks that contain that word
			typename std::set<T2>::iterator T2_set_itr;
			//Go through all weblinks and insert them into the result_vec, 
			//check for duplicates too, during the insertion
			for(T2_set_itr = T2_set.begin(); 
				T2_set_itr != T2_set.end(); 
				T2_set_itr++
				) {
				temp_set.insert((*T2_set_itr)->getWebLink());
			}
		}
	}
	typename std::set<T1>::iterator set_itr;
	for(set_itr = temp_set.begin(); 
		set_itr != temp_set.end(); 
		set_itr++
		) {
		result_vec.push_back(*set_itr);
	}
	return make_pair(result_vec, true);
}

//For OR command (OVERLOADED FUNCTION FOR STRING AND WEBPAGE*)
template <class T2>
const typename std::pair< std::vector<std::string>, bool > unionT(
	std::vector<std::string>& command_vec, 
	std::map< std::string, std::set<T2> >& T1_map
	) {
	typename std::vector<std::string> result_vec;
	typename std::set<std::string> temp_set;
	for(int i = 1; i < int(command_vec.size()); i++) {
		//convert all chars into lowercase
		for(int j = 0; j < int(command_vec[i].size()); j++) {
			command_vec[i][j] = tolower(command_vec[i][j]);
		}
		//iterator to the word in word_map
		typename std::map< std::string, std::set<T2> >::iterator T1_map_itr = T1_map.find(command_vec[i]);
		if(T1_map_itr != T1_map.end()) {
			typename std::set<T2> T2_set = T1_map_itr->second; //Set of all weblinks that contain that word
			typename std::set<T2>::iterator T2_set_itr;
			//Go through all weblinks and insert them into the result_vec, 
			//check for duplicates too, during the insertion
			for(T2_set_itr = T2_set.begin(); 
				T2_set_itr != T2_set.end(); 
				T2_set_itr++
				) {
				temp_set.insert((*T2_set_itr)->getWebLink());
			}
		}
	}
	typename std::set<std::string>::iterator set_itr;
	for(set_itr = temp_set.begin(); 
		set_itr != temp_set.end(); 
		set_itr++
		) {
		result_vec.push_back(*set_itr);
	}
	return make_pair(result_vec, true);
}

//for INCOMING command
template <class T2>
const typename std::pair<std::vector<std::string>, bool> getIncomingLinks(
	std::vector<std::string>& command_vec,
	const std::map<std::string, T2>& T2_map
	) {
	typename std::map<std::string, T2>::const_iterator T2_map_itr = T2_map.find(command_vec[1]);
	bool isFound = false;
	if(T2_map_itr != T2_map.end()) {
		isFound = true;
		return make_pair((T2_map_itr->second)->getIncomingLinkVec(), isFound);
	}
	if(!isFound) {
		typename std::vector<std::string> incomingLinkVec;
		return make_pair(incomingLinkVec, isFound);
	}
}

//for OUTGOING COMMAND
template <class T2>
const typename std::pair<std::vector<std::string>, bool> getOutgoingLinks(
	std::vector<std::string>& command_vec,
	const std::map<std::string, T2>& T2_map
	) {
	typename std::map<std::string, T2>::const_iterator T2_map_itr = T2_map.find(command_vec[1]);
	bool isFound = false;
	if(T2_map_itr != T2_map.end()) {
		isFound = true;
		return make_pair((T2_map_itr->second)->getOutgoingLinkVec(), isFound);
	}
	if(!isFound) {
		typename std::vector<std::string> outgoingLinkVec;
		return make_pair(outgoingLinkVec, isFound);
	}
}

//for single word query 
template <class T1, class T2>
const typename std::vector<T1> search(
	T1& word, 
	std::map< T1, std::set<T2> >& T1_map
	) {
	typename std::vector<T1> result_vec;
	typename std::map< T1, std::set<T2> >::iterator T1_map_itr = T1_map.find(word);
	if(T1_map_itr != T1_map.end()) {
		typename std::set<T2> T2_set = T1_map_itr->second;
		typename std::set<T2>::iterator T2_set_itr;
		for(T2_set_itr = T2_set.begin(); 
			T2_set_itr != T2_set.end(); 
			T2_set_itr++
			) {
			result_vec.push_back((*T2_set_itr)->getWebLink());
		}
	}
	return result_vec;
}

//for single word query (OVERLOADED FUNCTION FOR STRING AND WEBPAGE*)
template <class T2>
const typename std::vector<std::string> search(
	std::string& word, 
	std::map< std::string, std::set<T2> >& T1_map
	) {
	for(int i = 0; i < int(word.length()); i++) {
		word[i] = tolower(word[i]);
	}
	typename std::vector<std::string> result_vec;
	typename std::map< std::string, std::set<T2> >::iterator T1_map_itr = T1_map.find(word);
	if(T1_map_itr != T1_map.end()) {
		typename std::set<T2> T2_set = T1_map_itr->second;
		typename std::set<T2>::iterator T2_set_itr;
		for(T2_set_itr = T2_set.begin(); 
			T2_set_itr != T2_set.end(); 
			T2_set_itr++
			) {
			result_vec.push_back((*T2_set_itr)->getWebLink());
		}
	}
	return result_vec;
}

//to print out the number of matched files and matched files line by line
template <class T1>
void outputResults(
	std::vector<T1>& results,
	std::ofstream& output
	) {
	if(results.size() > 0) {
		output << int(results.size()) << std::endl;
		typename std::vector<T1>::iterator results_itr;
		for(results_itr = results.begin(); 
			results_itr != results.end(); 
			results_itr++
			) {
			output << *(results_itr) << std::endl;
		}
	} else {
		output << 0 << std::endl;
	}
}
/*------------- END QUERY HANDLING FUNCTIONS -------------*/

#endif