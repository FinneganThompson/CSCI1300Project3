/*
* item.cpp
* CSCI 1300 Project 3, Spring 2023
* August Milliken & Finnegan Thompson
*
*  Implementations for all functions in item.h
*/

#include "item.h"
#include "RNG.h"

// parameterized constructor for weapon class, set based on the type of input 
weapon::weapon(int inputIntType){
    switch(inputIntType){
        case 1:{ // club
            type = "Club";
            cost = 2;
            modifier = 0;
            break;
        }
        case 2:{ //spear
            type = "Spear";
            cost = 2;
            modifier = 0;
            break;
        }
        case 3:{ // rapier
            type = "Rapier";
            cost = 5;
            modifier = 1;
            break;
        }
        case 4:{ // battle axe
            type = "Battle Axe";
            cost = 15;
            modifier = 2;
            break;
        }
        case 5:{ // longsword
            type = "Longsword";
            cost = 50;
            modifier = 3;
            break;
        }
    }
}
// return weapon type
string weapon::getType(){
    return type;
}
// return cost value
int weapon::getCost(){
    return cost;
} 
// returns modifier value
int weapon::getMod(){
    return modifier;
} 

// Validates type and sets price based on type
treasure::treasure(int inputIntType){
    switch(inputIntType){
        case 1:{
            type = "Silver ring";
            price = 10;
            break;
        }
        case 2:{
            type = "Ruby necklace";
            price = 20;
            break;
        }
        case 3:{
            type = "Emerald bracelet";
            price = 30;
            break;
        }
        case 4:{
            type = "Diamond circlet";
            price = 40;
            break;
        }
        case 5:{
            type = "Gem-encrusted goblet";
            price = 50;
            break;
        }
    }
}
// returns the type of treasure
string treasure::getType(){
    return type;
}
// returns treasure cost
int treasure::getPrice(){
    return price;
}
// returns the amount of that type of treasure
int treasure::getQuantity(){
    return quantity;
}
// sets the quantity
void treasure::setQuantity(int inputQuantity){
    quantity = inputQuantity;
}



// parameterized constructor for cookware class, sets type and price based on type

cookware::cookware(int inputIntType){
    switch(inputIntType){
        case 1:{
            type = "Ceramic pot";
            cost = 5;
            breakProb = 0.25;
            break;
        }
        case 2:{
            type = "Frying pan";
            cost =10;
            breakProb = 0.1;
            break;
        }
        case 3:{
            type = "Cauldron";
            cost = 20;
            breakProb = 0.02;
            break;
        }
    }
}
// Returns false is cookware breaks and removes from vector
bool cookware::useCookware(vector<cookware> cookwares_, int vectPos){
    RNG prob;
    if(prob.doesActionOccur(getBreakProb()) == true){
        cookwares_.erase(cookwares_.begin()+vectPos);
        return false;
    }
    else{
        return true;
    }
} 
// Returns cookware type
string cookware::getType(){
    return type;
}
// Returns cookware cost
int cookware::getCost(){
    return cost;
}
// Retruns the probability of the cookware breaking
int cookware::getBreakProb(){
    return breakProb;
}


// Default constructor for inventory
inventory::inventory()
{
    goldPieces_ = 0;
    ingredients = 0;
    armor = 0;
}

// !!TO DO!! Returns sum of all amount values of ingredient vector
int inventory::totalIngredientsAvliable()
{
    return ingredients;
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

// Returns number of armor pieces avalible **
int inventory::armorAvalible()
{
    return armor;
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

// Adds ingredient to total ingredients
void inventory::addIngredients(int inputIngredients){
    ingredients += inputIngredients;
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
void inventory::addArmor(int inputArmor){
    if((armor + inputArmor) <= 5){
        armor += inputArmor;
    }
    else{
        armor = 5;
    }
}

// Add cookware to inventory
void inventory::addCookware(cookware cookwareToAdd)
{
    cookwares_.push_back(cookwareToAdd);
    return;
}

/*// Add treasure to inventory
void inventory::findTreasure(treasure treasureToAdd)
{
    treasures_.push_back(treasureToAdd);
    return;
}*/

// changes the amount of that type of treasure
void inventory::ChangeQuantity(int type, int quantChange){
    treasures_.at(type).setQuantity(treasures_.at(type).getQuantity() + quantChange);
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
        goldPieces_ == amountToSpend;
        return true;
    }
    else return false;
}
