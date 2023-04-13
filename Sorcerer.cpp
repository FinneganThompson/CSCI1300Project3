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
    string name = inputName;
    int level = inputLevel;
    int anger = 0;
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
// to be used each turn since it can only increase by one
void Sorcerer :: increaseAnger(){
    anger += 1;
}
