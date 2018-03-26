#ifndef PARSER_H
#define PARSER_H
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

class Parser {
    public:
        Parser(std::ifstream& input, std::ofstream& output);
        Parser(std::ifstream& input, std::ifstream& query, std::ofstream& output); 
        virtual ~Parser();
        void tokenize(
            WebPage* webpage_ptr, 
            std::ifstream& webpage_file, 
            std::map< std::string, std::set<WebPage*> >& word_map,
            const std::set< WebPage* >& webpage_set
            );
        bool isCloseParen(std::string x);
        bool isOpenParen(std::string x);
        bool isCloseBrack(std::string x);
        bool isOpenBrack(std::string x);
    
    private:
        //Member variables
        std::set< WebPage* > webpage_set; //{webpg1obj_ptr, webpg2obj_ptr, webpg3obj_ptr} 
        std::map< std::string, std::set<WebPage*> > word_map; //{"yo"=> {webpg1obj_ptr, webpg2obj_ptr, webpg3obj_ptr}}

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
            const std::set< WebPage* >& webpage_set
            );
        void createMdLink(
            WebPage* webpage_ptr, 
            std::ifstream& webpage_file,
            const std::set< WebPage* >& webpage_set
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