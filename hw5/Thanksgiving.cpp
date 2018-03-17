#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include "LengthMismatch.h"
#include "qsort.h"

using namespace std;

vector<pair<int, int>> assignPlates(
            vector<int> turkeys, 
            vector<int> potatoes) 
            {
    //Variables:
    vector<pair<int, int>> result_vec; 
    int total_calories = 0; 

    //If # of turkey don't match potatoes, throw LengthMismatch exception
    if(int(turkeys.size()) != int(potatoes.size())) { 
        throw LengthMismatch(int(turkeys.size()), int(potatoes.size())); 
    } else {
        for(vector<int>::iterator itr = turkeys.begin(); itr != turkeys.end(); itr++) {
            total_calories += *itr;
        }
        for(vector<int>::iterator itr = potatoes.begin(); itr != potatoes.end(); itr++) {
            total_calories += *itr;
        }
        int calories_per_plate = (total_calories / int(turkeys.size()));
        QuickSort(turkeys, less<int>()); //O(nlogn), worst - O(n^2)
        QuickSort(potatoes, less<int>()); //O(nlogn), worst - O(n^2)
        int start_idx = 0;
        int end_idx = int(turkeys.size()) - 1;
        while(end_idx >= 0 && start_idx < int(turkeys.size())) {
            if((turkeys[start_idx] + potatoes[end_idx]) == calories_per_plate) {
                result_vec.push_back(make_pair(turkeys[start_idx], potatoes[end_idx]));
                start_idx++; end_idx--;
            } else {
                return vector<pair<int, int>>();
            }
        }
        return result_vec;
    }
}