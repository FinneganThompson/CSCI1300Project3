/*
* puzzles.h
* CSCI 1300 Project 3, Spring 2023
* August Milliken & Finnegan Thompson
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

int NPCPuzzle(); // Prints out a random riddle, returns success or failure of player to solve puzzle. 0 = fail, 1 = sucess, -1 = no puzzles found

bool doorPuzzle(); // Give party the door puzzle, returns success or failure of player to solve puzze

#endif