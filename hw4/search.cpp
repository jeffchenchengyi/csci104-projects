#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <set>
#include <map>
#include "webpage.h"

using namespace std;

/*------------- START TOKENIZATION/PARSING FUNCTIONS -------------*/
	bool isCloseParen(string x) {
	    return (x == ")") ? true : false;
	}

	bool isOpenParen(string x) {
	    return (x == "(") ? true : false;
	}

	bool isCloseBrack(string x) {
	    return (x == "]") ? true : false;
	}

	bool isOpenBrack(string x) {
	    return (x == "[") ? true : false;
	}

	//Inserts token into word_map
	void updateWordMap(
			WebPage* webpage_ptr, 
			map< string, set<WebPage*> >& word_map,
			const string& token
			) {
		if(int(token.length()) == 0) return; //check if token is empty
		//Iterator to go through word_map
		map< string, set<WebPage*> >::iterator word_map_itr = word_map.find(token);
		//If the word exists in the map:
		if(word_map_itr != word_map.end()) {
			(word_map_itr->second).insert(webpage_ptr);
		}
		//If the word doesnt exist in map: 
		else {
			set<WebPage*> newWebPage_set; //Create new set with pointer to WebPage obj
			newWebPage_set.insert(webpage_ptr);
			word_map.insert(word_map_itr, make_pair(token, newWebPage_set));
		}
	}

	//Store all alphanum into token until special char
	void readWord(
			ifstream& webpage_file, 
			string& token
			) {
		while(
				webpage_file.peek() != EOF && 
				isalnum(webpage_file.peek())
				) {
			char curr_char;
			webpage_file.get(curr_char);
			token.append(string(1, tolower(curr_char))); //Store lower case version
		}
	}

	void readLink(
			ifstream& webpage_file, 
			string& token
			) {
		while(
				webpage_file.peek() != EOF && 
				!isCloseParen(string(1, webpage_file.peek()))
				) {
			char curr_char;
			webpage_file.get(curr_char);
			token.append(string(1, curr_char)); //Store original version of link
		}
	}

	void createMdLink(
			WebPage* webpage_ptr, 
			ifstream& webpage_file,
			const set< WebPage* >& webpage_set
			) {
		string mdlink;
		readLink(webpage_file, mdlink);
		//Find the WebPage obj that mdlink directs to
		//If the WebPage obj is not found, only the outgoing link 
		//for current webpage is added
		for(set< WebPage* >::iterator webpage_itr = webpage_set.begin(); 
	    		webpage_itr != webpage_set.end(); 
	    			webpage_itr++) {
			if(((*webpage_itr)->getWebLink()) == mdlink) {
				(*webpage_itr)->addIncomingLink(webpage_ptr->getWebLink()); //Add incoming link for target webpage
				break;
			}
		}
		webpage_ptr->addOutgoingLink(mdlink); //Adding outgoing link for current webpage
		char openParen;
		webpage_file.get(openParen); //Remove the closing paren in the ifstream obj
	}

	//Handles anchortext, when '[' is seen from checkSpecChar()
	void createAnchortext(
			WebPage* webpage_ptr, 
			map< string, set<WebPage*> >& word_map,
			ifstream& webpage_file,
			char special_char
			) {
		//while loop is used to ensure cases like [word1 word2 word3] are read well
		while(!isCloseBrack(string(1, special_char))) {
			string anchortext;
			readWord(webpage_file, anchortext);
			updateWordMap(webpage_ptr, word_map, anchortext);
			webpage_file.get(special_char); //Extract closing bracket
		}
	}

	//Remove special chars from ifstream obj & checks for
	//MD Links 
	void checkSpecChar(
			WebPage* webpage_ptr, 
			map< string, set<WebPage*> >& word_map,
			ifstream& webpage_file,
			const set< WebPage* >& webpage_set
			) {
		while(
				webpage_file.peek() != EOF && 
				!isalnum(webpage_file.peek())
				) {
			char special_char;
			webpage_file.get(special_char); //Extract the special char from ifstream obj
			if(isOpenParen(string(1, special_char))) {
				createMdLink(webpage_ptr, webpage_file, webpage_set);
			}
			else if(isOpenBrack(string(1, special_char))) {
				createAnchortext(webpage_ptr, word_map, webpage_file, special_char);
			}
		}
	}

	void tokenize(
			WebPage* webpage_ptr, 
			ifstream& webpage_file, 
			map< string, set<WebPage*> >& word_map,
			const set< WebPage* >& webpage_set
			) {
		while(webpage_file.peek() != EOF) {
			string token; //To store word tokens
			readWord(webpage_file, token); //Updated token with a word
			updateWordMap(webpage_ptr, word_map, token); //Update word map with new word
			checkSpecChar(webpage_ptr, word_map, webpage_file, webpage_set); //Check what the special char is
		}
	}
/*------------- END TOKENIZATION/PARSING FUNCTIONS-------------*/

/*------------- START QUERY HANDLING FUNCTIONS -------------*/
	void displayWebPage(string weblink, ofstream& output) {
		ifstream webpage_file(weblink.c_str());
		if(!webpage_file) {
    		output << "Invalid query" << endl;
        	return;
    	}
    	output << weblink << endl;
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

	const pair< set<string>, bool > intersectString(
			vector<string>& command_vec, 
			map< string, set<WebPage*> >& word_map
			) {
		map<string, int> query_map;
		map<string, int>::iterator query_map_itr; 
		set<string> result_set;
		for(int i = 1; i < int(command_vec.size()); i++) {
			for(int j = 0; j < int(command_vec[i].size()); j++) {
				command_vec[i][j] = tolower(command_vec[i][j]);
			}
			map< string, set<WebPage*> >::iterator word_map_itr = word_map.find(command_vec[i]);
			if(word_map_itr != word_map.end()) {
				set<WebPage*> wordwebpage_set = word_map_itr->second;
				set<WebPage*>::iterator wordwebpage_itr;
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
				result_set.insert(query_map_itr->first);
			}
		}
		return make_pair(result_set, true);
	}

	const pair< set<string>, bool > unionString(
			vector<string>& command_vec, 
			map< string, set<WebPage*> >& word_map
			) {
		set<string> result_set;
		for(int i = 1; i < int(command_vec.size()); i++) {
			for(int j = 0; j < int(command_vec[i].size()); j++) {
				command_vec[i][j] = tolower(command_vec[i][j]);
			}
			map< string, set<WebPage*> >::iterator word_map_itr = word_map.find(command_vec[i]);
			if(word_map_itr != word_map.end()) {
				set<WebPage*> wordwebpage_set = word_map_itr->second;
				set<WebPage*>::iterator wordwebpage_itr;
				for(
						wordwebpage_itr = wordwebpage_set.begin(); 
						wordwebpage_itr != wordwebpage_set.end(); 
						wordwebpage_itr++
						) {
					result_set.insert((*wordwebpage_itr)->getWebLink());
				}
			}
		}
		return make_pair(result_set, true);
	}

	const pair< set<string>, bool > getIncomingLinks(
			vector<string>& command_vec,
			const set< WebPage* >& webpage_set
			) {
		set< WebPage* >::iterator webpage_itr;
		bool isFound = false;
		for(
				webpage_itr = webpage_set.begin(); 
				webpage_itr != webpage_set.end(); 
				webpage_itr++
				) {
			if((*webpage_itr)->getWebLink() == command_vec[1]) {
				isFound = true;
				return make_pair((*webpage_itr)->getIncomingLinkSet(), isFound);
			}
		}
		if(!isFound) {
			set<string> outgoingLinkSet;
			return make_pair(outgoingLinkSet, isFound);
		}
	}

	const pair< set<string>, bool > getOutgoingLinks(
			vector<string>& command_vec,
			const set< WebPage* >& webpage_set
			) {
		set< WebPage* >::iterator webpage_itr;
		bool isFound = false;
		for(
				webpage_itr = webpage_set.begin(); 
				webpage_itr != webpage_set.end(); 
				webpage_itr++
				) {
			if((*webpage_itr)->getWebLink() == command_vec[1]) {
				isFound = true;
				return make_pair((*webpage_itr)->getOutgoingLinkSet(), isFound);
			}
		}
		if(!isFound) {
			set<string> outgoingLinkSet;
			return make_pair(outgoingLinkSet, isFound);
		}
	}

	const set<string> searchWord(
			string& word, 
			map< string, set<WebPage*> >& word_map
			) {
		for(int i = 0; i < int(word.length()); i++) {
			word[i] = tolower(word[i]);
		}
		set<string> result_set;
		map< string, set<WebPage*> >::iterator word_map_itr = word_map.find(word);
		if(word_map_itr != word_map.end()) {
			set<WebPage*> wordwebpage_set = word_map_itr->second;
			set<WebPage*>::iterator wordwebpage_itr;
			for(
					wordwebpage_itr = wordwebpage_set.begin(); 
					wordwebpage_itr != wordwebpage_set.end(); 
					wordwebpage_itr++
					) {
				result_set.insert((*wordwebpage_itr)->getWebLink());
			}
		}
		return result_set;
	}

	void outputResults(
			const set<string>& results,
			ofstream& output
			) {
		if(results.size() > 0) {
			output << int(results.size()) << endl;
			set<string>::iterator results_itr;
			for(
					results_itr = results.begin(); 
					results_itr != results.end(); 
					results_itr++
					) {
				output << *(results_itr) << endl;
			}
		} else {
			output << 0 << endl;
		}
	}

	void analyzeQuery(
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
		set<string> weblink_set;
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
					pair< set<string>, bool > results = make_pair(weblink_set, false); 
					if(command_vec[0] == "AND") {
						results = intersectString(command_vec, word_map);
					} 
					else if(command_vec[0] == "OR") {
						results = unionString(command_vec, word_map);
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
				weblink_set = searchWord(command_vec[0], word_map);
				outputResults(weblink_set, output);
			}
		} else {
			//If query was just trailing whitespaces
			output << "Invalid query" << endl;
		} 
	}
/*------------- END QUERY HANDLING FUNCTIONS -------------*/

int main(int argc, char* argv[])
{
/*------------- START INITIALIZE REQUIRED FILES -------------*/
    //To check if the input, query, and output file was also included as a command line parameter
    if (argc < 4) {
       cerr << "Please provide input, query, and output file" << endl;
       return -1;
    }

    ifstream input(argv[1]);
    ifstream query(argv[2]);
    ofstream output(argv[3]);

    //If the input file given could not be found or could not be open
    if(input.fail()) {
        cout << "Input file could not be open." << endl;
        return 1;
    }

    //If the query file given could not be found or could not be open
    if(query.fail()) {
        cout << "Query file could not be open." << endl;
        return 1;
    }

    //If the output file given could not be found or could not be open
    if(output.fail()) {
        cout << "Output file could not be open." << endl;
        return 1;
    }
/*------------- END INITIALIZE REQUIRED FILES -------------*/

/*------------- START MAIN VARIABLES -------------*/
    string weblink; //"data/webpg1.txt", "data/webpg2.txt", "data/webpg3.txt"
    set< WebPage* > webpage_set; //{webpg1obj_ptr, webpg2obj_ptr, webpg3obj_ptr} 
 	map< string, set<WebPage*> > word_map; //{"yo"=> {webpg1obj_ptr, webpg2obj_ptr, webpg3obj_ptr}}
/*------------- END MAIN VARIABLES -------------*/

/*------------- START ALLOCATE WEBPAGE DYNAMIC MEM -------------*/
    while(getline(input, weblink)) {
    	if(!weblink.empty()) {
    		WebPage* webpage_ptr = new WebPage(weblink);
    		webpage_set.insert(webpage_ptr);
    	}
    }
/*------------- END ALLOCATE WEBPAGE DYNAMIC MEM -------------*/

/*------------- START TOKENIZATION/PARSING OF WEBPAGES-------------*/
    for(set< WebPage* >::iterator webpage_itr = webpage_set.begin(); 
    		webpage_itr != webpage_set.end(); 
    			webpage_itr++) {
    	ifstream webpage_file(((*webpage_itr)->getWebLink()).c_str()); //why must put c_str()???
    	if(!webpage_file) {
    		cout << "Web Page file could not be open." << endl;
        	return 1;
    	}
    	tokenize(*(webpage_itr), webpage_file, word_map, webpage_set);
	}
/*------------- END TOKENIZATION/PARSING OF WEBPAGES-------------*/

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

/*------------- START DEALLOCATE WEBPAGE DYNAMIC MEM -------------*/
	for(set< WebPage* >::iterator webpage_itr = webpage_set.begin(); 
    		webpage_itr != webpage_set.end(); 
    			webpage_itr++) {
    	delete (*webpage_itr);
	}
/*------------- END DEALLOCATE WEBPAGE DYNAMIC MEM -------------*/
    return 0;
}