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

        //Member functions
};

#endif