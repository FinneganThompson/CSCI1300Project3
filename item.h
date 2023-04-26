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
    const int cost = 1; // Cost / kg; always 1g
}; 

// Weapons class
class weapon{
    private:
        string type_; // C: Club, S: Spear, R: Rapier, B: Battle axe, L: longsword 
        int cost_; // C,S: 2; R:5; B:15; L:50 
        int modifier_; // R: +1; B: +2; L: +3 (Default is 1)
    public:
        weapon(int inputIntType);
        string getType(); // return the type of weapon
        int getCost(); // return cost value
        int getMod(); // returns modifier value
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
        string type_; // P: pot; F: frying pan; C: Cauldron
        int cost_; // Will be set by constructor
        int breakProb_;
        int quantity_;
    public:
        cookware(int inputIntType); // Validates type and sets price based on type
        string getType(); // Returns cookware type
        int getCost(); // Returns cookware cost
        int getBreakProb(); // returns probability of cookware breaking
        int getQuantity(); // returns the amount of that type of cookware 
        void setQuantity(int inputQuantity); // sets the quantity
};

class treasure{
    private:
        string type_; 
        int price_;
        int quantity_;
    public:
        treasure(int inputIntType); // Validates type and sets price based on type
        string getType(); // returns the type of treasure
        int getPrice(); // returns treasure price
        int getQuantity(); // returns the amount of that type of treasure 
        void setQuantity(int inputQuantity); // sets the quantity
};

class inventory{
    private:
        int goldPieces_;
        int ingredients_;
        vector <weapon> weapons_;
        int armor_;
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


        void addIngredients(int inputIngredients); // Adds ingredient to total ingredients
        void addGold(int numPieces); // Adds numPieces to the current amount of gold
        void addWeapons(weapon weaponToAdd); // Add weapon to inventory
        void addArmor(int inputArmor); // Add armor to inventory
        bool removeWeapon(int weaponToRemove); // Removes weapon
        bool removeArmor(int armorToRemove); // Removes armor. Returns success
        void addCookware(cookware cookwareToAdd); // Add cookware to inventory
        bool removeCookware(int cookwareToRemove); // Removes cookware. Returns success
        bool useCookware(int type); // Returns false is cookware breaks and removes from vector
        void changeTreasureQuantity(int type, int quantChange); // changes the amount of that type of treasure
        void changeCookwareQuantity(int type, int quantChange); // changes the amount of that type of cookware
        int totalCookware(); // returns how much cookware the party has


        bool useCookware(char type, int kgIngredientsUsed); // If cookware of a given type is avaible, see if using it results in sucess. Uses up ingredients

        bool spendGold(int amountToSpend); // Checks to see if the user has sufficient gold, subtracts it if true
 
};

#endif
