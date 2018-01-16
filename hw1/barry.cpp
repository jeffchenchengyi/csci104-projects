#include <iostream>
#include <stdlib.h>
#include <cstring>

using namespace std;

bool increasing(int a)
{
	if (a > 0) {

		//if the recursive call fails, don't bother to check further.
		if (!increasing (a/10)) return false;

		//the least significant digit
		int last = a % 10;

		//the second least significant digit, 0 if a < 10
		int prev = (a / 10) % 10;

		//make your changes only below this line.  You may not use any loops.

		//Base Case: When we reached the most significant digit
		if (prev <= last) {
		    return true;
		} else {
		    return false;
		}
	} 
	//If a == 0, it can only mean the original input is 0 
	//Or that we have reached the most significant digit, 
	//e.g. if a == 6, we received 6 / 10, truncate after decimal point
	//hence 0, so we will return true so that the function can work for a > 0
	else if(a == 0) {
		//Hence, !increasing(a/10) == false, 
		//and the function can continue instead of returning false
	    return true;
	} 
	//just return false for negative inputs, 
	//Prof Aaron Cote said we do not need to handle them, I just left it in just in case
	else {
	    return false;
	}
}

//do not change the main function.
int main (int argc, char* argv[])
{
  if(argc < 2){
    cerr << "Please provide an integer." << endl;
    return 1;
  }
  int x = atoi(argv[1]);
  if(increasing(x)) cout << "Increasing order." << endl;
  else cout << "Not increasing order." << endl;
  return 0;
}