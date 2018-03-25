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
				for(
						T2_set_itr = T2_set.begin(); 
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
		for(
				query_map_itr = query_map.begin(); 
				query_map_itr != query_map.end(); 
				query_map_itr++
				) {
			if(query_map_itr->second == (int(command_vec.size()) - 1)) {
				result_vec.push_back(query_map_itr->first);
			}
		}
		return make_pair(result_vec, true);
	}

	//For AND command (OVERLOADED FUNCTION FOR STRING AND WEBPAGE*)
	const std::pair< std::vector<std::string>, bool > intersectT(
		std::vector<std::string>& command_vec, 
		std::map< std::string, std::set<WebPage*> >& word_map
		) {
		std::map<std::string, int> query_map;
		std::map<std::string, int>::iterator query_map_itr; 
		std::vector<std::string> result_vec;
		//Traverse each word in command vec
		for(int i = 1; i < int(command_vec.size()); i++) {
			//convert all chars to lowercase
			for(int j = 0; j < int(command_vec[i].size()); j++) {
				command_vec[i][j] = tolower(command_vec[i][j]);
			}
			//Find word in word_map O(logn)
			std::map< std::string, std::set<WebPage*> >::iterator word_map_itr = word_map.find(command_vec[i]);
			if(word_map_itr != word_map.end()) {
				std::set<WebPage*> wordwebpage_set = word_map_itr->second;
				std::set<WebPage*>::iterator wordwebpage_itr;
				//Check if the same weblink exists for each word O(m) 
				//where m is the number of weblinks in my result set
				for(
						wordwebpage_itr = wordwebpage_set.begin(); 
						wordwebpage_itr != wordwebpage_set.end(); 
						wordwebpage_itr++
						) {
					query_map_itr = query_map.find((*wordwebpage_itr)->getWebLink());
					//If query_map already has the weblink as a key, increment its count
					//else create a new key: weblink, value: count pair
					if(query_map_itr != query_map.end()) {
						(query_map_itr->second)++;
					} else {
						query_map.insert(make_pair((*wordwebpage_itr)->getWebLink(), 1));
					}
				}
			} else {
				break;
			}
		}
		//Any weblinks that have command_vec - 1 # of counts means it contains
		//all required query keywords in AND
		for(
				query_map_itr = query_map.begin(); 
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
				for(
						T2_set_itr = T2_set.begin(); 
						T2_set_itr != T2_set.end(); 
						T2_set_itr++
						) {
					temp_set.insert((*T2_set_itr)->getWebLink());
				}
			}
		}
		for(
				typename std::set<T1>::iterator set_itr = temp_set.begin(); 
				set_itr != temp_set.end(); 
				set_itr++
				) {
			result_vec.push_back(*set_itr);
		}
		return make_pair(result_vec, true);
	}

	//For OR command (OVERLOADED FUNCTION FOR STRING AND WEBPAGE*)
	const std::pair< std::vector<std::string>, bool > unionT(
		std::vector<std::string>& command_vec, 
		std::map< std::string, std::set<WebPage*> >& word_map
		) {
		std::vector<std::string> result_vec;
		std::set<std::string> temp_set;
		for(int i = 1; i < int(command_vec.size()); i++) {
			//convert all chars into lowercase
			for(int j = 0; j < int(command_vec[i].size()); j++) {
				command_vec[i][j] = tolower(command_vec[i][j]);
			}
			//iterator to the word in word_map
			std::map< std::string, std::set<WebPage*> >::iterator word_map_itr = word_map.find(command_vec[i]);
			if(word_map_itr != word_map.end()) {
				std::set<WebPage*> wordwebpage_set = word_map_itr->second; //Set of all weblinks that contain that word
				std::set<WebPage*>::iterator wordwebpage_itr;
				//Go through all weblinks and insert them into the result_vec, 
				//check for duplicates too, during the insertion
				for(
						wordwebpage_itr = wordwebpage_set.begin(); 
						wordwebpage_itr != wordwebpage_set.end(); 
						wordwebpage_itr++
						) {
					temp_set.insert((*wordwebpage_itr)->getWebLink());
				}
			}
		}
		for(
				std::set<std::string>::iterator set_itr = temp_set.begin(); 
				set_itr != temp_set.end(); 
				set_itr++
				) {
			result_vec.push_back(*set_itr);
		}
		return make_pair(result_vec, true);
	}

	//for INCOMING command
	template <class T1, class T2>
	const typename std::pair<std::vector<T1>, bool> getIncomingLinks(
		std::vector<T1>& command_vec,
		const std::set<T2>& T2_set
		) {
		typename std::set<T2>::iterator T2_set_itr;
		bool isFound = false;
		for(
				T2_set_itr = T2_set.begin(); 
				T2_set_itr != T2_set.end(); 
				T2_set_itr++
				) {
			if((*T2_set_itr)->getWebLink() == command_vec[1]) {
				isFound = true;
				return make_pair((*T2_set_itr)->getIncomingLinkVec(), isFound);
			}
		}
		if(!isFound) {
			typename std::vector<T1> outgoingLinkVec;
			return make_pair(outgoingLinkVec, isFound);
		}
	}

	//for OUTGOING COMMAND
	template <class T1, class T2>
	const typename std::pair<std::vector<T1>, bool> getOutgoingLinks(
		std::vector<T1>& command_vec,
		const std::set<T2>& T2_set
		) {
		typename std::set<T2>::iterator T2_set_itr;
		bool isFound = false;
		for(
				T2_set_itr = T2_set.begin(); 
				T2_set_itr != T2_set.end(); 
				T2_set_itr++
				) {
			if((*T2_set_itr)->getWebLink() == command_vec[1]) {
				isFound = true;
				return make_pair((*T2_set_itr)->getOutgoingLinkVec(), isFound);
			}
		}
		if(!isFound) {
			typename std::vector<T1> outgoingLinkVec;
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
			for(
					T2_set_itr = T2_set.begin(); 
					T2_set_itr != T2_set.end(); 
					T2_set_itr++
					) {
				result_vec.push_back((*T2_set_itr)->getWebLink());
			}
		}
		return result_vec;
	}

	//for single word query (OVERLOADED FUNCTION FOR STRING AND WEBPAGE*)
	const std::vector<std::string> search(
		std::string& word, 
		std::map< std::string, std::set<WebPage*> >& word_map
		) {
		for(int i = 0; i < int(word.length()); i++) {
			word[i] = tolower(word[i]);
		}
		std::vector<std::string> result_vec;
		std::map< std::string, std::set<WebPage*> >::iterator word_map_itr = word_map.find(word);
		if(word_map_itr != word_map.end()) {
			std::set<WebPage*> wordwebpage_set = word_map_itr->second;
			std::set<WebPage*>::iterator wordwebpage_itr;
			for(
					wordwebpage_itr = wordwebpage_set.begin(); 
					wordwebpage_itr != wordwebpage_set.end(); 
					wordwebpage_itr++
					) {
				result_vec.push_back((*wordwebpage_itr)->getWebLink());
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
			for(
					results_itr = results.begin(); 
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