#ifndef FUNCTOR_H
#define FUNCTOR_H
#include <string>

struct NumStrComp {
    int stringSum(const std::string& str); //Helper function to calculate sum of the alphanumerics in a string
    bool operator()(const std::string& lhs, const std::string& rhs);
};

#endif