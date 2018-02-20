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

/*------------- START TOKENIZATION/PASRSING FUNCTIONS -------------*/
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
			word_map.insert(make_pair(token, newWebPage_set));
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
		for(set< WebPage* >::iterator webpage_itr = webpage_set.begin(); 
	    		webpage_itr != webpage_set.end(); 
	    			webpage_itr++) {
			if(((*webpage_itr)->getWebLink()) == mdlink) {
				(*webpage_itr)->addIncomingLink(webpage_ptr); //Add incoming link for target webpage
				webpage_ptr->addOutgoingLink(*webpage_itr); //Adding outgoing link for current webpage
				break;
			}
		}
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
		string anchortext;
		//anchortext.append(string(1, special_char)); //To add "[" to anchor text
		readWord(webpage_file, anchortext);
		webpage_file.get(special_char); //Extract closing bracket
		//anchortext.append(string(1, special_char)); //To add "]" to anchor text
		updateWordMap(webpage_ptr, word_map, anchortext);
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
/*------------- END TOKENIZATION/PASRSING FUNCTIONS-------------*/

/*------------- START QUERY HANDLING FUNCTIONS -------------*/
	void analyzeQuery(
			string query_command, 
			const set< WebPage* >& webpage_set, 
			const map< string, set<WebPage*> >& word_map,
			ofstream& output
			) {
		vector<string> command_vec;
		for(int i = 0; i < int(query_command.length()); i++) {
			string command_token;
			while(
					i < int(query_command.length()) && 
					!isblank(query_command[i])
					) {
				command_token.append(string(1, tolower(query_command[i])));
				i++;
			}
			command_vec.push_back(command_token);
		}
		cout << command_vec.size() << endl;
		if(command_vec[0] == "AND") {
			//intersectString(command_vec, word_map);
		} 
		else if(command_vec[0] == "OR") {
			//unionString(command_vec, word_map);
		} 
		else if(command_vec[0] == "PRINT") {
			//displayWebPage(command_vec);
		} 
		else if(command_vec[0] == "INCOMING") {
			//getIncomingLinks(command_vec, webpage_set);
		} 
		else if(command_vec[0] == "OUTGOING") {
			//getOutgoingLinks(command_vec, webpage_set);
		} 
		else {
			if(command_vec.size() > 1) {
				output << "Invalid query" << endl;
			} else {
				//searchWord(command_vec[0]);
			}
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
    	//ifstream webpage_file("data/text1.txt");
    	if(!webpage_file) {
    		cout << "Web Page file could not be open." << endl;
        	return 1;
    	}
    	tokenize(*(webpage_itr), webpage_file, word_map, webpage_set);
	}
/*------------- END TOKENIZATION/PARSING OF WEBPAGES-------------*/

/*------------- START QUERY HANDLING-------------*/
	/*
	for(map< string, set<WebPage*> >::iterator word_map_itr = word_map.begin(); 
    		word_map_itr != word_map.end(); 
    			word_map_itr++) {
		cout << endl;
    	cout << word_map_itr->first << " => " << endl;
    	for(set< WebPage* >::iterator webpage_itr = (word_map_itr->second).begin(); 
    		webpage_itr != (word_map_itr->second).end(); 
    			webpage_itr++) {
    		cout << (*webpage_itr)->getWebLink() << endl;
    	}
    	cout << endl;
	}
	*/
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