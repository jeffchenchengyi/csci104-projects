#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <set>
#include <map>
#include "webpage.h"
#include "parse.h"
#include "queryhandler.h"
using namespace std;

/*------------- START ALLOCATE WEBPAGE DYNAMIC MEM -------------*/
//Constructor for search.cpp, query is the file with commands on what to search, output is result
Parse::Parse(
	ifstream& input, 
	ifstream& query, 
	ofstream& output, 
	double RESTART_PROBABILITY, 
	int STEP_NUMBER) {
	string weblink; //"data/webpg1.txt", "data/webpg2.txt", "data/webpg3.txt"
    while(getline(input, weblink)) {
    	if(!weblink.empty()) {
    		WebPage* webpage_ptr = new WebPage(weblink);
    		webpage_map.insert(make_pair(weblink, webpage_ptr));
    	}
    }
    /*------------- START TOKENIZATION/PARSING OF WEBPAGES-------------*/
    map< string, WebPage* >::iterator webpage_itr;
    for(webpage_itr = webpage_map.begin(); 
    	webpage_itr != webpage_map.end(); 
    	webpage_itr++) {
    	ifstream webpage_file((webpage_itr->first).c_str()); //why must put c_str()???
    	if(!webpage_file) {
    		cerr << "Web Page file could not be open." << endl;
    	} else {
    		tokenize((webpage_itr->second), webpage_file, word_map, webpage_map);
    	}
	}
	/*------------- END TOKENIZATION/PARSING OF WEBPAGES-------------*/

	//Handles all queries in query file
	QueryHandler(query, webpage_map, word_map, output, RESTART_PROBABILITY, STEP_NUMBER);
}
/*------------- END ALLOCATE WEBPAGE DYNAMIC MEM -------------*/

/*------------- START DEALLOCATE WEBPAGE DYNAMIC MEM -------------*/
Parse::~Parse() {
	map< string, WebPage* >::iterator webpage_itr;
	for(webpage_itr = webpage_map.begin(); 
    	webpage_itr != webpage_map.end(); 
    	webpage_itr++) {
    	delete webpage_itr->second;
	}
}
/*------------- END DEALLOCATE WEBPAGE DYNAMIC MEM -------------*/

/*------------- START GENERAL TOKENIZATION/PARSING FUNCTIONS -------------*/
bool Parse::isCloseParen(string x) {
    return (x == ")") ? true : false;
}

bool Parse::isOpenParen(string x) {
    return (x == "(") ? true : false;
}

bool Parse::isCloseBrack(string x) {
    return (x == "]") ? true : false;
}

bool Parse::isOpenBrack(string x) {
    return (x == "[") ? true : false;
}

//to parse all the words in the text to valid string tokens in word_map
void Parse::tokenize(
	WebPage* webpage_ptr, 
	ifstream& webpage_file, 
	map< string, set<WebPage*> >& word_map,
	const map< string, WebPage* >& webpage_map
	) {
	while(webpage_file.peek() != EOF) {
		string token; //To store word tokens
		readWord(webpage_file, token); //Updated token with a word
		updateWordMap(webpage_ptr, word_map, token); //Update word map with new word
		checkSpecChar(webpage_ptr, word_map, webpage_file, webpage_map); //Check what the special char is
	}
}

//Store all alphanum into token until special char
void Parse::readWord(
	ifstream& webpage_file, 
	string& token
	) {
	while(webpage_file.peek() != EOF && 
		isalnum(webpage_file.peek())
		) {
		char curr_char;
		webpage_file.get(curr_char);
		token.append(string(1, tolower(curr_char))); //Store lower case version
	}
}

//Inserts token into word_map
void Parse::updateWordMap(
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

//Remove special chars from ifstream obj & checks for
//MD Links 
void Parse::checkSpecChar(
	WebPage* webpage_ptr, 
	map< string, set<WebPage*> >& word_map,
	ifstream& webpage_file,
	const map< string, WebPage* >& webpage_map
	) {
	while(webpage_file.peek() != EOF && 
		!isalnum(webpage_file.peek())
		) {
		char special_char;
		webpage_file.get(special_char); //Extract the special char from ifstream obj
		if(isOpenParen(string(1, special_char))) {
			createMdLink(webpage_ptr, webpage_file, webpage_map);
		}
		else if(isOpenBrack(string(1, special_char))) {
			createAnchortext(webpage_ptr, word_map, webpage_file, special_char);
		}
	}
}

//to store and create the link in parentheses to incominglink/outgoinglinkvec in webpage class
void Parse::createMdLink(
	WebPage* webpage_ptr, 
	ifstream& webpage_file,
	const map< string, WebPage* >& webpage_map
	) {
	string mdlink;
	readLink(webpage_file, mdlink);
	//Find the WebPage obj that mdlink directs to
	//If the WebPage obj is not found, only the outgoing link 
	//for current webpage is added
	map< string, WebPage* >::const_iterator webpage_itr = webpage_map.find(mdlink);
	if(webpage_itr != webpage_map.end()) {
		(webpage_itr->second)->addIncomingLink(webpage_ptr->getWebLink()); //Add incoming link for target webpage
	}
	webpage_ptr->addOutgoingLink(mdlink); //Adding outgoing link for current webpage
	char openParen;
	webpage_file.get(openParen); //Remove the closing paren in the ifstream obj
}

//Handles anchortext, when '[' is seen from checkSpecChar()
void Parse::createAnchortext(
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

//to get the link after anchor text in parentheses
void Parse::readLink(
	ifstream& webpage_file, 
	string& token
	) {
	while(webpage_file.peek() != EOF && 
		!isCloseParen(string(1, webpage_file.peek()))
		) {
		char curr_char;
		webpage_file.get(curr_char);
		token.append(string(1, curr_char)); //Store original version of link
	}
}
/*------------- END GENERAL TOKENIZATION/PARSING FUNCTIONS-------------*/