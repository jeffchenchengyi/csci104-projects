#ifndef QSORT_H
#define QSORT_H
#include <vector>
#include <cmath>

//Swaps two values in a given array
template <class T>
void swapVal(std::vector<T> &myArray, int i, int j) {
    T temp = myArray[i];
    myArray[i] = myArray[j];
    myArray[j] = temp;
}

//Changes median of 3 (start, end, mid) to the last element of array
template <class T, class Comparator>
void medianOfThree(std::vector<T> &myArray, Comparator comp, int start, int mid, int end) {
  if(!comp(myArray[start], myArray[mid])) { 
    swapVal(myArray, start, mid);
  }
  if(!comp(myArray[start], myArray[end])) { 
    swapVal(myArray, start, end);
  }
  if(comp(myArray[mid], myArray[end])) { 
    swapVal(myArray, mid, end);
  }
}

//Partitioning function using the init_pivot_idx as the initial pos of the pivot, 
//returns the correct position of pivot after placing all elements less than
//pivot element on left of pivot and all elements strictly more than pivot element on
//right of pivot element (according to comparator)
//*Pivot is always the last element
template <class T, class Comparator>
int partition(std::vector<T> &myArray, Comparator comp, int start, int end) {
  T pivot_element = myArray[end];
  int new_pivot_idx = start; //Counts how many elements are less than the pivot
  int left_idx = start; 
  //Loops through the array and when we see an element less than the pivot,
  //we increment new_pivot_idx, which accounts for the one element less
  //than the pivot, placing the new_pivot_idx in the correct position
  //Before that, we will swap the new_pivot_idx element with the left_idx
  //to make sure that the lesser element is on the left of the new_pivot_idx
  while(left_idx < end) {
    if(comp(myArray[left_idx], pivot_element)) {
      swapVal(myArray, left_idx, new_pivot_idx);
      new_pivot_idx++;
    }
    left_idx++;
  }
  swapVal(myArray, new_pivot_idx, end);
  return new_pivot_idx;
}

template <class T, class Comparator>
void quick_sort(std::vector<T> &myArray, Comparator comp, int start, int end) {
  //Ensure that myArray has more than one element
  if(start < end) {
    int mid = floor((start + end) / 2);
    medianOfThree(myArray, comp, start, mid, end); 
    int new_pivot_idx = partition(myArray, comp, start, end);
    quick_sort(myArray, comp, start, new_pivot_idx - 1);
    quick_sort(myArray, comp, new_pivot_idx + 1, end);
  }
}

template <class T, class Comparator>
void QuickSort (std::vector<T> &myArray, Comparator comp) {
  quick_sort(myArray, comp, 0, myArray.size() - 1);
}

#endif