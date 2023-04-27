#include "item.h"
#include "Monster.h"
#include "Sorcerer.h"
#include "party.h"
#include "Map.h"
#include "RNG.h"
#include "puzzles.h"
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
Algorithm prints the fullness points of each player in the party
Accepts a party object
Declarea vector of the players
Loop through the party and print the fullness points for each member
*/

void printFullness(party mainParty);

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

/*
Algorithm prints out a status update, to be used at the start of every turn
Accepts a party object and a sorcerer object
Print out the number of rooms cleared, keys found, and the anger level of the sorcerer
Print the inventory by calling the print inventory function
Print out the fullness of the player and all party members
*/

void statusUpdate(party mainParty, Sorcerer gameSorcerer);

/*
Algorithm accepts a map object and a party object
Declare a RNG object, a char to hold the move directio choice, and a bool to hold if the party's move choice is allowed
While the move is not allowed:
Ask the user where they would like to go and print the options as well
Accept the user input into the move choice
Check if the move choice is allowed using the .move function (if it is by checking you will also be moving)
If it is not allowed print out a message to inform the user
After exiting the while loop (if the party moved) loop through the party and individually determine if that player loses a fullness point
*/

void move(Map &mainMap, party &mainParty, Sorcerer &gameSorcerer);

void investigate(party &mainParty);


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
bool endOfTurnMisfortune(party &mainParty, int misfortuneProb, bool wasLastActionExitRoomOpenedWithKey);

// Reads in monsters to the provided vector from the file
bool readInMonsters(vector<Monster> &monsters, string filename);

// Complete fight sequence
bool fightMonster(vector<Monster> &monsters, party &mainParty, bool isInRoom);

// Complete sorcerer fight sequence 
bool fightSorcerer(party &mainParty, Sorcerer &mainSorcerer); 
