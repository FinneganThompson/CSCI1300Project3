#include "item.h"
#include "Monster.h"
#include "Sorcerer.h"
#include "party.h"
#include "Map.h"

/*
Algorithm prints out everything that is in the party's inventory 
Accepts the party's inventory object 
Create vectors for the cookware, weapons, and treasure, of their respective types
Create ints to hold the amount of each type of cookware, weapons, and treasure respectively 
Loop through each vector and count the number of each type for cookware, weapons, and treasure respectively
*/

void printInventory(inventory partyInventory);
