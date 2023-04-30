/*
* game.h
* CSCI 1300 Project 3, Spring 2023
* August Milliken & Finnegan Thompson
* to run: g++ mainDriver.cpp item.cpp Monster.cpp Sorcerer.cpp party.cpp Map.cpp game.cpp RNG.cpp puzzles.cpp move.cpp
* 
* All functions that are pertinent to the game but cannot belong to a class
*/

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


//Algorithm prints the fullness points of each player in the party
void printFullness(party mainParty);


//Algorithm is an interactive menu to allow a user to buy or sell items 
void merchantMenu(party &mainParty);


//Algorithm prints out a status update, to be used at the start of every turn
void statusUpdate(party mainParty, Sorcerer gameSorcerer);

//Algorithm allows the party to move spaces on the map
void move(Map &mainMap, party &mainParty, Sorcerer &gameSorcerer);

//Algorithm allows the party to investigate the space
void investigate(party &mainParty, bool &gameOver, vector<Monster> &monsters);

// Randomly causes one of the end of turn misfortunes to the party
bool endOfTurnMisfortune(party &mainParty, int misfortuneProb, bool wasLastActionExitRoomOpenedWithKey, bool &gameOver);

// Reads in monsters to the provided vector from the file
bool readInMonsters(vector<Monster> &monsters, string filename);

// Complete fight sequence
bool fightMonster(vector<Monster> &monsters, party &mainParty, bool isInRoom, bool &gameOver);

// Complete sorcerer fight sequence 
bool fightSorcerer(party &mainParty, Map &mainMap, Sorcerer &mainSorcerer, vector<Monster> &monsters); 
