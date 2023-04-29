/*
* party.h
* CSCI 1300 Project 3, Spring 2023
* August Milliken & Finnegan Thompson
* to run: g++ mainDriver.cpp item.cpp Monster.cpp Sorcerer.cpp party.cpp Map.cpp game.cpp RNG.cpp puzzles.cpp move.cpp
*
* Includes player struct, partyDependentAttackContributors struct status struct, party class
*/

#include "item.h"
#include <iostream>

#ifndef PARTY_H
#define PARTY_H

struct player{

    string name;
    int hunger;
    bool isUserPlayer = false; // Is the one controlling the game (leader)

};

struct partyDependentAttackContributors{ // Parts of the attack formula that are dependent on the party
    int w; // #weapons + modifiers
    int d; // 4 if all weapons are unique, 0 else
    int a; // #armor sets

};

struct partyStatus{ // For status updates, does not include anger level
    int roomsCleared;
    int keys;
    inventory partyInventory; 
    vector<player> players; 
};

class party{
    private:
        
        vector<player> players_;

        int roomsCleared_; 
        int spacesExplored_;
        int keysFound_;
        int turnsElapsed_;

        vector<string> monstersDefeated_; // holds the monsteres that the party has encountered and defeated
        int numMonstersDefeated_;

    public:

        inventory partyInventory_;
        party(); // Default constructor, all ints set to zero

        int getRoomsCleared();
        int getSpacesExplored();
        int getKeysFound();
        int getTurnsElapsed();
        int getNumMonstersDefeated();

        void increaseRoomsCleared(); // Inc. by 1
        void increaseSpacesExplored(); // Inc. by 1
        void increaseKeysFound(); // Inc. by 1
        void loseKey(); // Decr by 1
        void incrementTurn(); // Inc by 1

        void addPlayer(player playerToAdd);
        vector<player> getPlayers(); 

        void cookAndEat(); // Prompts for kg ingredients and cookware. Hunger increases are dist. equally
        bool removeHunger(int playerPosition, int hungerToRemove); // Removes hunger from the player at position playerPosition in the players_ vector. Returns false if removing that much hunger would kill the player. 
        void addHunger(int playerPosition, int hungerToAdd); // Adds hunger points

        void winBattle(string monsterNamebool, bool &gameOver); // iterates num monsters defeated by 1 adds to monsters defeated. 50% chance for each player to lose one hunger
        void loseBattle(bool &gameOver); // Lose 1/4 of gold, up to 30kg food, each party member wearing armor has 5% death, otherwise 10% death. Prints death message. 50% food drop by 1. 
        void surrenderBattle(bool &gameOver); // Party loses one non-main member and items as appropiate. 50% food drop by 1. 


        vector<player> starvingPlayers(); // Returns all starving players
        partyStatus getStatus(); // Returns filled status
        // partyDependentAttackContributors getPartyDependentAttackContributors(); // Returns filled struct. 

        void killPlayerNoMessage(string name); // Removes player and items as appropriate
        void killPlayerOfHunger(string name, bool &gameOver); // Removes player + items and prints hunger death message

        void winGame(); // Game is won
        void loseGame(int deathType); // Type 0:Give up; 1: all but main player die; 2: main player dies; 3: Sorcerer's anger
        
        void printFullness(); //prints the fullness points of each player in the party


};

#endif
