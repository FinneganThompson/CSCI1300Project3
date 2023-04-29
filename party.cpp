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
#include <fstream>


bool createResultsFile(vector<player> players, bool didPartyWin, int roomsCleared, int goldRemaining, vector<treasure> treasuresRemaining, 
int spacesExplored, int monstersDefeated, int turnsElapsed)
{
    ofstream outFile; 
    outFile.open("results.txt", ios::app);
    if (!outFile.is_open()) return false;

    if (didPartyWin)
    {
        outFile << "You won!\n";
    }
    else outFile << "You lost.\n";

    for(int i=0; i<players.size(); i++)
    {
        if (players.at(i).isUserPlayer)
        {
            outFile << players.at(i).name << endl;
            break;
        }
    }
    outFile << "The remaning players in your party are:\n";
    for(int i=0; i<players.size(); i++)
    {
        if (!players.at(i).isUserPlayer)
        {
            outFile << players.at(i).name << endl;
            break;
        }
    }

    outFile << "Rooms cleared: " << roomsCleared << endl;
    outFile << "Gold remaining: " << goldRemaining << endl;
    outFile << "Currently held treasure items: \n";
    for (int i=0; i<treasuresRemaining.size();i++)
    {
        outFile << '\t' << treasuresRemaining.at(i).getType() << endl;
    }
    outFile << "Spaces explored: " << spacesExplored << endl;
    outFile << "Monsters defeated: " << monstersDefeated << endl;
    outFile << "Turns elapsed: " << turnsElapsed << endl;
    return true;
}

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

void party::cookAndEat(){
    cout << "In order to cook a meal, you must have at least 5kg of ingredients and can only cook in 5kg increments." << endl <<
    "For each 5kg of ingredients cooked, your whole party will gain back 1 fullness point, however no one can exceed more than 50 fullness points.\n" << endl;
    if(partyInventory_.totalIngredientsAvliable() < 5){
        cout << "Unfortunately it looks like you don't have enough ingredients for a meal, better hope you find a merchant!\n"<< endl;
    }
    else{
        RNG random;
        int quantity = partyInventory_.totalIngredientsAvliable() + 1, typeCookware;
        bool canCook = false;
        while(quantity > partyInventory_.totalIngredientsAvliable()){
            cout << "How much would you like to cook?\n" << endl;
            cin >> quantity;
            cout << endl;
            if(quantity > partyInventory_.totalIngredientsAvliable() || quantity % 5 != 0){
                cout << "Hmm... I am not sure you can cook with that amount. Make sure you have enough ingredients and its an increment of 5!\n" << endl;
            }
            else{
                while(canCook == false){
                    cout << "And what would you like to cook with?\n1. Pot\n2. Frying pan\n3. Cauldron\n" << endl;
                    cin >> typeCookware;
                    cout << endl;
                    cout << partyInventory_.cookwareAvailible().at(typeCookware-1).getQuantity() << endl << endl;
                    if(partyInventory_.cookwareAvailible().at(typeCookware-1).getQuantity() < 1){
                        cout << "Looks like you dont have enough " << partyInventory_.cookwareAvailible().at(typeCookware-1).getType() << 
                        "s to cook with one. Try something else.\n" << endl;
                    }
                    else{
                        canCook = true;
                    }
                }
                if(partyInventory_.useCookware(typeCookware-1) == false){
                    cout << "Oooo, your " << partyInventory_.cookwareAvailible().at(typeCookware-1).getType() << 
                    " broke while trying to use it. Unfortunately that means no food, a waste of ingredients, and you no longer have your " << 
                    partyInventory_.cookwareAvailible().at(typeCookware-1).getType() << ".\n" << endl;
                }
                else{
                    cout << "Your food was cooked successfully! Everyone in your party gains " << (quantity/5) << " fullness point(s).\n" << endl;
                    for(int i = 0; i < getPlayers().size(); i++){
                        addHunger(i,(quantity/5));
                    }
                }
                partyInventory_.addIngredients(-quantity);
            }
        }
        printFullness();
        cout << endl << "You have " << partyInventory_.totalIngredientsAvliable() << "kg of ingredients left.\n" << endl;
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
void party::winBattle(string monsterName, bool &gameOver)
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
        else killPlayerOfHunger(players_.at(i).name, gameOver);
    }
  }
  return;
}

// !! TO DO !! Lose 1/4 of gold, up to 30kg food, each party member wearing armor has 5% death, otherwise 10% death. 
//Prints death message if neccesary. 50% food drop by 1. 
void party::loseBattle(bool &gameOver)
{
    RNG randomGenerator;
    int goldToLose = partyInventory_.goldAvalible() / 4; // Gold to lose
    int ingredientsToLose = randomGenerator.randIntOnRange(0,partyInventory_.totalIngredientsAvliable()/2); // Ingredients to lose (cannot lose more than half)
    if (partyInventory_.totalIngredientsAvliable() == 0)
    {
        ingredientsToLose = 0;
    }

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
        else killPlayerOfHunger(players_.at(i).name, gameOver);
    }
  }
}

// !! TO DO !! Party loses one non-main member and their items as appropiate. 50% food drop by 1. 
void party::surrenderBattle(bool &gameOver){
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
            else killPlayerOfHunger(players_.at(i).name, gameOver);
        }
    }
    return;
}

// !! TO DO !! Returns all starving players
vector<player> party::starvingPlayers()
{
   vector<player> starvingPlayers;
    for (int i=0; i<players_.size(); i++)
    {
        if (players_.at(i).hunger < 5)
        {
            starvingPlayers.push_back(players_.at(i));
        }
    }
    return starvingPlayers;
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
void party::killPlayerOfHunger(string name, bool &gameOver){
    cout << name <<" has died of hunger. Your party grows smaller..." << endl;
    killPlayerNoMessage(name);
    for(int i = 0; i < getPlayers().size(); i++){
        if(name == getPlayers().at(i).name && getPlayers().at(i).isUserPlayer == true){
            loseGame(2);
            bool gameOver = true;
        }
        
    }
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
        cout << "\t" << treasuresGotten.at(i).getType() << ": " << treasuresGotten.at(i).getQuantity() << endl;
    }
    cout << "Spaces explored: " << spacesExplored_ << endl;
    cout << "Monsters defeated: " << numMonstersDefeated_ << endl;
    cout << "Turns elapsed: " << turnsElapsed_ << endl;
    createResultsFile(players_, true, roomsCleared_, partyInventory_.goldAvalible(), partyInventory_.treasureAvailible(), spacesExplored_, 
    numMonstersDefeated_, turnsElapsed_);
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
            cout << "\t" << players_.at(i).name << endl;
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
            cout << "\t" << players_.at(i).name << endl;
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
    cout << "Turns elapsed: " << turnsElapsed_ << endl;

    createResultsFile(players_, false, roomsCleared_, partyInventory_.goldAvalible(), partyInventory_.treasureAvailible(), spacesExplored_, 
    numMonstersDefeated_, turnsElapsed_);
    return;
}

/*
Algorithm prints the fullness points of each player in the party
Accepts a party object
Loop through the party and print the fullness points for each member
*/

// selection sort
void selectionSort(vector<int> &values){
    int max;
    for(int i = 0; i < values.size(); i++){
        max = i;
        //cout << "OG " << values.at(i) << endl;
        for(int j = i + 1; j < values.size(); j++){
            //cout << " " << values.at(y) << endl;
            if(values.at(j) > values.at(max)){
                max = j;
            }
        }
        if(max != i){
            int holder = values.at(i);
            values.at(i) = values.at(max);
            values.at(max) = holder;
        }
        //cout << values.at(i);
    }
    cout << endl;
}


void party::printFullness(){
    cout << "+-------------+\n| PARTY       |\n+-------------+" << endl;
    // selection sort
    int max;
    for(int i = 0; i < players_.size(); i++){
        max = i;
        for(int j = i + 1; j < players_.size(); j++){
            if(players_.at(j).hunger > players_.at(max).hunger){
                max = j;
            }
        }
        if(max != i){
            player holder = players_.at(i);
            players_.at(i) = players_.at(max);
            players_.at(max) = holder;
        }
    }
    // loop through all the party members and print out their fullness
    for(int i = 0; i < players_.size(); i++){
        cout << "| " << players_.at(i).name << " | Fullness: " << players_.at(i).hunger << endl;
    }
    cout << "+-------------+\n" << endl;
}
