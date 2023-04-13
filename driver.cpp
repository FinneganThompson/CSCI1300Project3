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

    // check declaring and changing a monster
    string nameM = "Lizard man";
    int levelM = 2;
    Monster m(nameM, levelM);
    assert(m.getName()=="Lizard man");
    assert(m.getLevel()==2);
    m.setLevel(4);
    m.setName("Demiguise");
    assert(m.getName()=="Demiguise");
    assert(m.getLevel()==4);

    // check declaring and changing the sorcerer
    string nameS = "Sorcerer";
    int levelS = 6;
    Sorcerer s(nameS, levelS);
    assert(s.getName()=="Sorcerer");
    assert(s.getLevel()==6);
    assert(s.getAnger()==0);
    s.setLevel(5);
    s.setName("Bill");
    s.increaseAnger();
    s.increaseAnger();
    s.increaseAnger();
    assert(s.getName()=="Bill");
    assert(s.getLevel()==5);
    assert(s.getAnger()==3);

    return 0;

}
