/*
* RNG.h
* CSCI 1300 Project 3, Spring 2023
* August Milliken & Finnegan Thompson
* to run: g++ mainDriver.cpp item.cpp Monster.cpp Sorcerer.cpp party.cpp Map.cpp game.cpp RNG.cpp puzzles.cpp move.cpp
*
* File includes random number generating functions
*/

#include <cstdlib>
#include <time.h>

using namespace std;

#ifndef RNG_H
#define RNG_H

class RNG{
    public:
        RNG(); // default constructor, runs srand
        bool doesActionOccur(int probabilityOfAction); // returns wether or not an action occurs based off of its probability
        int randIntBetweenOneAndTen(); // Returns random int between one and ten (not including 0, including 10)
        int randIntOnRange(int lowerBound, int upperBound); // Both bounds are included. Returns -1 for failure
};

#endif
