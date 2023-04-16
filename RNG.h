/*
* RNG.h
* CSCI 1300 Project 3, Spring 2023
* August Milliken & Finnegan Thompson
*
* File includes random number generating functions
*/

#include <cstdlib>
#include <time.h>

using namespace std;

#ifndef RNG_H
#define RNG_H

bool doesActionOccur(int probabilityOfAction); // returns wether or not an action occurs based off of its probability
int randIntBetweenOneAndTen(); // Returns random int between one and ten (not including 0, including 10)
int randIntOnRange(int lowerBound, int upperBound); // Both bounds are included. Returns -1 for failure

#endif
