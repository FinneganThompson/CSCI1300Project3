/*
* item.h
* CSCI 1300 Project 3, Spring 2023
* August Milliken & Finnegan Thompson
*
* Includes structs and classes for all items
*/

#include <string>
#include <vector>

#ifndef ITEM_H
#define ITEM_H

using namespace std;

// Ingredients struct
struct ingredient{  
    string name;
    int kilograms;
    int cost; // Cost / kg; always 1g
}; 

// Weapons struct
struct weapon{
    char type; // C: Club, S: Spear, R: Rapier, B: Battle axe, L: longsword
    int cost; // C,S: 2; R:5; B:15; L:50;
    int modifier; // R: +1; B: +2; L: +3 (Default is 1)
};

// Armor struct
struct armor{
    const int cost = 5;
};

// Cookware class (using cookware may destroy it)
class cookware
{
    private:
        char type_; // P: pot; F: frying pan; C: Cauldron
        int cost_; // Will be set by constructor
    public:
        cookware(char type); // Validates type and sets price based on typ
        bool useCooware(); // Returns false is cookware breaks. 
};

struct treasure{
    char type; // See writeup for prices and names
    int cost;
};

class inventory{
    private:
        int goldPieces_;
        vector<ingredient> ingredients_;
        vector <weapon> weapons_;
        vector <armor> armors_;
        vector <cookware> cookware_;
        vector <treasure> treasure_;

    public:
        inventory();

        int totalIngredientsAvliable(); // Returns total ingredients avail. in kg

        int goldAvalible(); // Returns gold avalible

        weapon weaponsAvalible(); // Returns weapons avalible

        armor armorAvalible(); // Returns armor avalible

        treasure treasureAvailible(); // Returns treasure availible

        bool hasSufficientGold(int goldNeeded); // Checks to see if the user has sufficient gold
 
};

#endif
