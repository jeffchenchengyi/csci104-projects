#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <set>
#include <map>
#include "crawl.h"
using namespace std;

//Constructor for crawler.cpp, input is the seed file, output is the new index file
Crawl::Crawl(ifstream& input, ofstream& output) {
	string weblink; //"data/webpg1.txt", "data/webpg2.txt", "data/webpg3.txt"
	set<string> visited_weblink_set;
	vector<string> webpages_explored;

	//Start of crawling using DFS algo
    while(getline(input, weblink)) {
    	if(!weblink.empty()) {
    		DFScrawl(visited_weblink_set, webpages_explored, weblink);
    	}
    }
    
    //Output all files explored in order to output file
    vector<string>::iterator vec_itr;
    for(vec_itr = webpages_explored.begin(); 
    	vec_itr != webpages_explored.end(); 
    	vec_itr++) {
    	output << *vec_itr << endl;
	}
}

Crawl::~Crawl() {
}

bool Crawl::isCloseParen(string x) {
    return (x == ")") ? true : false;
}

bool Crawl::isOpenParen(string x) {
    return (x == "(") ? true : false;
}

bool Crawl::isCloseBrack(string x) {
    return (x == "]") ? true : false;
}

bool Crawl::isOpenBrack(string x) {
    return (x == "[") ? true : false;
}

//DFS algorthm to explore links to new webpages
void Crawl::DFScrawl(
	set<string>& visited_weblink_set,
	vector<string>& webpages_explored, 
	string curr_weblink) {

	//Mark vertex/current weblink as visited
	if(checkValidFile(curr_weblink)) {
		visited_weblink_set.insert(curr_weblink);

		//Process the webpage and get all the mdlinks in the page
		vector<string> mdlink_vec;
		tokenize(curr_weblink, mdlink_vec);
		webpages_explored.push_back(curr_weblink);

		//Visit neighbours
		vector<string>::iterator vec_itr;
		//Weblinks in predecessor_weblinks are the neighbouring vertices
		for(vec_itr = mdlink_vec.begin();
			vec_itr != mdlink_vec.end();
			vec_itr++;
			) {
			if(visited_weblink_set.find(*vec_itr) == visited_weblink_set.end()) {
				DFScrawl(visited_weblink_set, webpages_explored, *vec_itr);
			}
		}
	}
}

//Checks if the link provided is valid
bool Crawl::checkValidFile(string& weblink) {
	ifstream webpage_file(weblink.c_str()); //why must put c_str()???
    if(!webpage_file) {
    	cerr << "Web Page file could not be open." << endl;
    	return false;
    } else {
    	return true;
    }
}

//to parse all the words in the text to valid string tokens in word_map
void Crawl::tokenize(
	const string& curr_weblink
	vector<string>& mdlink_vec) {
	ifstream webpage_file(curr_weblink.c_str());
    while(webpage_file.peek() != EOF) {
        string token; //To store word tokens
        readWord(webpage_file, token); //Updated token with a word
        checkSpecChar(webpage_file, mdlink_vec); //Check what the special char is
    }
}

//Store all alphanum into token until special char
void Crawl::readWord(
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

//to get the link after anchor text in parentheses
void Crawl::readLink(
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

//Remove special chars from ifstream obj & checks for
//MD Links 
void Crawl::checkSpecChar(
    ifstream& webpage_file,
    vector<string>& mdlink_vec
    ) {
    while(webpage_file.peek() != EOF && 
        !isalnum(webpage_file.peek())
        ) {
        char special_char;
        webpage_file.get(special_char); //Extract the special char from ifstream obj
        if(isOpenParen(string(1, special_char))) {
            createMdLink(webpage_file, mdlink_vec);
        }
        else if(isOpenBrack(string(1, special_char))) {
            createAnchortext(webpage_file, special_char);
        }
    }
}

//to store mdlinks 
void Crawl::createMdLink(
    ifstream& webpage_file,
    vector<string>& mdlink_vec
    ) {
    string mdlink;
    readLink(webpage_file, mdlink);
    mdlink_vec.push_back(mdlink); //Store the mdlink in mdlink_vec
    char openParen;
    webpage_file.get(openParen); //Remove the closing paren in the ifstream obj
}

//Handles anchortext, when '[' is seen from checkSpecChar()
void Crawl::createAnchortext(
    ifstream& webpage_file,
    char special_char
    ) {
    //while loop is used to ensure cases like [word1 word2 word3] are read well
    while(!isCloseBrack(string(1, special_char))) {
        string anchortext;
        readWord(webpage_file, anchortext);
        webpage_file.get(special_char); //Extract closing bracket
    }
}