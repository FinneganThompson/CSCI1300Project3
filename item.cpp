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
            type_ = "Club";
            cost_ = 2;
            modifier_ = 0;
            break;
        }
        case 2:{ //spear
            type_ = "Spear";
            cost_ = 2;
            modifier_ = 0;
            break;
        }
        case 3:{ // rapier
            type_ = "Rapier";
            cost_ = 5;
            modifier_ = 1;
            break;
        }
        case 4:{ // battle axe
            type_ = "Battle Axe";
            cost_ = 15;
            modifier_ = 2;
            break;
        }
        case 5:{ // longsword
            type_ = "Longsword";
            cost_ = 50;
            modifier_ = 3;
            break;
        }
    }
}
// return weapon type
string weapon::getType(){
    return type_;
}
// return cost value
int weapon::getCost(){
    return cost_;
} 
// returns modifier value
int weapon::getMod(){
    return modifier_;
} 

// Validates type and sets price based on type
treasure::treasure(int inputIntType){
    switch(inputIntType){
        case 1:{
            type_ = "Silver ring";
            price_ = 10;
            quantity_ = 0;
            break;
        }
        case 2:{
            type_ = "Ruby necklace";
            price_ = 20;
            quantity_ = 0;
            break;
        }
        case 3:{
            type_ = "Emerald bracelet";
            price_ = 30;
            quantity_ = 0;
            break;
        }
        case 4:{
            type_ = "Diamond circlet";
            price_ = 40;
            quantity_ = 0;
            break;
        }
        case 5:{
            type_ = "Gem-encrusted goblet";
            price_ = 50;
            quantity_ = 0;
            break;
        }
    }
}
// returns the type of treasure
string treasure::getType(){
    return type_;
}
// returns treasure cost
int treasure::getPrice(){
    return price_;
}
// returns the amount of that type of treasure
int treasure::getQuantity(){
    return quantity_;
}
// sets the quantity
void treasure::setQuantity(int inputQuantity){
    quantity_ = inputQuantity;
}



// parameterized constructor for cookware class, sets type and price based on type

cookware::cookware(int inputIntType){
    switch(inputIntType){
        case 1:{
            type_ = "Ceramic pot";
            cost_ = 5;
            breakProb_ = 0.25;
            quantity_ = 0;
            break;
        }
        case 2:{
            type_ = "Frying pan";
            cost_ =10;
            breakProb_ = 0.1;
            quantity_ = 0;
            break;
        }
        case 3:{
            type_ = "Cauldron";
            cost_ = 20;
            breakProb_ = 0.02;
            quantity_ = 0;
            break;
        }
    }
}
// Returns cookware type
string cookware::getType(){
    return type_;
}
// Returns cookware cost
int cookware::getCost(){
    return cost_;
}
// Retruns the probability of the cookware breaking
int cookware::getBreakProb(){
    return breakProb_;
}

// returns the amount of that type of cookware
int cookware::getQuantity(){
    return quantity_;
}

// sets the quantity
void cookware::setQuantity(int inputQuantity){
    quantity_ = inputQuantity;
}


// Default constructor for inventory
inventory::inventory()
{
    goldPieces_ = 0;
    ingredients_ = 0;
    armor_ = 0;
    treasure rings(1), necklaces(2), bracelets(3), circlets(4), goblets(5);
    treasures_ = {rings, necklaces, bracelets, circlets, goblets};
    cookware pots(1), pans(2), cauldrons(3);
    cookwares_ = {pots,pans,cauldrons};
}

// !!TO DO!! Returns sum of all amount values of ingredient vector
int inventory::totalIngredientsAvliable()
{
    return ingredients_;
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
    return armor_;
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
    ingredients_ += inputIngredients;
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
    if(weapons_.size() < 5){
        weapons_.push_back(weaponToAdd);
        return;
    }
}

bool inventory::removeWeapon(int weaponToRemove)
{
    if (weapons_.size() > weaponToRemove)
    {
        weapons_.erase(weapons_.begin() + weaponToRemove);
        return true;
    }
    else return false;
}

// Removes armor. Returns success
bool inventory::removeArmor(int armorToRemove){
    if((armor_ - armorToRemove) >= 0){
        armor_ -= armorToRemove;
        return true;
    }
    else{
        return false;
    }
}

/*
bool inventory::removeCookware(int cookwareToRemove)
{
   if (cookwares_.size() > cookwareToRemove)
    {
        cookwares_.erase(cookwares_.begin() + cookwareToRemove);
        return true;
    }
    else return false; 
}
*/

bool inventory::removeCookware(int cookwareToRemove)
{
   if (cookwares_.at(cookwareToRemove).getQuantity() > 0)
    {
        //cookwares_.erase(cookwares_.begin() + cookwareToRemove);
        changeCookwareQuantity(cookwareToRemove,-1);
        return true;
    }
    else return false; 
}


// Add armor to inventory
void inventory::addArmor(int inputArmor){
    if((armor_ + inputArmor) <= 5){
        armor_ += inputArmor;
    }
    else{
        armor_ = 5;
    }
}

// Returns false is cookware breaks and removes from vector
bool inventory::useCookware(int type){
    RNG prob;
    if(prob.doesActionOccur(cookwares_.at(type).getBreakProb()) == true){
        changeCookwareQuantity(type,-1);
        return false;
    }
    else{
        return true;
    }
} 

// changes the amount of that type of treasure
void inventory::changeTreasureQuantity(int type, int quantChange){
    treasures_.at(type).setQuantity(treasures_.at(type).getQuantity() + quantChange);
}

// changes the amount of that type of cookware
void inventory::changeCookwareQuantity(int type, int quantChange){
    cookwares_.at(type).setQuantity(cookwares_.at(type).getQuantity() + quantChange);
}

// returns how much cookware the party has
int inventory::totalCookware(){
    int sum = 0;
    for(int i = 0; i < 3; i++){
        sum += cookwares_.at(i).getQuantity();
    }
    return sum;
}

// !!TO DO!! Determines if a cookware use is sucessful (if requested cookware exists), and uses up ingredients in cooking
bool inventory::useCookware(char type, int kgIngredientsUsed)
{
    return true;
}

// Checks if sufficient gold is avalible
bool inventory::spendGold(int amountToSpend)
{
    if (goldPieces_ >= amountToSpend)
    {
        return true;
    }
    else return false;
}
