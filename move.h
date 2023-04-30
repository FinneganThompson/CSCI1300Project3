/*
* move.h
* CSCI 1300 Project 3, Spring 2023
* August Milliken & Finnegan Thompson
* to run: g++ mainDriver.cpp item.cpp Monster.cpp Sorcerer.cpp party.cpp Map.cpp game.cpp RNG.cpp puzzles.cpp move.cpp
* 
* The NPC, room, and normal space turn functions
*/

#include "game.h"

// Algorithm enacts what should happen when the party is on a normal space
void normalSpace(Map &mainMap, party &mainParty, Sorcerer &gameSorcerer, bool &gameOver, vector<Monster> &monsters);

//Algorithm enacts what should happen when the party is on a room space
void roomSpace(Map &mainMap, party &mainParty, Sorcerer &gameSorcerer, bool &gameOver, vector<Monster> &monsters);

//Algorithm enacts what should happen when the party is on an NPC space
void npcSpace(Map &mainMap, party &mainParty, Sorcerer &gameSorcerer, bool &gameOver, vector<Monster> &monsters);