
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

// Weapons struct
struct weapon{
    char type; // C: Club, S: Spear, R: Rapier, B: Battle axe, L: longsword
    int cost; // C,S: 2; R:5; B:15; L:50;
    int modifier; // R: +1; B: +2; L: +3 (Default is 1)
};

// Armor struct
struct armor{
    int protection = 1; // Defualt protection level is one
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
        bool useCookware(); // Returns false is cookware breaks. 
        char getType(); // Returns cookware type
        int getCost(); // Returns cookware cost
};

struct treasure{
    char type; // See writeup for prices and names
    int cost;
};

class inventory{
    private:
        int goldPieces_;
        int ingredients_;
        vector <weapon> weapons_;
        vector <armor> armors_;
        vector <cookware> cookwares_;
        vector <treasure> treasures_;

    public:
        inventory();

        int totalIngredientsAvliable(); // Returns total ingredients avail. in kg
        int goldAvalible(); // Returns gold avalible
        vector<weapon> weaponsAvalible(); // Returns weapons avalible
        int armorAvalible(); // Returns armor avalible
        vector<treasure> treasureAvailible(); // Returns treasure availible
        vector<cookware> cookwareAvailible(); // Returns cookware avalible


        void setIngredients(int newIngredientAmount); // Adds ingredient to ingredients vector
        void addGold(int numPieces); // Adds numPieces to the current amount of gold
        void addWeapons(weapon weaponToAdd); // Add weapon to inventory
        void addArmor(armor armorToAdd); // Add armor to inventory
        bool removeArmor(int armorToRemove); // Removes armor. Returns success
        bool removeCookware(int cookwareToRemove); // Removes cookware. Returns success
        void addCookware(cookware cookwareToAdd); // Add cookware to inventory
        void findTreasure(treasure treasureToAdd); // Add treasure to inventory


        bool useCookware(char type, int kgIngredientsUsed); // If cookware of a given type is avaible, see if using it results in sucess. Uses up ingredients

        bool spendGold(int amountToSpend); // Checks to see if the user has sufficient gold, subtracts it if true
 
};

#endif
