/*
* puzzles.h
* CSCI 1300 Project 3, Spring 2023
* August Milliken & Finnegan Thompson
* to run: g++ mainDriver.cpp item.cpp Monster.cpp Sorcerer.cpp party.cpp Map.cpp game.cpp RNG.cpp puzzles.cpp move.cpp
*
* Puzzles used in the game
*/

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "RNG.h"

using namespace std;

#ifndef PUZZLE_H
#define PUZZLE_H


// Splits a string at a given seperator an puts it into an array
int split(string inputString, char seperator, string peiceArray[], int peiceArraySize);

// Prints out a random riddle, returns success or failure of player to solve puzzle. 0 = fail, 1 = sucess, -1 = no puzzles found
int NPCPuzzle(); 

bool doorPuzzle(); // Give party the door puzzle, returns success or failure of player to solve puzze

#endif
