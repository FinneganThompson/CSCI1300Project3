/*
* Sorcerer.cpp
* CSCI 1300 Project 3, Spring 2023
* August Milliken & Finnegan Thompson
* to run: g++ mainDriver.cpp item.cpp Monster.cpp Sorcerer.cpp party.cpp Map.cpp game.cpp RNG.cpp puzzles.cpp move.cpp
*
* Implementation of sorcerer member functions
*/
    
#include "Sorcerer.h"

// no default constructor 
// parameterized constructor
Sorcerer :: Sorcerer(string inputName, int inputLevel){
    name = inputName;
    level = inputLevel;
    anger = 0;
    doesAngerIncrease_ = true;
}
string Sorcerer :: getName(){ // gets name of sorcerer
    return name;
}
void Sorcerer :: setName(string inputName){ // sets the anme of the sorcerer
    name = inputName;
}
int Sorcerer :: getLevel(){ // gets the level of the sorcerer
    return level;
}
void Sorcerer :: setLevel(int inputLevel){ // sets the level of the sorcerer
    level = inputLevel;
}
int Sorcerer :: getAnger(){ // gets the anger of the sorcerer
    return anger;
}
void Sorcerer :: increaseAnger(){ // increases the anger of the sorcerer by 1
    if (doesAngerIncrease_) // checks to make sure that the sorcerer has not been beaten 
        anger += 1;
    else return;
}

void Sorcerer::angerNoLongerIncreases() // sets the ability of the sorcerers anger to increase to false
{
    doesAngerIncrease_ = false; 
}
