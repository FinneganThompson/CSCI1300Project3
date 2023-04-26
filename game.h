#include "item.h"
#include "Monster.h"
#include "Sorcerer.h"
#include "party.h"
#include "Map.h"
#include "RNG.h"

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


bool endOfTurnMisfortune(party &mainParty, bool wasLastActionExitRoomOpenedWithKey);
