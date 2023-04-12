/*
* party.h
* CSCI 1300 Project 3, Spring 2023
* August Milliken & Finnegan Thompson
*
* Includes player struct, partyDependentAttackContributors struct status struct, party class
*/

#include "item.h"

#ifndef PARTY_H
#define PARTY_H

struct player{

    string name;
    int hunger;
    bool isUserPlayer; // Is the one controlling the game (leader)

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
        int monstersDefeated;

    public:

        inventory partyInventory_;

        void investigate(); // 10% key; 20% treasure; 10% monster; no matter outcome 50% individual hunger drop chance

        void cookAndEat(); // Prompts for kg ingredients and cookware. Hunger increases are dist. equally

        void winBattle(int challengeRating); // Adds 10 * challenge coins and 5 * challenge kg of food to inventory, adds key 10% of time. 50% food drop by 1. 
        void loseBattle(); // Lose 1/4 of gold, up to 30kg food, each party member wearing armor has 5% death, otherwise 10% death. Prints death message. 50% food drop by 1. 
        void surrenderBattle(); // Party loses one non-main member and items as appropiate. 50% food drop by 1. 

        void endOfTurnMisfortune(); // Each turn there is a 40% one of the misfortunes will occur. 

        vector<player> starvingPlayers(); // Returns all starving players
        partyStatus getStatus(); // Returns filled status
        partyDependentAttackContributors getPartyDependentAttackContributors(); // Returns filled struct. 

        void killPlayerNoMessage(string name); // Removes player and items as appropriate
        void killPlayerOfHunger(string name); // Removes player + items and prints hunger death message

        void winGame(); // Game is won
        void loseGame(int deathType); // Type 0:Give up; 1: all but main player die; 2: main player dies; 3: Sorcerer's anger


};

#endif
