/*
* Monster.h
* CSCI 1300 Project 3, Spring 2023
* August Milliken & Finnegan Thompson
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
    string getName();
    void setName(string inputName);
    int getLevel();
    void setLevel(int inputLevel);
};

#endif