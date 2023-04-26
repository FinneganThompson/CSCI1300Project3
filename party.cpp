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
#include <fstream>


bool createResultsFile(vector<player> players, bool didPartyWin, int roomsCleared, int goldRemaining, vector<treasure> treasuresRemaining, int spacesExplored, int monstersDefeated, int turnsElapsed)
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
    cout << "The remaning players in your party are:\n";
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
    return;

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
    return;
}

// !!TO DO!! Prompts player for kg to cook and type of cookware. Determines sucess of cooking, and will add to hunger pts as appropriate
void party::cookAndEat()
{
    return;
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

    cout << "You have lost the battle. You lost" << goldToLose << "gold, and " << ingredientsToLose << " ingredients." << endl;

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
void party::surrenderBattle()
{
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

 // NO LONGER NEEDED Returns filled status:
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
void party::killPlayerNoMessage(string name)
{
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

// Removes player + items and prints hunger death message
void party::killPlayerOfHunger(string name)
{
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
void party::winGame()
{
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
        cout << '\t' << treasuresGotten.at(i).getType() << endl;
    }
    cout << "Spaces explored: " << spacesExplored_ << endl;
    cout << "Monsters defeated: " << numMonstersDefeated_ << endl;
    cout << "Turns elapsed: " << turnsElapsed_ << endl;
    createResultsFile(players_, true, roomsCleared_, partyInventory_.goldAvalible(), partyInventory_.treasureAvailible(), spacesExplored_, numMonstersDefeated_, turnsElapsed_);
    return;
}

// Game is lost. Print same info as win. Type 0:Give up; 1: all but main player die; 2: main player dies; 3: Sorcerer's anger; 4: sorcerer kills them.
void party::loseGame(int deathType)
{   
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
        cout << '\t' << treasuresGotten.at(i).getType() << endl;
    }
    cout << "Spaces explored: " << spacesExplored_ << endl;
    cout << "Monsters defeated: " << numMonstersDefeated_ << endl;
    cout << "Turns elapsed: " << turnsElapsed_ << endl;

    createResultsFile(players_, false, roomsCleared_, partyInventory_.goldAvalible(), partyInventory_.treasureAvailible(), spacesExplored_, numMonstersDefeated_, turnsElapsed_);

    return;
}

