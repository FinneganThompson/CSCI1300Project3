/*
* RNG.cpp
* CSCI 1300 Project 3, Spring 2023
* August Milliken & Finnegan Thompson
* to run: g++ mainDriver.cpp item.cpp Monster.cpp Sorcerer.cpp party.cpp Map.cpp game.cpp RNG.cpp puzzles.cpp move.cpp
*
* File includes random number generating functions
*/


#include "RNG.h"

RNG::RNG()
{
    srand(time(NULL)); // Call our srand function (applies globally)
}

// Accepts a probability as a percentage (0 to 100) and uses a random dice roll to get an outcome within or out of that probability range. 
bool RNG::doesActionOccur(int probabilityOfAction)
{
    int randomInt = rand() % 100; // Take the last 2 digits of the random int
    
    if (randomInt < probabilityOfAction) // This gives us the correct probabilties
    {
        return true;
    }
    else return false; 
}

int RNG::randIntBetweenOneAndTen() // Returns random int between one and ten (not including 0, including 10)
{   
    int randomInt = rand() % 10 +1 ; // Gets random number between one and 10
    return randomInt;
}

int RNG::randIntOnRange(int lowerBound, int upperBound) // Returns int between lower and upper bound inclusively
{
    if (lowerBound > upperBound) // This makes sure that the lower bound does not exceed the upper bound
    {
        return -1;
    }
    else if (lowerBound == upperBound) // This makes sure that they are not equal
    {
        return 0;
    }

    int range = upperBound - lowerBound + 1; // This gives us the range
    int randomInt = rand() % range + lowerBound; // This finds the randum number
    return randomInt;
}
