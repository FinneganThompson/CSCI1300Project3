/*
* Monster.cpp
* CSCI 1300 Project 3, Spring 2023
* August Milliken & Finnegan Thompson
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
string Monster :: getName(){
    return name;
}
void Monster :: setName(string inputName){
    name = inputName;
}
int Monster :: getLevel(){
    return level;
}
void Monster :: setLevel(int inputLevel){
    level = inputLevel;
}
