/*
* Monster.cpp
* CSCI 1300 Project 3, Spring 2023
* August Milliken & Finnegan Thompson
* to run: g++ mainDriver.cpp item.cpp Monster.cpp Sorcerer.cpp party.cpp Map.cpp game.cpp RNG.cpp puzzles.cpp move.cpp
*
* Implement member functions of monster class
*/

#include "Monster.h"

// no default constructor 
// parameterized constructor
Monster :: Monster(string inputName, int inputLevel){
    name = inputName;
    level = inputLevel;
}
string Monster :: getName(){ // get monster name
    return name;
}
void Monster :: setName(string inputName){ // set monster name
    name = inputName;
}
int Monster :: getLevel(){ // get monster level
    return level;
}
void Monster :: setLevel(int inputLevel){ // set monster level
    level = inputLevel;
}
