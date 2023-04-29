/*
* Sorcerer.h
* CSCI 1300 Project 3, Spring 2023
* August Milliken & Finnegan Thompson
* to run: g++ mainDriver.cpp item.cpp Monster.cpp Sorcerer.cpp party.cpp Map.cpp game.cpp RNG.cpp puzzles.cpp move.cpp
*
* File includes sorcerer class
*/

#ifndef SORCERER_H
#define SORCERER_H

#include <string>
#include <iostream>

using namespace std;



// sorcerer
class Sorcerer{
    private:
    string name;
    int level;
    int anger;
    bool doesAngerIncrease_ ;

    public:
    // no default constructor 
    // parameterized constructor
    Sorcerer(string inputName, int inputLevel);
    string getName(); // gets name of sorcerer
    void setName(string inputName); // sets the anme of the sorcerer
    int getLevel(); // gets the level of the sorcerer
    void setLevel(int inputLevel);// sets the level of the sorcerer
    int getAnger(); // gets the anger of the sorcerer
    // to be used each turn since it can only increase by one
    void increaseAnger(); // increases the anger of the sorcerer by 1
    void angerNoLongerIncreases(); // When the sorcerer is defeated
};

#endif
