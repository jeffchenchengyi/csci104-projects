#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>

using namespace std;

struct Warrior {
    string weapon;
    int power;
};
/*
//Feel free to modify the parameters if you need other values
bool skirmish(Warrior*** protectors, Warrior*** invaders, int skirmish_row, int rows, int columns, int &reserves, ofstream &output){
    //returns true if the invaders breach the walls.

    //If i is out of bounds (there is no row i of invaders nor column i of protectors), then nothing happens, and you move on to the next skirmish.
    if(skirmish_row <= columns) {
        for(int invaderColIndex = 0; invaderColIndex < rows; invaderColIndex++) {
            cout << protectors[invaderColIndex][skirmish_row] << endl;
        }
    } else {
        return false;
    }
    return false;
}*/

int main(int argc, char* argv[])
{
    if (argc < 3) {
       cerr << "Please provide an input and output file" << endl;
       return -1;
    }

    ifstream input(argv[1]);
    ofstream output(argv[2]);

    //number of rows of protectors, and columns of invaders
    int rows;

    //number of columns of protectors, and rows of invaders
    int cols;

    //number of reserve forces for protectors
    int reserve;

    //number of skirmishes
    int skirmishes;

    //read the input file and initialize the values here.

    //If the input file given could not be found or could not be open
    if(input.fail()) {
        cout << "Input file could not be open." << endl;
        return 1;
    }

    //Storing the values of rows, cols, reserve, skirmishes from input file
    input >> rows >> cols >> reserve >> skirmishes;

    //If the first four values cannot be read, or not present
    if(input.fail()) {
        cout << "rows, cols, reserve, skirmishes values are not present." << endl;
    }
    
    Warrior ***protectors = NULL;
    Warrior ***invaders = NULL;

    //initialize the protectors and invaders here.
    //Starks are rows by columns
    //Initializing pointer to a row n pointer to a col m pointer of type Warrior*, AKA protector's Warrior***
    protectors = new Warrior**[rows];
    for(int n = 0; n < rows; n++) {
        protectors[n] = new Warrior*[cols];
    }

    //Giving the stark protectors their power
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            protectors[i][j]->power = (i * 10 + (j + 1) * 10);/*
            if(i % 2 == 0) {
                protectors[i][j]->weapon = "axe";
            } else {
                protectors[i][j]->weapon = "sword";
            }*/
        }
    }

    //Lannisters are columns by rows
    //Initializing pointer to a col m pointer to a row n pointer of type Warrior*, AKA invader's Warrior***
    invaders = new Warrior**[cols];
    for(int m = 0; m < cols; m++) {
        invaders[m] = new Warrior*[rows];
    }

    //Giving the lannister invaders their power
    for(int j = 0; j < cols; j++) {
        for(int i = 0; i < rows; i++) {/*
            invaders[j][i]->power = (i * 10 + (j + 1) * 10);
            if(i % 2 != 0) {
                invaders[j][i]->weapon = "axe";
            } else {
                invaders[j][i]->weapon = "sword";
            }*/
        }
    }
    /*
    for (int i=1; i <= skirmishes; i++){
        //row of invaders and column of protectors that fights in skirmish
        int skirmish_row;
        
        //read the input file to find the value for skirmish row
        input >> skirmish_row;
        
        //In general, it is bad style to throw everything into your main function
        bool end = skirmish(protectors, invaders, skirmish_row, rows, cols, reserve, output);
        if(end) cout << "yas" << endl;
    }
*/
    //output the winner and deallocate your memory.
    //Deallocating memory for each row of an array of protector's Warrior*
    for(int i = 0; i < rows; i++) {
        delete [] protectors[i];
    }

    //Deallocating memory for array of protector's Warrior**
    delete [] protectors;

    //Deallocating memory for each row of an array of invader's Warrior*
    for(int j = 0; j < cols; j++) {
        delete [] invaders[j];
    }

    //Deallocating memory for array of invader's Warrior**
    delete [] invaders;

    //Closing input and output files
    input.close();
    output.close();

    return 0;
}