#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>

using namespace std;

struct Warrior {
    string weapon;
    int power;
};

/*----------------------------SKIRMISH BATTLE BEGINS----------------------------*/

//Feel free to modify the parameters if you need other values
//To check if protector can defect or just get killed
void check_defected(Warrior*** invaders, Warrior* curr_protector, int rows, 
							int columns, int &reserves, ofstream &output) {
    bool defected = false;

    //Checking for any open positions in the invader's army
    for(int x = 0; x < columns; x++) {
        for(int y = 0; y < rows; y++) {
            //Any invader's power < 10 means the invader was killed previously, 
            //leaving position open
            if(invaders[x][y]->power < 10) {
                //Current protector defects to invader position
                invaders[x][y]->power = curr_protector->power;
                invaders[x][y]->weapon = curr_protector->weapon;

                //Check if there are any reserve protectors to fill the 
                //open position, set power to reserve warrior power 100, 
                //reserve warrior weapon axe
                if(reserves > 0) {
                    curr_protector->power = 100;
                    curr_protector->weapon = "axe";
                    reserves--;
                } 
                //Current protector position is now open, undefended, 
                //set power to 0 and weapon to nothing
                else {
                    curr_protector->power = 0;
                    curr_protector->weapon = "";
                }

                defected = true;
                break;
            }
        }
        if(defected) {
            break;
        }
    }

    if(defected) {
        output << "Protector defected" << endl;
    } else {
        //Check if there are any reserve protectors to fill the open 
        //position, set power to reserve warrior power 100, reserve 
        //warrior weapon axe
        if(reserves > 0) {
            curr_protector->power = 100;
            curr_protector->weapon = "axe";
            reserves--;
        } 
        //Current protector position is now open, undefended, 
        //set power to 0 and weapon to nothing
        else {
            curr_protector->power = 0;
            curr_protector->weapon = "";
        }
        //Ultimately, protector is still killed
        output << "Protector killed" << endl;
    }
} 

//To perform actions when invader is killed
void invader_killed(Warrior*** invaders, Warrior* curr_invader, 
											ofstream &output) {
    //Set their power and weapon to 0 and nothing respectively 
    //to simulate an open position/empty
    curr_invader->power = 0;
    curr_invader->weapon = "";

    output << "Invader killed" << endl;
}

bool skirmish(Warrior*** protectors, Warrior*** invaders, int skirmish_row, 
					int rows, int columns, int &reserves, ofstream &output){
    //returns true if the invaders breach the walls.
    bool breached_wall = false;

    //If i is out of bounds (there is no row i of invaders nor column i 
    //of protectors), then nothing happens, and you move on to the next 
	//skirmish.
    if(skirmish_row < columns) {
        for(int invaderColIndex = 0; invaderColIndex < rows; invaderColIndex++) {
            Warrior* curr_protector = protectors[invaderColIndex][skirmish_row];
            Warrior* curr_invader = invaders[skirmish_row][invaderColIndex];

            //In any given duel, if there is no invader at that location, 
            //then nothing happens.
            //Invaders not present
            if((curr_protector->power >= 10) && (curr_invader->power < 10)) {
                output << "No assault" << endl;
            } 
            //Invaders breached wall
            else if((curr_protector->power < 10) && (curr_invader->power >= 10)) {
                breached_wall = true;
                break;
            }
            //Protectors VS Invaders
            else {
                //In any given duel, if exactly one of the two warriors 
                //has an axe, that warrior wins.
                //Scenario 1: Protector wins! Invader position 
                //becomes empty
                if((curr_protector->weapon == "axe") && 
                		(curr_invader->weapon == "sword")) {
                    invader_killed(invaders, curr_invader, output);
                }  
                //Scenario 2: Invader wins! Protector loses duel, 
                //will check if protector will defect
                else if((curr_protector->weapon == "sword") && 
                				(curr_invader->weapon == "axe")) {
                    check_defected(invaders, curr_protector, rows, columns, 
                    										reserves, output);
                } 
                //Scenario 3: Protector weapon == Invader weapon
                else {
                    //Scenario 3a: Protector power > Invader power 
                    //Invader position becomes empty
                    if(curr_protector->power > curr_invader->power) {
                        invader_killed(invaders, curr_invader, output);
                    } 
                    //Scenario 3b: Protector power < Invader power 
                    //Protector loses duel, will check if protector will defect
                    else if(curr_protector->power < curr_invader->power) {
                        check_defected(invaders, curr_protector, rows, columns, 
                        										reserves, output);
                    } 
                    //Scenario 3c: Protector power == Invader power
                    else {
                        output << "Duel ends in draw" << endl;
                    }
                } 
            }
        }
    }

    //Returns breached_wall = false unless invaders have breached
    return breached_wall;
}

/*----------------------------SKIRMISH BATTLE ENDS----------------------------*/

int main(int argc, char* argv[])
{
/*----------------------------START OF SETUP----------------------------*/

    if (argc < 3) {
       cerr << "Please provide an input and output file" << endl;
       return -1;
    }

    ifstream input(argv[1]);
    ofstream output(argv[2]);

    //number of rows of protectors, and columns of invaders
    int rows = 0;

    //number of columns of protectors, and rows of invaders
    int cols = 0;

    //number of reserve forces for protectors
    int reserve = 0;

    //number of skirmishes
    int skirmishes = 0;

    //if warriors or invaders won
    bool end = false;

/*----------------------------END OF SETUP----------------------------*/

/*----------------------------START OF INITIALISATION----------------------------*/

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
        return 1;
    }

    //If the output file given could not be found or could not be open
    if(output.fail()) {
        cout << "Output file could not be open." << endl;
        return 1;
    }
    
    Warrior ***protectors = NULL;
    Warrior ***invaders = NULL;

    //initialize the protectors and invaders here.
    //Starks are rows by columns
    //Initializing pointer to a row n pointer to a col m pointer of type Warrior*, 
    //AKA protector's Warrior***
    protectors = new Warrior**[rows];
    for(int n = 0; n < rows; n++) {
        protectors[n] = new Warrior*[cols];
    }

    //Giving the stark protectors their power, lowest possible is 10
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            Warrior *stark = new Warrior;
            protectors[i][j] = stark;
            protectors[i][j]->power = ((i * 10) + ((j + 1) * 10));
            if(i % 2) {
                protectors[i][j]->weapon = "sword";
            } else {
                protectors[i][j]->weapon = "axe";
            }
        }
    }

    //Lannisters are columns by rows
    //Initializing pointer to a col m pointer to a row n pointer of type Warrior*, 
    //AKA invader's Warrior***
    invaders = new Warrior**[cols];
    for(int m = 0; m < cols; m++) {
        invaders[m] = new Warrior*[rows];
    }

    //Giving the lannister invaders their power, lowest possible is 10
    for(int j = 0; j < cols; j++) {
        for(int i = 0; i < rows; i++) {
            Warrior *lannister = new Warrior;
            invaders[j][i] = lannister;
            invaders[j][i]->power = ((j * 10) + ((i + 1) * 10));
            if(j % 2) {
                invaders[j][i]->weapon = "axe";
            } else {
                invaders[j][i]->weapon = "sword";
            }
        }
    }
    
/*----------------------------END OF INITIALISATION----------------------------*/

/*----------------------------START OF SKIRMISH BATTLE----------------------------*/

    for (int i=1; i <= skirmishes; i++){
        //row of invaders and column of protectors that fights in skirmish
        int skirmish_row;
        
        //read the input file to find the value for skirmish row
        input >> skirmish_row;
        
        //In general, it is bad style to throw everything into your main function
        end = skirmish(protectors, invaders, skirmish_row, 
        						rows, cols, reserve, output);

        //If end == true, means invaders have breached the wall and 
        //invaders win the whole battle, hence break out of the for loop 
        //and no more skirmishes are played
        if(end){
            output << "Winner: invaders";
            break;
        }
    }

/*----------------------------END OF SKIRMISH BATTLE----------------------------*/

/*------------------START OF DEALLOCATION OF HEAP MEMORY------------------*/

    //output the winner and deallocate your memory.
    if(!end) {
        output << "Winner: protectors";
    }

    //Deallocating memory for each row of an array of protector's Warrior*
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            //Deleting each of the of the stark protectors (Warrior*) 
            //at row i, col j
            delete protectors[i][j];
        }
        //Deleting the array of stark protector pointers (Warrior**) 
        //that point to each protector
        delete [] protectors[i];
    }

    //Deallocating memory for array of protector's Warrior**
    delete [] protectors;

    //Deallocating memory for each row of an array of invader's Warrior*
    for(int j = 0; j < cols; j++) {
        for(int i = 0; i < rows; i++) {
            //Deleting each of the of the lannister invaders (Warrior*) 
            //at row j, col i
            delete invaders[j][i];
        }
        //Deleting the array of lannister invader pointers (Warrior**) that 
        //point to each invader
        delete [] invaders[j];
    }

    //Deallocating memory for array of invader's Warrior**
    delete [] invaders;

    //Closing input and output files
    input.close();
    output.close();

    return 0;
}

/*------------------END OF DEALLOCATION OF HEAP MEMORY------------------*/