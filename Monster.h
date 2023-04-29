/*
* Monster.h
* CSCI 1300 Project 3, Spring 2023
* August Milliken & Finnegan Thompson
* to run: g++ mainDriver.cpp item.cpp Monster.cpp Sorcerer.cpp party.cpp Map.cpp game.cpp RNG.cpp puzzles.cpp move.cpp
*
* File includes monster class
*/
#ifndef MONSTER_H
#define MONSTER_H

#include <string>
#include <iostream>

using namespace std;

// monster definition
class Monster{
    private:
    string name;
    int level;

    public:
    // no default constructor 
    // parameterized constructor
    Monster(string inputName, int inputLevel);
    string getName();// get monster name
    void setName(string inputName);// set monster name
    int getLevel();// get monster level
    void setLevel(int inputLevel);// set monster level
};

#endif