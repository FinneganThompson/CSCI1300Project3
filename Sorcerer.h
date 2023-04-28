/*
* Sorcerer.h
* CSCI 1300 Project 3, Spring 2023
* August Milliken & Finnegan Thompson
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
    string getName();
    void setName(string inputName);
    int getLevel();
    void setLevel(int inputLevel);
    int getAnger();
    // to be used each turn since it can only increase by one
    void increaseAnger();
    void angerNoLongerIncreases(); // When the sorcerer is defeated
};

#endif
