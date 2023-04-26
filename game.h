
#include "item.h"
#include "Monster.h"
#include "Sorcerer.h"
#include "party.h"
#include "RNG.h"
#include <vector>
#include <iostream>
#include <fstream>


/*
Algorithm prints out everything that is in the party's inventory 
Accepts the party's inventory object 
Create vectors for the cookware, weapons, and treasure, of their respective types
Create ints to hold the amount of each type of cookware, weapons, and treasure respectively 
Loop through each vector and count the number of each type for cookware, weapons, and treasure respectively
For treasure, after counting the amount of each type of treasure add it to the vector passed to the function
*/

void printInventory(inventory partyInventory);

/*
Algorithm is an interactive menu to allow a user to buy or sell items 
Accepts a party object
Declare an inventory object to hold the party's inventory
Declare an integer to hold the value of how much the cost should change (based on how many rooms have been cleared), one to hold the main menu choice,
one to hold the quantity of items to be bought or sold, the type of item to be bought or sold, and the calculated cost of items to be bought or sold
Declare a char to hold whether or not a user would like to finalize a sale or purchase
Print out welcome message 
Enter a loop to be the menu that will continue until the user wants to exit the menu
Call the printInventory funciton 
Print out the options 
Take user input and pass it to the main menu choice int 
Enter the switch statement
(Each option)
*/

void merchantMenu(party &mainParty);


//Each turn there is a 40% one of the misfortunes will occur. Misfortunes:
/*
robbed (chosen at random) 30%
    lose ingredients (10kg)
    cookware (1 item)
    armor (1 item( break either weapon or armor 10% food poisoning one member loses 10 hunger points (can kill) 
    30% locked in room: only happens if player tries to open door with key (nothing happens if picked when not open door) 
    30% One random member that is not leader (can end game if no more members)
*/

// Randomly causes one of the end of turn misfortunes to the party
bool endOfTurnMisfortune(party &mainParty, bool wasLastActionExitRoomOpenedWithKey);

// Reads in monsters to the provided vector from the file
bool readInMonsters(vector<Monster> &monsters, string filename);

// Complete fight sequence
bool fightMonster(vector<Monster> &monsters, party &mainParty);

// Complete sorcerer fight sequence 
bool fightSorcerer(party &mainParty, Sorcerer &mainSorcerer); 
