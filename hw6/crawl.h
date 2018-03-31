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
#include "webpage.h"

class Crawl {
    public:
        Crawl(std::ifstream& input, std::ifstream& query, std::ofstream& output); //For search.cpp
        virtual ~Crawl();
    
    private:
        //Member variables
        std::set< WebPage* > webpage_set; //{webpg1obj_ptr, webpg2obj_ptr, webpg3obj_ptr} 
        std::vector<std::string> webpages_explored; //Contains vector of weblink strings to be used to print out to output

        //Member functions
};

#endif