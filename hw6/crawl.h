#ifndef CRAWL_H
#define CRAWL_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <set>
#include <map>

class Crawl {
    public:
        Crawl(std::ifstream& input, std::ofstream& output); //For crawler.cpp
        virtual ~Crawl();
    
    private:
        //Member variables
        std::set<std::string> visited_weblink_set; //Contains all the visited weblinks for O(lgn) search
        std::vector<std::string> webpages_explored; //Contains vector of weblink strings to be used to print out to output

        //Member functions
        bool isCloseParen(std::string x);
        bool isOpenParen(std::string x);
        bool isCloseBrack(std::string x);
        bool isOpenBrack(std::string x);
        void DFScrawl(
        	std::set<std::string>& visited_weblink_set,
			std::vector<std::string>& webpages_explored, 
			std::string curr_weblink);
        bool checkValidFile(std::string& weblink);
        void tokenize(
			const std::string& curr_weblink,
			std::vector<std::string>& mdlink_vec);
        void readWord(
		    std::ifstream& webpage_file, 
		    std::string& token);
        void readLink(
		    std::ifstream& webpage_file, 
		    std::string& token);
        void checkSpecChar(
		    std::ifstream& webpage_file,
		    std::vector<std::string>& mdlink_vec);
        void createMdLink(
		    std::ifstream& webpage_file,
		    std::vector<std::string>& mdlink_vec);
        void createAnchortext(
		    std::ifstream& webpage_file,
		    char special_char);
};

#endif