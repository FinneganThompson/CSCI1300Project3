/*
* item.cpp
* CSCI 1300 Project 3, Spring 2023
* August Milliken & Finnegan Thompson
*
*  Implementations for all functions in item.h
*/

#include "item.h"
#include "RNG.h"

// parameterized constructor for cookware class, sets type and price based on type

cookware::cookware(char type)
{
    type_ = type;
    switch (type)
    {
        case 'P': // Pot
            cost_ = 5;
            break;
        case 'F': // Frying pan
            cost_ = 10;
            break;
        case 'C': // Cauldron
            cost_ = 20;
            break;
    }
}

// !!TO DO!! Determines if cookware breaks based off of type and RNG 
bool cookware::useCookware()
{
 return false;
}

char cookware::getType()
{
    return type_;
}

int cookware::getCost()
{
    return cost_;   
}

// Default constructor for inventory
inventory::inventory()
{
    goldPieces_ = 0;
}

// !!TO DO!! Returns sum of all amount values of ingredient vector
int inventory::totalIngredientsAvliable()
{
    return 0;
}

// getter for avalible gold
int inventory::goldAvalible()
{
    return goldPieces_;
}

// Returns vector of availible weapons
vector<weapon> inventory::weaponsAvalible()
{
    return weapons_;
}

// Returns number of armor pieces avalible
int inventory::armorAvalible()
{
    return armors_.size();
}

// Returns array of avilible treasure
vector<treasure> inventory::treasureAvailible()
{
    return treasures_;
}

//Returns array of availible cookware
vector<cookware> inventory::cookwareAvailible()
{
    return cookwares_;
}

// Add ingredients to inventory
void inventory::addIngredients(ingredient ingredientToAdd)
{
    ingredients_.push_back(ingredientToAdd);
    return;
}

// Add gold to inventory
void inventory::addGold(int numPieces)
{
    goldPieces_ += numPieces;
    return;
}

// Add weapon to inventory
void inventory::addWeapons(weapon weaponToAdd)
{
    weapons_.push_back(weaponToAdd);
    return;
}

// Add armor to inventory
void inventory::addArmor(armor armorToAdd)
{
    armors_.push_back(armorToAdd);
    return;
}

// Add cookware to inventory
void inventory::addCookware(cookware cookwareToAdd)
{
    cookwares_.push_back(cookwareToAdd);
    return;
}

// Add treasure to inventory
void inventory::findTreasure(treasure treasureToAdd)
{
    treasures_.push_back(treasureToAdd);
    return;
}

// !!TO DO!! Determines if a cookware use is sucessful (if requested cookware exists), and uses up ingredients in cooking
bool inventory::useCookware(char type, int kgIngredientsUsed)
{
    return true;
}

// Checks if sufficient gold is avalible, subtracts it if true
bool inventory::spendGold(int amountToSpend)
{
    if (goldPieces_ >= amountToSpend)
    {
        goldPieces_ -= amountToSpend;
        return true;
    }
    else return false;
}
