/*
* Sorcerer.cpp
* CSCI 1300 Project 3, Spring 2023
* August Milliken & Finnegan Thompson
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
string Sorcerer :: getName(){
    return name;
}
void Sorcerer :: setName(string inputName){
    name = inputName;
}
int Sorcerer :: getLevel(){
    return level;
}
void Sorcerer :: setLevel(int inputLevel){
    level = inputLevel;
}
int Sorcerer :: getAnger(){
    return anger;
}
void Sorcerer :: increaseAnger(){
    if (doesAngerIncrease_)
        anger += 1;
    else return;
}

void Sorcerer::angerNoLongerIncreases()
{
    doesAngerIncrease_ = false; 
}
