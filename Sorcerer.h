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

    public:
    // no default constructor 
    // parameterized constructor
    Sorcerer(string inputName, int inputLevel);
    string getName();
    void setName(string inputName);
    int getLevel();
    void setLevel(int inputLevel);
    int getAnger();
    void increaseAnger();
};

#endif