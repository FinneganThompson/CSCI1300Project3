/*
* driver.cpp
* CSCI 1300 Project 3, Spring 2023
* August Milliken & Finnegan Thompson
*
* Tests the classes for the program (some of which have multiple nested classes)
*/

#include "item.h"
#include "Monster.h"
#include "Sorcerer.h"
#include "party.h"
#include <cassert>

int main()
{
    // This tests the party and inventory classes (as inventory is a nested class in party)
    party mainParty;
    // Check default constructor
    assert(mainParty.getRoomsCleared() == 0);
    mainParty.increaseRoomsCleared();
    assert(mainParty.getRoomsCleared() == 1);

    assert(mainParty.getKeysFound() == 0);
    mainParty.increaseKeysFound();
    assert(mainParty.getKeysFound() == 1);

    // Checking starving player return
    player tempPlayer;
    tempPlayer.name = "TestPlayer";
    assert(mainParty.starvingPlayers().at(0).name == tempPlayer.name);

    // Check spending gold
    mainParty.partyInventory_.addGold(20);
    assert(mainParty.partyInventory_.goldAvalible() == 20);
    mainParty.partyInventory_.spendGold(10);
    assert(mainParty.partyInventory_.goldAvalible() == 10);
    assert(mainParty.partyInventory_.spendGold(20) == false);



    return 0;

}
