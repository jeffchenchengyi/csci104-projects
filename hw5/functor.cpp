#include <iostream>
#include <stdlib.h>
#include "functor.h"
#include <string>

using namespace std;

//Sums up all the int values of the digits according to HW5:
//("0" = 0, "1" = 1, "2" = 2, ..., "9" = 9, "A" = 10, "B" = 11, "C" = 12, ..., "Z" = 35
int NumStrComp::stringSum(const string& str) {
	int sum = 0;
	for(int i = 0; i < int(str.size()); i++) {
   		if(isalnum(str[i])) {
            if(isalpha(str[i])) {
            	sum += (int(toupper(str[i])) - int('0') - 7); 
            }
            else if(isdigit(str[i])) {
				sum += (int(str[i]) - int('0')); 
			}
        }
   	}
   	return sum;
}

bool NumStrComp::operator()(const string& lhs, const string& rhs) {
	int lhs_sum = stringSum(lhs);
	int rhs_sum = stringSum(rhs);
	if(lhs_sum != rhs_sum) {
		return lhs_sum < rhs_sum;
	} else {
	    // Uses string's built in operator< 
	    // to do lexicographic (alphabetical) comparison
	    return lhs < rhs; 
	}
}