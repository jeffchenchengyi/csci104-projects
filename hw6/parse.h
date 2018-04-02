#ifndef PARSE_H
#define PARSE_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <set>
#include <map>
#include "webpage.h"
#include "queryhandler.h"

class Parse {
    public:
        Parse(std::ifstream& input, 
            std::ifstream& query, 
            std::ofstream& output, 
            double RESTART_PROBABILITY, 
            int STEP_NUMBER); //For search.cpp
        virtual ~Parse();
        void tokenize(
            WebPage* webpage_ptr, 
            std::ifstream& webpage_file, 
            std::map< std::string, std::set<WebPage*> >& word_map,
            const std::map< std::string, WebPage* >& webpage_map
            );
        bool isCloseParen(std::string x);
        bool isOpenParen(std::string x);
        bool isCloseBrack(std::string x);
        bool isOpenBrack(std::string x);
    
    private:
        //Member variables
        //{"data/text1.txt" => webpg1obj_ptr, "data/text2.txt" => webpg2obj_ptr, "data/text3.txt" => webpg3obj_ptr}
        std::map< std::string, WebPage* > webpage_map;  
        //{"yo"=> {webpg1obj_ptr, webpg2obj_ptr, webpg3obj_ptr}}
        std::map< std::string, std::set<WebPage*> > word_map; 

        //Member functions
        void readWord(
            std::ifstream& webpage_file, 
            std::string& token
            );
        void updateWordMap(
            WebPage* webpage_ptr, 
            std::map< std::string, std::set<WebPage*> >& word_map, 
            const std::string& token
            );
        void checkSpecChar(
            WebPage* webpage_ptr, 
            std::map< std::string, std::set<WebPage*> >& word_map,
            std::ifstream& webpage_file,
            const std::map< std::string, WebPage* >& webpage_map
            );
        void createMdLink(
            WebPage* webpage_ptr, 
            std::ifstream& webpage_file,
            const std::map< std::string, WebPage* >& webpage_map
            );
        void createAnchortext(
            WebPage* webpage_ptr, 
            std::map< std::string, std::set<WebPage*> >& word_map,
            std::ifstream& webpage_file,
            char special_char
            );
        void readLink(
            std::ifstream& webpage_file, 
            std::string& token
            );
};

#endif