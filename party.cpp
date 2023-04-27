/*
* party.cpp
* CSCI 1300 Project 3, Spring 2023
* August Milliken & Finnegan Thompson
*
* implementations for the party class
*/

#include "party.h"
#include "item.h"
#include "RNG.h"
#include "game.h"
#include <iostream>

// Default constructor, sets all values to 0
party::party()
{
    roomsCleared_ = 0;
    spacesExplored_ = 0;
    keysFound_ = 0;
    turnsElapsed_ = 0;
    numMonstersDefeated_ = 0;
}

int party::getRoomsCleared() {return roomsCleared_;}
int party::getSpacesExplored() {return spacesExplored_;}
int party::getKeysFound() {return keysFound_;}
int party::getTurnsElapsed() {return turnsElapsed_;}
int party::getNumMonstersDefeated() {return numMonstersDefeated_;}

void party::increaseRoomsCleared() {roomsCleared_++; return;} // Inc. by 1
void party::increaseSpacesExplored() {spacesExplored_++; return;} // Inc. by 1
void party::increaseKeysFound() {keysFound_++; return;} // Inc. by 1
void party::loseKey() {keysFound_--; return;} // Decr by 1 
void party::incrementTurn() {turnsElapsed_++; return;} // Inc by 1

void party::addPlayer(player playerToAdd)
{
    players_.push_back(playerToAdd);
    return;
}


vector<player> party::getPlayers()
{
    return players_;
}

// !!TO DO!! When the party investigates a space (map operations are seperate) the following actions may occur with certain probabilities
// 10% key; 20% treasure; 10% monster; no matter outcome 50% individual hunger drop chance
void party::investigate()
{
    RNG random;
    bool healthDrop = false;
    int investigationResult = random.randIntBetweenOneAndTen();
    if(investigationResult == 1){
        increaseKeysFound();
        cout << "What luck, you found a key!\n" << endl;
    }
    else if(investigationResult == 2 || investigationResult == 3){
        if(getRoomsCleared() > 0){
            partyInventory_.changeTreasureQuantity(getRoomsCleared()-1,1);
            cout << "Something shiny... You found a " << partyInventory_.treasureAvailible().at(getRoomsCleared()-1).getType() << "!\n" << endl;
        }
    }
    else if(investigationResult == 4 || investigationResult == 5){
        cout << "Uh-oh, you have encountered a monster!\n" << endl;
        vector<Monster> monsters;
        readInMonsters(monsters, "monsters.txt");
        //fightMonster(monsters, mainParty);
        // lose health 50%
    }
    else{
        cout << "Looks like nothing turned up.\n" << endl;
    }
    if(healthDrop == false){
        if(random.doesActionOccur(50) == true){
            for(int i = 0; i < getPlayers().size(); i++){
                removeHunger(i,1);
            }
            cout << "You all became tired from exploring, -1 hunger.\n" << endl;
        }
    }
    increaseSpacesExplored();
    return;
}

// !!TO DO!! Prompts player for kg to cook and type of cookware. Determines sucess of cooking, and will add to hunger pts as appropriate
void party::cookAndEat(){
    cout << "In order to cook a meal, you must have at least 5kg of ingredients and can only cook in 5kg increments." << endl <<
    "For each 5kg of ingredients cooked, your whole party will gain back 1 fullness point. However no one can exceed 50 fullness points.\n" << endl;
    if(partyInventory_.totalIngredientsAvliable() < 5){
        cout << "Unfortunately it looks like you don't have enough ingredients for a meal, better hope you find a merchant!\n"<< endl;
    }
    else if(partyInventory_.totalCookware() == 0){
        cout << "Looks like you have no cookware to cook with, perhaps go see a merchant.\n" << endl;
    }
    else{
        RNG random;
        int quantity = partyInventory_.totalIngredientsAvliable() + 1, type = 0;
        bool hasType = false;
        while(quantity > partyInventory_.totalIngredientsAvliable()){
            cout << "How much would you like to cook?\n" << endl;
            cin >> quantity;
            cout << endl;
            if(quantity > partyInventory_.totalIngredientsAvliable() || quantity < 5){
                cout << "You can't make that, try a differnt amount and remember it has to be an increment of 5!\n" << endl;
            }
            else{
                while(hasType == false){
                    cout << "What would you like to cook with?\n1. Ceramic pot.\n2. Frying pan.\n3. Cauldron.\n" << endl;
                    cin >> type;
                    cout << endl;
                    if(partyInventory_.cookwareAvailible().at(type-1).getQuantity() == 0){
                        cout << "Unfortunately you don't have any of those to cook with. See if you have something else to use.\n" << endl;
                    }
                    else{
                        hasType = true;
                    }
                }
                if(partyInventory_.useCookware(type-1) == true){
                    cout << "Your food was made successfully! You have all gained: " << (quantity / 5) << " fullness points!\n" << endl;
                    for(int i = 0; i < getPlayers().size(); i++){
                        addHunger(i,(quantity / 5));
                    }
                    partyInventory_.addIngredients(-quantity);
                }
                else{
                    cout << "Oh no! Your " << partyInventory_.cookwareAvailible().at(type-1).getType() << " broke. " << 
                    "You were unable to cook a meal and no longer have your " << partyInventory_.cookwareAvailible().at(type-1).getType() <<
                    ".\n" << endl;
                    partyInventory_.removeCookware(type-1);
                }
                printFullness();
                cout << "You have " << partyInventory_.totalIngredientsAvliable() << "kg of ingredients left.\n" << endl;
            }
        }
    }
}

// Removes hunger from player at player position. Returns false if removing that much would kill anyone
bool party::removeHunger(int playerPosition, int hungerToRemove)
{
    if (hungerToRemove >= players_.at(playerPosition).hunger)
    {
        return false;
    }
    else 
    {
        players_.at(playerPosition).hunger -= hungerToRemove;
        return true;
    }
}

// Adds hunger points
void party::addHunger(int playerPosition, int hungerToAdd){
    if((hungerToAdd + players_.at(playerPosition).hunger) > 50){
        players_.at(playerPosition).hunger = 50;
    }
    else{
        players_.at(playerPosition).hunger += hungerToAdd;
    }
}

// iterates num monsters defeated by 1 adds to monsters defeated. 50% chance for each player to lose one hunger
void party::winBattle(string monsterName)
{
  RNG randomGenerator;
  monstersDefeated_.push_back(monsterName); // Add name to monsters defeated
  numMonstersDefeated_++; // iterate num monsters defeated
  
  // 50% chance for each player to lose one hunger
  for (int i=0; i<players_.size(); i++)
  {
    if (randomGenerator.doesActionOccur(50)) 
    {
        if (removeHunger(i,1)) continue; // If losing the 1 hunger would kill them, kill them. 
        else killPlayerOfHunger(players_.at(i).name);
    }
  }
  return;
}

// !! TO DO !! Lose 1/4 of gold, up to 30kg food, each party member wearing armor has 5% death, otherwise 10% death. 
//Prints death message if neccesary. 50% food drop by 1. 
void party::loseBattle()
{
    RNG randomGenerator;
    int goldToLose = partyInventory_.goldAvalible() / 4; // Gold to lose
    int ingredientsToLose = randomGenerator.randIntOnRange(0,partyInventory_.totalIngredientsAvliable()/2); // Ingredients to lose (cannot lose more than half)

    // Go through all players and check to see if they die
    for (int i = 0; i<players_.size(); i++)
    {
        if (partyInventory_.armorAvalible()-i >= 0 && !players_.at(i).isUserPlayer)  // Check to see if this user is wearing armor and is not the main player
        {
            if (randomGenerator.doesActionOccur(5))
            {
                cout << players_.at(i).name << " has died in the battle." << endl;
                killPlayerNoMessage(players_.at(i).name);
            }
        } // Player has no armor
        else if (partyInventory_.armorAvalible()-i < 0 && !players_.at(i).isUserPlayer)
        {
           if (randomGenerator.doesActionOccur(10))
            {
                cout << players_.at(i).name << " has died in the battle." << endl;
                killPlayerNoMessage(players_.at(i).name);
            } 
        }
        
    }
    // Remove the gold
    partyInventory_.spendGold(goldToLose);

    // Remove the ingredients 
    partyInventory_.addIngredients(-ingredientsToLose);

    cout << "You have lost the battle. You lost " << goldToLose << " gold, and " << ingredientsToLose << " ingredients." << endl;

  // 50% chance for each player to lose one hunger
  for (int i=0; i<players_.size(); i++)
  {
    if (randomGenerator.doesActionOccur(50))
    {
        if (removeHunger(i,1)) continue;
        else killPlayerOfHunger(players_.at(i).name);
    }
  }
}

// !! TO DO !! Party loses one non-main member and their items as appropiate. 50% food drop by 1. 
void party::surrenderBattle(){
    RNG randomGenerator;
    cout << "You have chosen to surrender this battle." << endl;
    int playerToKill = 0;

    do
    {
        playerToKill = randomGenerator.randIntOnRange(0,players_.size() - 1);
    } while (players_.at(playerToKill).isUserPlayer);
    cout << players_.at(playerToKill).name << " has been killed." << endl;
    killPlayerNoMessage(players_.at(playerToKill).name);


    // 50% chance for each player to lose one hunger
    for (int i=0; i<players_.size(); i++)
    {
        if (randomGenerator.doesActionOccur(50))
        {
            if (removeHunger(i,1)) continue;
            else killPlayerOfHunger(players_.at(i).name);
        }
    }
    return;
}

// !! TO DO !! Returns all starving players
vector<player> party::starvingPlayers()
{
    player tempPlayer; // Code just for testing
    tempPlayer.name = "TestPlayer";

    vector<player> testPlayerVector;
    testPlayerVector.push_back(tempPlayer);

    return testPlayerVector;
}

 // !! TO DO !! Returns filled status:
 /*
 Number of rooms cleared 
 Keys found
fullness of each party member 
Ingredients (kg) 
cookware available
Weapons and armor available
Gold available 
Treasure items available 
Sorcerer’s anger
 */
 // partyStatus party::getStatus()

 // !! TO DO !! Returns all of the contributors to the sucess of an attack that are parts of the party class.
// partyDependentAttackContributors getPartyDependentAttackContributors()

// Removes a player and thier items as appropriate
void party::killPlayerNoMessage(string name){
     partyInventory_.removeArmor(1);
    partyInventory_.removeWeapon(0);
    for(int i=0; i<players_.size(); i++) // Loop through all players
    {
        if (players_.at(i).name == name) // Find one with the correct name
        {
            players_.erase(players_.begin()+i); // Delete the player
            return;
        }
    }
    return;
}

// !! TO DO !! Removes player + items and prints hunger death message
void party::killPlayerOfHunger(string name){
    cout << name <<" has died of hunger. Your party grows smaller..." << endl;
    killPlayerNoMessage(name);
    return;
}

// !! TO DO !! Game win: Print out nesary info from party class
/*
    name of leader and remaining members
    number of rooms cleared
    gold remaining
    treasure items
    number of spaces explored
    number of monsters defeated
*/
void party::winGame(){
    cout << "You have won the game!\n" << "Your party leader is: \n";
    for(int i=0; i<players_.size(); i++)
    {
        if (players_.at(i).isUserPlayer)
        {
            cout << players_.at(i).name << endl;
            break;
        }
    }
    cout << "The remaning players in your party are:\n";
    for(int i=0; i<players_.size(); i++)
    {
        if (!players_.at(i).isUserPlayer)
        {
            cout << players_.at(i).name << endl;
            break;
        }
    }

    cout << "Rooms cleared: " << roomsCleared_ << endl;
    cout << "Gold remaining: " << partyInventory_.goldAvalible() << endl;
    cout << "Currently held treasure items: \n";
    vector<treasure> treasuresGotten = partyInventory_.treasureAvailible();
    for (int i=0; i<treasuresGotten.size();i++)
    {
        cout << treasuresGotten.at(i).getType() << endl;
    }
    cout << "Spaces explored: " << spacesExplored_ << endl;
    cout << "Monsters defeated: " << numMonstersDefeated_ << endl;
    return;
}

// Game is lost. Print same info as win. Type 0:Give up; 1: all but main player die; 2: main player dies; 3: Sorcerer's anger; 4: sorcerer kills them.
void party::loseGame(int deathType){   
    // Reasons why the player lost
    switch(deathType)
    {
        case 0:
            cout << "You gave up the game. It's not really that hard..." << endl;
            break;
        case 1:
            cout << "Everyone but you has died... You cannot continue without your party." << endl;
            break;
        case 2:
            cout << "You died, and your party cannot continue on without you." << endl;
            break;
        case 3:
            cout << "The Sorcerer's anger has overwhelmed the dungeon, and all in it have perished." << endl;
            break;
        case 4:
            cout << "The Sorcerer has killed all of your party with a powerfull spell." << endl;
            break;
        default:
            cout << "You have lost the game" << endl;
    }
    for(int i=0; i<players_.size(); i++)
    {
        if (players_.at(i).isUserPlayer)
        {
            cout << players_.at(i).name << endl;
            break;
        }
    }
    cout << "The remaning players in your party are:\n";
    for(int i=0; i<players_.size(); i++)
    {
        //check why
        // could make i start at 1 but potentially run into error if game ends from too few players
        if (!players_.at(i).isUserPlayer)
        {
            cout << players_.at(i).name << endl;
            break;
        }
    }

    cout << "Rooms cleared: " << roomsCleared_ << endl;
    cout << "Gold remaining: " << partyInventory_.goldAvalible() << endl;
    cout << "Currently held treasure items: \n";
    vector<treasure> treasuresGotten = partyInventory_.treasureAvailible();
    for (int i=0; i<treasuresGotten.size();i++)
    {
        cout << "\t" << treasuresGotten.at(i).getType() << ": " << treasuresGotten.at(i).getQuantity() << endl;
    }
    cout << "Spaces explored: " << spacesExplored_ << endl;
    cout << "Monsters defeated: " << numMonstersDefeated_ << endl;
    return;
}

/*
Algorithm prints the fullness points of each player in the party
Accepts a party object
Loop through the party and print the fullness points for each member
*/

void party::printFullness(){
    cout << "+-------------+\n| PARTY       |\n+-------------+" << endl;
    // loop through all the party members and print out their fullness
    for(int i = 0; i < players_.size(); i++){
        cout << "| " << players_.at(i).name << " | Fullness: " << players_.at(i).hunger << endl;
    }
    cout << "+-------------+\n" << endl;
}
